#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#define ARRAY_SIZE 10

typedef struct {
    int *inputArray;
    int *outputArray;
    int startIndex;
    int endIndex;
    int offsetValue;
} PrefixSumThreadArgs;

void* calculatePrefixSum(void* args) {
    PrefixSumThreadArgs* threadArgs = (PrefixSumThreadArgs*)args;
    threadArgs->outputArray = malloc(sizeof(int) * (threadArgs->endIndex - threadArgs->startIndex));
    if (!threadArgs->outputArray) {
        perror("Memory allocation failed");
        pthread_exit(NULL);
    }
    threadArgs->outputArray[0] = threadArgs->inputArray[threadArgs->startIndex] + threadArgs->offsetValue;
    for (int i = threadArgs->startIndex + 1; i < threadArgs->endIndex; i++) {
        threadArgs->outputArray[i - threadArgs->startIndex] = threadArgs->outputArray[i - threadArgs->startIndex - 1] + threadArgs->inputArray[i];
    }
    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));
    struct timeval startTime, endTime;
    int inputArray[ARRAY_SIZE];
    int midpoint = ARRAY_SIZE / 2;

    for (int i = 0; i < ARRAY_SIZE; i++) {
        inputArray[i] = rand() % 10;
    }

    gettimeofday(&startTime, NULL);

    PrefixSumThreadArgs args1 = {inputArray, NULL, 0, midpoint, 0};
    PrefixSumThreadArgs args2 = {inputArray, NULL, midpoint, ARRAY_SIZE, 0};
    pthread_t thread1, thread2;

    if (pthread_create(&thread1, NULL, calculatePrefixSum, &args1) != 0) {
        perror("Failed to create first thread");
        return 1;
    }

    if (pthread_join(thread1, NULL) != 0) {
        perror("Failed to join first thread");
        return 1;
    }

    args2.offsetValue = args1.outputArray[midpoint - 1];

    if (pthread_create(&thread2, NULL, calculatePrefixSum, &args2) != 0) {
        perror("Failed to create second thread");
        return 1;
    }

    if (pthread_join(thread2, NULL) != 0) {
        perror("Failed to join second thread");
        return 1;
    }

    free(args1.outputArray);
    free(args2.outputArray);

    gettimeofday(&endTime, NULL);
    double executionDuration = (endTime.tv_sec - startTime.tv_sec) * 1000.0 + (endTime.tv_usec - startTime.tv_usec) / 1000.0;
    printf("Total Execution Time: %.6f milliseconds \n", executionDuration);

    return 0;
}
