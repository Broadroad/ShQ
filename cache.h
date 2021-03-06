#ifndef CACHE
#define CACHE
#include <unistd.h>
#include <iostream>
using namespace std;
class Cache
{
private:
    int size_;
public:
    Cache(int size) : size_(size) {};
    virtual ~Cache() {};
    virtual uint8_t* Data(string x) const = 0;
    int Size() {return size_;};
};

#endif