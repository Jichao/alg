#include <stdio.h>
#include <stdlib.h>

void merge(std::vector<int>& numbers, size_t low, size_t mid, size_t high)
{
	size_t srcIndex1 = low;
	size_t srcIndex2 = mid + 1;
	size_t dstIndex = 0;
	std::vector<int> dstNumbers;
	dstNumbers.resize(high - low + 1);
	while (dstIndex != high - low + 1) {
		if (srcIndex1 == mid + 1) {
			std::copy(
		}
	}

}

void sort(std::vector<int>& numbers, size_t low, size_t high)
{
	if (low == high)
		return;
	if (low + 1 == high) {
		if (numbers[low] > numbers[high]) {
			std::swap(numbers[low], numbers[high]);
		}
		return;
	}
	int mid = (low + high) / 2;
	sort(numbers, low, mid);
	sort(numbers, mid, high);
	merge(numbers, low, mid, high);
}

int main()
{
	int count;
	std::cout << "number count:";
	std::cin >> count;
	std::cout << "numbers:";
	std::vector<int> numbers;
	for (int i = 0; i < count; ++i) {
		int number;
		std::cin >> number;
		numbers.push_back(number);
	}

	for (int i = 1; i < count; ++i) {
		for (int j = 0; j < i; ++j) {
			if (numbers[i] < numbers[j]) {
				int value = numbers[i];
				for (int x = i; x != j; --x) {
					numbers[x] = numbers[x - 1];
				}
				numbers[j] = value;
			}
		}
	}

	std::cout << "insert sort result:\n";
	for (int i = 0; i < count; ++i) {
		std::cout << numbers[i] << "\t";
	}
	std::cout << "\n";
	return 0;
}


