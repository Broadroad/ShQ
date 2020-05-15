#include <iostream>
#include "ShmCache.h"
#include "shm_multi_cache.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "./consumer file";
        exit(1);
    }

    Cache *cache = new Shm_multi_cache(true);
    for (int i = 0;;i++) {
        uint8_t p[BLK];
        memcpy(p, cache->Data(to_string(i)), BLK);
        for (int j = 0; j < BLK; j++) {
            cout << p[j] << " ";
        }
        std::cout << endl;
        sleep(1);
    } 
    return 0;
}