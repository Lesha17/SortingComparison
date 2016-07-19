#include<iostream> // to use swap()

using namespace std;

void bubble_simple_sort(int * a, size_t a_len) {
	size_t i, j;
	for (i = 0; i < a_len - 1; ++i) {
		for (j = a_len - 1; j > i; --j) {
			if (a[j - 1] > a[j]) {
				swap(a[j - 1], a[j]);
			}
		}
	}
}

void bubble_first_criteria_sort(int * a, size_t a_len) {
	bool swapped;
	size_t i, j;
	for (i = 0; i < a_len - 1; ++i) {
		swapped = false;
		for (j = a_len - 1; j > i; --j) {
			if (a[j - 1] > a[j]) {
				swap(a[j - 1], a[j]);
				swapped = true;
			}
		}
		if (!swapped) {
			break;
		}
	}
}

void bubble_first_and_second_criteria_sort(int * a, size_t a_len) {
	size_t k = 0, r;
	size_t i, j;
	for (i = 0; i < a_len - 1; ++i) {
		r = k;
		for (j = a_len - 1; j > k; --j) {
			if (a[j - 1] > a[j]) {
				swap(a[j - 1], a[j]);
				r = j;
			}
		}
		if (r == k) {
			break;
		}
		k = r;
	}
}

inline int bin_search(int * a, size_t left, size_t right, int k) {
	if (right - left <= 1) {
		if (a[left] < k) {
			return left + 1;
		}
		else {
			return left;
		}
	}
	size_t mid = (left + right) / 2;
	if (a[mid] < k) {
		return bin_search(a, mid + 1, right, k);
	}
	else {
		return bin_search(a, left, mid, k);
	}
}

void linear_insert_sort(int * a, size_t a_len) {
	size_t i;
	size_t k;
	for (i = 1; i < a_len; ++i) {
		k = a[i];
		for (int j = i - 1; j >= 0; --j) {
			if (a[j] > k) {
				swap(a[j], a[j + 1]);
			}
			else {
				break;
			}
		}
	}
}

void binary_insert_sort(int * a, size_t a_len) {
	size_t i, j, k, move_len;
	for (int i = 1; i < a_len; ++i) {
		k = a[i];
		j = bin_search(a, 0, i, k);
		move_len = i - j;
		memcpy(&a[j + 1], &a[j], (move_len)* sizeof(int));
		a[j] = k;
	}
}
