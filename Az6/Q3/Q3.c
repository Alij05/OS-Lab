#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


typedef struct {
    int *inputArray;
    int *partialSumArray;
    int startIndex;
    int endIndex;
} ThreadArguments;

void* calculatePartialSum(void* args) {
    ThreadArguments* threadArgs = args;
    threadArgs->partialSumArray = malloc(sizeof(int) * (threadArgs->endIndex - threadArgs->startIndex));
    threadArgs->partialSumArray[0] = threadArgs->inputArray[threadArgs->startIndex];
    for (int i = threadArgs->startIndex + 1; i < threadArgs->endIndex; i++) {
        threadArgs->partialSumArray[i - threadArgs->startIndex] = 
            threadArgs->partialSumArray[i - threadArgs->startIndex - 1] + 
            threadArgs->inputArray[i];
    }
    pthread_exit(NULL);
}

int main() {
    int inputArray[10] = {1, 2, 1, 5, 0, 7, 3, 4, 2, 7};
    int midpoint = 10 / 2;

    ThreadArguments firstHalfArgs = {inputArray, NULL, 0, midpoint};
    ThreadArguments secondHalfArgs = {inputArray, NULL, midpoint, 10};

    pthread_t firstThread, secondThread;

    if (pthread_create(&firstThread, NULL, calculatePartialSum, &firstHalfArgs) != 0) {
        perror("Error creating the first thread");
        return 1;
    }
    if (pthread_create(&secondThread, NULL, calculatePartialSum, &secondHalfArgs) != 0) {
        perror("Error creating the second thread");
        return 1;
    }

    if (pthread_join(firstThread, NULL) != 0) {
        perror("Error joining the first thread");
        return 1;
    }
    if (pthread_join(secondThread, NULL) != 0) {
        perror("Error joining the second thread");
        return 1;
    }

    printf("Prefix sum for the first half of the array: ");
    for (int i = 0; i < midpoint; i++) {
        printf("%d ", firstHalfArgs.partialSumArray[i]);
    }
    printf("\n");

    printf("Prefix sum for the second half of the array: ");
    for (int i = 0; i < 10 - midpoint; i++) {
        printf("%d ", secondHalfArgs.partialSumArray[i]);
    }
    printf("\n");

    free(firstHalfArgs.partialSumArray);
    free(secondHalfArgs.partialSumArray);

    return 0;
}
