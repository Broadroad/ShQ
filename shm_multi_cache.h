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
        fd_ = open(name_.c_str(), O_RDWR|O_CREAT|O_TRUNC, 0644);
        if (fd_ < 0) {
            cout << "Open Shared Memory failed" << endl;
        }
        ftruncate(fd_, BLK);
        p_ = (uint8_t *)mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd_, 0);
        if (p_ == MAP_FAILED) {
            cout << "Mmap Shared Memory failed" << endl;
        }
        HugepageFileInfo h(p_, BLK, name);
        return h;
    }

    HugepageFileInfo get(int num) {
        string name = "/tmp/shm_" + to_string(num);
        fd_ = open(name.c_str(), O_RDONLY, 0644);
        if (fd_ < 0) {
            perror("open");
		    exit(2);
        } 
        p_ = (uint8_t*)mmap(NULL, size, PROT_READ, MAP_SHARED, fd_, 0);
        if (p_ == MAP_FAILED) {
            perror("mmap");
		    exit(3);
        } 
        HugepageFileInfo h(p_, BLK, name);
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
        return hugeFiles[stoi(x)].addr; 
    }
};


