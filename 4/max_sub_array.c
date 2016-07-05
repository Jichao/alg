#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct tagSubArrayResult {
	int low;
	int high;
	int sum;
} SubArrayResult;


//find max subarray cross mid [mid-a,mid+b] a>=0, b>0
SubArrayResult find_cross_max_subarray(int* numbers, int low, int high)
{
	SubArrayResult result;
	int mid = (low + high) / 2;

	int low_max_sum = INT_MIN;
	int low_index = mid;
	int low_sum = 0;
	int low_max_index = -1;
	while (low_index >= low) {
		low_sum += numbers[low_index];
		if (low_sum > low_max_sum) {
			low_max_sum = low_sum;
			low_max_index = low_index;
		}
		low_index--;
	}

	int high_max_sum = INT_MIN;
	int high_index = mid + 1;
	int high_sum = 0;
	int high_max_index = -1;
	while (high_index <= high) {
		high_sum += numbers[high_index];
		if (high_sum > high_max_sum) {
			high_max_sum = high_sum;
			high_max_index = high_index;
		}
		high_index++;
	}
	result.sum = low_max_sum + high_max_sum;
	result.low = low_max_index;
	result.high = high_max_index;
	return result;
}

//find max subarray in [low, high]
SubArrayResult find_max_subarray(int* numbers, int low, int high)
{
	SubArrayResult result;
	if (low == high) {
		result.low = low;
		result.high = high;
		result.sum = numbers[low];
		return result;
	}
	int mid = (low + high) / 2;
	SubArrayResult lowResult = find_max_subarray(numbers, low, mid);
	SubArrayResult highResult = find_max_subarray(numbers, mid + 1, high);
	SubArrayResult crossResult = find_cross_max_subarray(numbers, low, high);
	if (lowResult.sum > highResult.sum && lowResult.sum > crossResult.sum)
		return lowResult;
	if (highResult.sum > lowResult.sum && highResult.sum > crossResult.sum)
		return highResult;
	return crossResult;
}

int main()
{
	int times = 0;
	printf("times:");
	scanf("%d", &times);
	while(times--) {
		int count;
		printf("number count:");
		scanf("%d", &count);
		printf("numbers:");
		int* numbers = malloc(count * sizeof(int));
		for (int i = 0; i < count; ++i) {
			scanf("%d", &numbers[i]);
		}
		SubArrayResult result = find_max_subarray(numbers, 0, count - 1);
		printf("the max subarray is [%d, %d], sum = %d\n", result.low, result.high, result.sum);
	}
	return 0;
}
