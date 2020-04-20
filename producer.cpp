#include <iostream>
#include "ShmCache.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "./producer file";
        exit(1);
    }

    ShmCache cache("/tmp/test", BLK * 32);
    for (int i = 0;;i++) {
        uint8_t a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        memcpy(cache.Data(i), a, 9);
        sleep(1);
    } 
    return 0;
}