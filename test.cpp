#include <iostream>
#include <unistd.h>
#include <assert.h>
using namespace std;

int main() {
	uint8_t c = 1;
	uint8_t *b = &c;
	uint64_t a = reinterpret_cast<uint64_t>(b);;
	auto int_as_pointer = reinterpret_cast<uint8_t*>(a);
	assert(&c == int_as_pointer);
	printf("%u %u\n", &c, int_as_pointer);
	printf("%d %d\n", c, *int_as_pointer);
}
