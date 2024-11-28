#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printHistogram(int* hist) {
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < hist[i]; j++) {
            printf("*");
        }
        printf("\n");
    }
}
void printNumbers(int * hist){
    printf("hist : ");
    for (int i = 0; i < 25; i++)
    {
        printf("%d ", hist[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    int num_samples = strtol(argv[1], NULL, 10);
    if (num_samples <= 0) return 0;
    clock_t start = clock();
    int hist[25] ={0};
    
    int counter = 0;
    srand(time(NULL));
    for (int i = 0; i < num_samples; i++) {
        counter = 0;
        for (int j = 0; j < 12; j++)
        {        
            int random_num = rand() % 101;
            if (random_num >= 49) 
                counter++;
            else 
                counter--;
        }
            hist[counter + 12]++;
    }
    clock_t stop = clock();
    double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
    printf("Time : %f ms\n", elapsed);
    
    printNumbers(hist);
    printHistogram(hist);
    return 0;
}
