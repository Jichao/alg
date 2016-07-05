//the brute-force version of maximum sub array version
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct tagSubArrayResult {
	int low;
	int high;
	int sum;
} SubArrayResult;

//find max subarray in [low, high]
SubArrayResult find_max_subarray(int* numbers, int low, int high)
{
	SubArrayResult result;
	result.sum = INT_MIN;
	for (int i = low; i <= high; ++i) {
		for (int j = i; j <= high; ++j) {
			int sum = 0;
			for (int k = i; k <= j; ++k) {
				sum += numbers[k];
			}
			if (sum > result.sum) {
				result.sum = sum;
				result.low = i;
				result.high = j;
			}
		}
	}
	return result;
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
