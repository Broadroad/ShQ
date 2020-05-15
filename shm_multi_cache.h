#ifndef SHM_MULTI_CACHE
#define SHM_MULTI_CACHE

#include "cache.h"

using namespace std;

struct HugepageFileInfo {
	uint64_t addr;            /**< virtual addr */
	uint32_t   size;            /**< the file size */
	char     path[4096];  /**< path to backing file */
    HugepageFileInfo(uint64_t addr_, uint32_t size_, string path_) : addr(addr_), size(size_) {
        strcpy(path, path_.c_str());
    };
};

class Shm_multi_cache :  public Cache
{
private:
    vector<HugepageFileInfo> hugeFiles; 
    HugepageFileInfo gen(int num) {
        string name = "/tmp/shm_" + to_string(num);
        int fd = open(name_.c_str(), O_RDWR|O_CREAT|O_TRUNC, 0644);
        if (fd < 0) {
            cout << "Open Shared Memory failed" << endl;
        }
        ftruncate(fd, BLK);
        uint8_t* p = (uint8_t *)mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        if (p == MAP_FAILED) {
            cout << "Mmap Shared Memory failed" << endl;
        }
        uint64_t addr = reinterpret_cast<uint64_t>(p);
        HugepageFileInfo h(addr, BLK, name);
        return h;
    }

    HugepageFileInfo get(int num) {
        string name = "/tmp/shm_" + to_string(num);
        int fd = open(name.c_str(), O_RDONLY, 0644);
        if (fd < 0) {
            perror("open");
		    exit(2);
        } 
        uint8_t *p = (uint8_t*)mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
        if (p == MAP_FAILED) {
            perror("mmap");
		    exit(3);
        } 
        uint64_t addr = reinterpret_cast<uint64_t>(p);
        HugepageFileInfo h(addr, BLK, name);
        return h;
    }
public:
    const int BLK = 2 * 1024;
    const string SHM_NAME = "/tmp/shm_test";
    const int SHM_NUM = 10;
    Shm_multi_cache() : Cache(BLK * SHM_NUM) {
        for (int i = 0; i < SHM_NUM; i++) {
            hugeFiles.push_back(gen(i));
        }
    }
    Shm_multi_cache(bool read) : Cache(BLK * SHM_NUM) {
        for (int i = 0; i < SHM_NUM; i++) {
            hugeFiles.push_back(get(i));
        }
    }
    ~Shm_multi_cache();
    vector<HugepageFileInfo> GetShms() {
        return hugeFiles;
    }

    uint8_t* Data(string x) const {
        return reinterpret_cast<uint8_t*>(hugeFiles[stoi(x)].addr); 
    }
};



#endif