#include <iostream>
#include <sys/mman.h>
using namespace std;
const int BLK = 2 * 1024;
class ShmCache {
private:
    int fd_;
    uint8_t *p_;
    uint32_t size_;
    string name_;
public:
    ShmCache(string name, int size) : name_(name), size_(size) {
        fd_ = open(name, O_RDWR|O_CREAT|O_TRUNC,0644);
        if (fd_ < 0) {
            perror("open");
		    exit(2);
        } 
        ftruncate(fd, size);
        p = (uint8_t*)mmap(NULL, size, PROT_READ|PROT_WRITE,MAP_SHARED, fd, 0);
        if (p_ == MAP_FAILED) {
            perror("mmap");
		    exit(3);
        } 
    }

    ~ShmCache() {
        close(fd_);
        int ret = munmap(p, ));
        if(ret < 0) {
            perror("mmumap");
            exit(4);
        }
    }

    uint8_t* Data(int x) {
        return p_ + x * BLK; 
    }

}