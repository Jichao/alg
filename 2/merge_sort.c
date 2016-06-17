#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//merge numbers in [low,high]
void merge(int* numbers, size_t low, size_t mid, size_t high)
{
	size_t srcIndex1 = low;
	size_t srcIndex2 = mid + 1;
	size_t dstIndex = 0;
	int* dstNumbers = malloc((high - low + 1) * sizeof(int));
	while (dstIndex != high - low + 1) {
		if (srcIndex1 == mid + 1) {
			memcpy(dstNumbers + dstIndex, numbers + srcIndex2, (high - srcIndex2 + 1) * sizeof(int));
			dstIndex += high - srcIndex2 + 1;
			srcIndex2 += high - srcIndex2 + 1;
			continue;
		}
		if (srcIndex2 == high + 1) {
			memcpy(dstNumbers + dstIndex, numbers + srcIndex1, (mid - srcIndex1 + 1) * sizeof(int));
			dstIndex += mid - srcIndex1 + 1;
			srcIndex1 += mid - srcIndex1 + 1;
			continue;
		}
		if (numbers[srcIndex1] < numbers[srcIndex2]) {
			dstNumbers[dstIndex] = numbers[srcIndex1];
			srcIndex1++;
			dstIndex++;
		} else {
			dstNumbers[dstIndex] = numbers[srcIndex2];
			srcIndex2++;
			dstIndex++;
		}
	}
	size_t i = 0;
	size_t j = low;
	for (; i < high - low + 1; i++, j++) {
		numbers[j] = dstNumbers[i];
	}
	free(dstNumbers);
}

//sort numbers in [low,high]
void sort(int* numbers, size_t low, size_t high)
{
	if (low == high)
		return;
	if (low + 1 == high) {
		if (numbers[low] > numbers[high]) {
			int temp = numbers[low];
			numbers[low] = numbers[high];
			numbers[high] = temp;
		}
		return;
	}
	int mid = (low + high) / 2;
	sort(numbers, low, mid); //sort numbers in [low, mid] 
	sort(numbers, mid + 1, high); // sort numbers in [mid, high]
	merge(numbers, low, mid, high);
}

int main()
{
	int count;
	printf("number count:");
	scanf("%d", &count);
	printf("numbers:");
	int* numbers = malloc(count * sizeof(int));
	for (int i = 0; i < count; ++i) {
		scanf("%d", &numbers[i]);
	}

	sort(numbers, 0, count - 1);

	printf("merge sort result:\n");
	for (int i = 0; i < count; ++i) {
		printf("%d\t", numbers[i]);
	}
	printf("\n");
	free(numbers);
	return 0;
}
