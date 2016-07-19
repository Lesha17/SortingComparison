#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <chrono>
#include "TestData.h"
#include "SortingAlgorithms.h"

using namespace std;

#define MAX_SIZE 9000
#define MIN_SIZE 1000
#define STEP 1000
#define TEST_CNT 100

#define CLOCK_FREQUENCY 1700000000

typedef struct sortAlgo {
	void(*sort)(int*, size_t);
	const char * name;
	ofstream file;

	sortAlgo(void(*_sort)(int*, size_t), const char * _name, const char * file_name) {
		sort = _sort;
		name = _name;
		file.open(file_name);
	}
};

typedef struct testAr {
	int * arr;
	const char * name;

	testAr(int * _arr, const char * _name) {
		arr = _arr;
		name = _name;
	}
};

long long test_sort(void(*sort)(int*, size_t), int *, size_t);
double average(unsigned long * a, size_t a_len);

int main()
{
	cout << fixed << setprecision(2);
	cout << "Time in concole is measured in milliseconds, but in csv files it is actually measured in nanoseconds" << endl;

	sortAlgo algos[5] = {
		sortAlgo(&bubble_simple_sort, "Simple bubble sort", "bubble_simple.csv"),
		sortAlgo(&bubble_first_criteria_sort, "Bubble sort with first criteria", "bubble_first.csv"),
		sortAlgo(&bubble_first_and_second_criteria_sort, "Bubble sort with two criterias", "bubble_second.csv"),
		sortAlgo(&linear_insert_sort, "Linear insert sort", "insert_linear.csv"),
		sortAlgo(&binary_insert_sort, "Insert sort with binary search", "insert_binary.csv")
	};

	testAr testData[4] = {
		testAr(generateRand07(MAX_SIZE), "Random numbers from 0 to 7"),
		testAr(generateRand0MaxInt(MAX_SIZE), "Random numbers from 0 to 32767"),
		testAr(generateAlmostSorted(MAX_SIZE), "Almost sorted array"),
		testAr(generateReverseSorted(MAX_SIZE), "Reverse sorted array")
	};

	int * rand07 = generateRand07(MAX_SIZE);
	int * rand0MaxInt = generateRand0MaxInt(MAX_SIZE);
	int * almost_sorted = generateAlmostSorted(MAX_SIZE);
	int * reverse_sorted = generateReverseSorted(MAX_SIZE);

	int * a = new int[MAX_SIZE];
	unsigned long * results = new unsigned long[TEST_CNT];

	for (size_t algo_i = 0; algo_i < 5; ++algo_i) {
		for (size_t test_data_i = 0; test_data_i < 4; ++test_data_i) {
			algos[algo_i].file << ";" << testData[test_data_i].name << ";";
		}
		algos[algo_i].file << endl;
		algos[algo_i].file << ";";
		for (size_t test_data_i = 0; test_data_i < 4; ++test_data_i) {
			algos[algo_i].file << "Average;Max;";
		}
		algos[algo_i].file << endl;

		for (size_t size = MIN_SIZE; size <= MAX_SIZE; size += STEP) {
			algos[algo_i].file << size << ";";
			for (size_t test_data_i = 0; test_data_i < 4; ++test_data_i) {
				cout << "Testing " << algos[algo_i].name << " at " << size << " for " << testData[test_data_i].name << endl;
				unsigned long maximum = 0;
				for (size_t i = 0; i < TEST_CNT; ++i) {
					copy_array_part(testData[test_data_i].arr, a, size);
					results[i] = test_sort(algos[algo_i].sort, a, size);
					if (maximum < results[i]) {
						maximum = results[i];
					}
				}

				long long avrg = (long long)average(results, TEST_CNT);
				cout << "\tavrg: " << avrg / 1000000.0 << "ms\t"
					<< "max: " << maximum / 1000000.0 << "ms"
					<< endl;
				algos[algo_i].file << avrg << ";" << maximum << ";";
			}
			algos[algo_i].file << endl;
		}
		algos[algo_i].file.close();
	}

	delete[] a;
	delete[] results;

	delete[] rand07;
	delete[] rand0MaxInt;
	delete[] almost_sorted;
	delete[] reverse_sorted;

	return 0;
}

long long test_sort(void(*sort)(int*, size_t), int * arr, size_t arr_len) {
	auto start = std::chrono::high_resolution_clock::now();
	sort(arr, arr_len);
	auto finish = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();
}

double average(unsigned long * a, size_t a_len) {
	double avrg = 0;
	double q = 1 / (double)a_len;
	for (size_t i = 0; i < a_len; ++i) {
		avrg += a[i] * q;
	}
	return avrg;
}


