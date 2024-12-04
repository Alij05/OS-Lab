#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 2

typedef struct {
    int *inputArray;
    int *prefixSumArray;
    int startIndex;
    int endIndex;
} ThreadData;

void *computePrefixSum(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    data->prefixSumArray[data->startIndex] = data->inputArray[data->startIndex];
    for (int i = data->startIndex + 1; i < data->endIndex; i++) {
        data->prefixSumArray[i] = data->prefixSumArray[i - 1] + data->inputArray[i];
    }
    pthread_exit(0);
}

int main() {
    int inputArray[] = {1, 2, 1, 5, 0, 7, 3, 4, 2, 7};
    int size = sizeof(inputArray) / sizeof(inputArray[0]);
    int prefixSumArray[size];

    pthread_t threads[NUM_THREADS];
    ThreadData threadData[NUM_THREADS];
    int segmentSize = size / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; i++) {
        threadData[i].inputArray = inputArray;
        threadData[i].prefixSumArray = prefixSumArray;
        threadData[i].startIndex = i * segmentSize;
        threadData[i].endIndex = (i == NUM_THREADS - 1) ? size : (i + 1) * segmentSize;
        pthread_create(&threads[i], NULL, computePrefixSum, &threadData[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 1; i < NUM_THREADS; i++) {
        int offset = prefixSumArray[threadData[i - 1].endIndex - 1];
        for (int j = threadData[i].startIndex; j < threadData[i].endIndex; j++) {
            prefixSumArray[j] += offset;
        }
    }

    printf("Prefix Sum Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", prefixSumArray[i]);
    }

    return 0;
}
