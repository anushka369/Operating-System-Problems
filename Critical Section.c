#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#define NUM_THREADS 2 // Number of threads (2 processes)

int turn;
bool flag[NUM_THREADS] = {false, false}; // Flag array for each process

// Function for entering the critical section
void enter_critical_section(int i, int j)
{
    flag[i] = true;    // Process i wants to enter the critical section
    turn = j;          // Give turn to the other process

    while (flag[j] && turn == j)
    {
        // Busy wait: Process i waits if process j is in critical section and turn is j
    }
}

// Function for leaving the critical section
void leave_critical_section(int i)
{
    flag[i] = false;  // Process i leaves the critical section
}

// Critical section code (replace with actual work)
void critical_section(int i)
{
    printf("Process %d is in the critical section\n", i);
    sleep(1); // Simulate work by sleeping
}

// Remainder section code (replace with actual work)
void remainder_section(int i)
{
    printf("Process %d is in the remainder section\n", i);
    sleep(1); // Simulate work by sleeping
}

// Function executed by each process (thread)
void* process(void* arg)
{
    int i = *(int*)arg;            // Current process id (i = 0 or 1)
    int j = (i + 1) % NUM_THREADS; // The other process (j = 1 or 0)
    
    while (true)
    {
        enter_critical_section(i, j); // Try to enter the critical section
        critical_section(i);          // Perform work in the critical section
        leave_critical_section(i);    // Exit the critical section        
        remainder_section(i);         // Perform work in the remainder section
    }
    
    return NULL;
}

int main()
{
    pthread_t threads[NUM_THREADS]; // Thread IDs for each process
    int thread_ids[NUM_THREADS] = {0, 1}; // IDs for each process

    // Create threads for each process
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, process, &thread_ids[i]);
    }

    // Wait for the threads to finish (infinite loop in this case)
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
