#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


typedef struct {
    int *inputArray;
    int *prefixSumArray;
    int startIndex;
    int endIndex;
    int previousSum;
} PrefixSumThreadArgs;

void* calculatePrefixSum(void* args) {
    PrefixSumThreadArgs* threadArgs = (PrefixSumThreadArgs*)args;
    threadArgs->prefixSumArray = malloc(sizeof(int) * (threadArgs->endIndex - threadArgs->startIndex));
    
    if (!threadArgs->prefixSumArray) {
        perror("Memory allocation failed");
        pthread_exit(NULL);
    }
    
    threadArgs->prefixSumArray[0] = threadArgs->inputArray[threadArgs->startIndex] + threadArgs->previousSum;
    
    for (int i = threadArgs->startIndex + 1; i < threadArgs->endIndex; i++) {
        threadArgs->prefixSumArray[i - threadArgs->startIndex] = threadArgs->prefixSumArray[i - threadArgs->startIndex - 1] + threadArgs->inputArray[i];
    }
    
    pthread_exit(NULL);
}

int main() {
    int inputArray[10] = {1, 2, 1, 5, 0, 7, 3, 4, 2, 7};
    int halfSize = 10 / 2;
    
    PrefixSumThreadArgs threadArgs1 = {inputArray, NULL, 0, halfSize, 0};
    PrefixSumThreadArgs threadArgs2 = {inputArray, NULL, halfSize, 10, 0};
    
    pthread_t thread1, thread2;
    
    if (pthread_create(&thread1, NULL, calculatePrefixSum, &threadArgs1) != 0) {
        perror("Failed to create thread1");
        return 1;
    }
    
    if (pthread_join(thread1, NULL) != 0) {
        perror("Failed to join thread1");
        return 1;
    }
    
    threadArgs2.previousSum = threadArgs1.prefixSumArray[halfSize - 1];
    
    if (pthread_create(&thread2, NULL, calculatePrefixSum, &threadArgs2) != 0) {
        perror("Failed to create thread2");
        return 1;
    }
    
    if (pthread_join(thread2, NULL) != 0) {
        perror("Failed to join thread2");
        return 1;
    }
    
    printf("Prefix Sum of First Half: ");
    for (int i = 0; i < halfSize; i++) {
        printf("%d ", threadArgs1.prefixSumArray[i]);
    }
    printf("\n");
    
    printf("Prefix Sum of Second Half: ");
    for (int i = 0; i < 10 - halfSize; i++) {
        printf("%d ", threadArgs2.prefixSumArray[i]);
    }
    printf("\n");
    
    free(threadArgs1.prefixSumArray);
    free(threadArgs2.prefixSumArray);
    
    return 0;
}
