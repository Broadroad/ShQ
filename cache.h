#include <unistd.h>
class Cache
{
private:
    int size_;
public:
    Cache(int size) : size_(size) {};
    virtual ~Cache() {};
    virtual uint8_t* Data(int x) const = 0;
    int Size() {return size_;};
};
