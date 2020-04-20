#include <iostream>
#include "ShmCache.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "./consumer file";
        exit(1);
    }

    ShmCache cache("/tmp/test", BLK * 32);
    for (int i = 0;;i++) {
        uint8_t p[10];
        memcpy(p, cache.Data(i), 9);
        for (int i = 0; i < 9; i++) {
            cout << p[i] << " ";
        }
        std::cout << endl;
        sleep(1);
    } 
    return 0;
}