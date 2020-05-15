#include <iostream>
#include "ShmCache.h"
#include "shm_multi_cache.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "./producer file";
        exit(1);
    }

    Cache *cache = new Shm_multi_cache();
    for (int i = 0;;i++) {
        uint8_t a[BLK];
        for (int j = 0; j < BLK; j++) {
            a[j] = j % 10 + '0';
        }
        memcpy(cache->Data(to_string(i)), a, BLK);
        for (int j = 0; j < BLK; j++) {
            cout << *(cache->Data(to_string(i)) + j) << " ";
        }
        cout << endl;
        sleep(1);
    } 
    return 0;
}