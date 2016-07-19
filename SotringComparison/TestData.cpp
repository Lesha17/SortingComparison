#include <iostream> // to use a swap() void ...
#include <ctime>
#include <cstdlib>

using namespace std;

int * generateRand07(size_t size) {
	int * a = new int[size];

	srand(time(NULL));
	for (int i = 0; i < size; ++i) {
		a[i] = rand() % 8;
	}

	return a;
}

int * generateRand0MaxInt(size_t size) {
	int * a = new int[size];

	srand(time(NULL));
	for (int i = 0; i < size; ++i) {
		a[i] = rand();
	}

	return a;
}

int * generateAlmostSorted(size_t size) {
	int * a = new int[size];

	for (int i = 0; i < size; ++i) {
		a[i] = i;
	}

	for (int i = 0; i < 45; ++i) {
		int indx1 = rand() % size;
		int indx2 = rand() % size;
		
		swap(a[indx1], a[indx2]);
	}

	return a;
}

int * generateReverseSorted(size_t size) {
	int * a = new int[size];

	for (int i = 0; i < size; ++i) {
		a[i] = size - i - 1;
	}

	return a;
}

void copy_array_part(int * a, int * dst, size_t size) {
	memcpy(dst, a, size * sizeof(int));
}