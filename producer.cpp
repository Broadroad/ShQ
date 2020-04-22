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
        uint8_t a[BLK];
        for (int j = 0; j < BLK; j++) {
            a[j] = j % 10 + '0';
        }
        memcpy(cache.Data(i), a, BLK);
        for (int j = 0; j < BLK; j++) {
            cout << *(cache.Data(i) + j) << " ";
        }
        cout << endl;
        sleep(1);
    } 
    return 0;
}