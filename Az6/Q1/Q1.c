#include <stdio.h>

void computePrefixSumSerial(int inputArray[], int size, int prefixSumArray[]) {
    prefixSumArray[0] = inputArray[0];
    for (int i = 1; i < size; i++) {
        prefixSumArray[i] = prefixSumArray[i - 1] + inputArray[i];
    }
}

int main() {
    int inputArray[] = {1, 2, 1, 5, 0, 7, 3, 4, 2, 7};
    int size = sizeof(inputArray) / sizeof(inputArray[0]);
    int prefixSumArray[size];

    computePrefixSumSerial(inputArray, size, prefixSumArray);

    printf("Prefix Sum Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", prefixSumArray[i]);
    }
    printf("\n");

    return 0;
}

