#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#define ARRAY_SIZE 500000

int* calculatePrefixSum(int array[], int startIndex, int endIndex) {
    int* result = (int*)malloc(sizeof(int) * (endIndex - startIndex));
    result[startIndex] = 1;
    for (int i = startIndex + 1; i < endIndex; i++) {
        result[i] = result[i - 1] + array[i];
    }
    return result;
}

int main() {
    struct timeval startTime, endTime;
    srand(time(NULL));
    int inputArray[ARRAY_SIZE];
    
    for (int i = 0; i < ARRAY_SIZE; i++) {
        inputArray[i] = rand() % 10;
    }

    gettimeofday(&startTime, NULL);
    int* prefixSum = calculatePrefixSum(inputArray, 0, ARRAY_SIZE);
    gettimeofday(&endTime, NULL);

    double executionDuration = (endTime.tv_sec - startTime.tv_sec) * 1000.0 + (endTime.tv_usec - startTime.tv_usec) / 1000.0;
    printf("Time taken for execution: %.6f milliseconds \n", executionDuration);

    return 0;
}
