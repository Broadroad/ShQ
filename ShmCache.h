#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>

#include "cache.h"

using namespace std;
const int BLK = 2 * 1024;
class ShmCache : public Cache{
private:
    int fd_;
    uint8_t *p_;
    string name_;
public:
    ShmCache(string name, int size) : Cache(size), name_(name) {
        fd_ = open(name.c_str(), O_RDWR|O_CREAT|O_TRUNC,0644);
        if (fd_ < 0) {
            perror("open");
		    exit(2);
        } 
        ftruncate(fd_, size);
        p_ = (uint8_t*)mmap(NULL, size, PROT_READ|PROT_WRITE,MAP_SHARED, fd_, 0);
        if (p_ == MAP_FAILED) {
            perror("mmap");
		    exit(3);
        } 
    }

    ShmCache(string name, int size, bool read) : Cache(size), name_(name) {
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
    }

    ~ShmCache() {
        close(fd_);
        int ret = munmap(p_, size_);
        if(ret < 0) {
            perror("mmumap");
            exit(4);
        }
    }

    void uint8_t* Data(int x) {
        return p_ + x * BLK; 
    }
};