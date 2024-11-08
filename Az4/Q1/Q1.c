#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <time.h>

// Define the size of shared memory to store one integer and one flag
#define SHM_SIZE (2 * sizeof(int))


// Producer function
void generate_numbers(int *number, int *flag) {
    srand(time(NULL));
    for (int i = 0; i < 20; i++) {
        
        // Wait until the consumer has consumed the previous number (avoiding busy-waiting)
        while (*flag == 1) {
            usleep(100);
        }

        // Generate a random number
        *number = rand() % 100;
	//mark it as ready for consumption
        *flag = 1;
        printf("Number Produced: %d\n", *number);
    }
}


// Consumer function
int consume_numbers(int *number, int *flag) {
    int total_sum = 0;
    for (int i = 0; i < 20; i++) {
        
        // Wait until the producer has produced a number (avoiding busy-waiting)
        while (*flag == 0) {
            usleep(100);
        }

        // Mark the number as consumed
        *flag = 0;
        printf("Number Consumed\n");
	// Update the running total sum
        total_sum += *number; 
    }

    return total_sum;
}



int main() {
    // Create a shared memory segment
    int memory_id = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666);
    if (memory_id == -1) {
        perror("Shared memory allocation failed");
        exit(1);
    }

    // Attach shared memory to the process
    int *shared_memory = (int *) shmat(memory_id, NULL, 0);
    if (shared_memory == (int *) -1) {
        perror("Shared memory attachment failed");
        exit(1);
    }

    // Pointers to shared memory for the number and flag (1 means ready, 0 means not ready)
    int *number = &shared_memory[0];
    int *flag = &shared_memory[1];

    // Initially, no number is written, so flag is set to 0
    *flag = 0;

    // Create a new process using fork()
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process: Consumer
        int total_sum = consume_numbers(number, flag);

        // Detach the shared memory from the child process
        shmdt(shared_memory);

        // Print the total sum
        printf("Total Sum: %d\n", total_sum);

        // Exit the child process
        exit(0);
    } else {
        // Parent process: Producer
        generate_numbers(number, flag);

        // Wait for the consumer process to finish
        wait(NULL);

        // Detach the shared memory from the parent process
        shmdt(shared_memory);

        // Remove the shared memory segment
        shmctl(memory_id, IPC_RMID, NULL);
    }

    return 0;
}
