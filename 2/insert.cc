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

