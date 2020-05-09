#include <unistd.h>
class Cache
{
private:
    int size_;
public:
    Cache(int size) : size_(size) {};
    ~Cache() {};
    virtual uint8_t* Data(int x) const;
    int Size() {return size_;};
};
