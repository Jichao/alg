#include <iostream>
#include <stdio.h>
#include <vector>

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
		int key = numbers[i];
		int j = i - 1;
		while ((j >= 0) && key < numbers[j]) {
			numbers[j + 1] = numbers[j];
			j--;
		}
		numbers[j + 1] = key;
	}

	std::cout << "insert sort result:\n";
	for (int i = 0; i < count; ++i) {
		std::cout << numbers[i] << "\t";
	}
	std::cout << "\n";
	return 0;
}

