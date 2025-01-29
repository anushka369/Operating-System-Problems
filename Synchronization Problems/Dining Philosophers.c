#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>

#define N 5 // Number of philosophers
#define THINKING 0
#define HUNGRY 1
#define EATING 2

int state[N];
sem_t mutex;
sem_t self[N];

// Function declarations
void test(int i);
void pickup(int i);
void putdown(int i);
void* philosopher(void* num);

// Pickup function
void pickup(int i)
{
    sem_wait(&mutex); // Entry section
    state[i] = HUNGRY;
    test(i); // Try to acquire chopsticks
    sem_post(&mutex); // Exit section
    sem_wait(&self[i]); // Block if unable to eat
}

// Putdown function
void putdown(int i)
{
    sem_wait(&mutex); // Entry section
    state[i] = THINKING;
    test((i + 4) % N); // Test left neighbor
    test((i + 1) % N); // Test right neighbor
    sem_post(&mutex); // Exit section
}

// Test function
void test(int i)
{
    if (state[i] == HUNGRY && 
        state[(i + 4) % N] != EATING && 
        state[(i + 1) % N] != EATING)
    {
        state[i] = EATING;
        sem_post(&self[i]); // Wake up philosopher
    }
}

// Philosopher's life cycle
void* philosopher(void* num)
{
    int i = *(int*)num;
    while (1)
    {
        // Thinking
        printf("Philosopher %d is THINKING\n", i);
        sleep(1);

        // Hungry and trying to pick up chopsticks
        pickup(i);

        // Eating
        printf("Philosopher %d is EATING\n", i);
        sleep(1);

        // Finished eating, put down chopsticks
        putdown(i);
    }
}

int main()
{
    int i;
    pthread_t tid[N];
    int phil[N] = { 0, 1, 2, 3, 4 };

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    for (i = 0; i < N; i++) 
    {
        sem_init(&self[i], 0, 0);
        state[i] = THINKING;
    }

    // Create philosopher threads
    for (i = 0; i < N; i++) 
    {
        pthread_create(&tid[i], NULL, philosopher, &phil[i]);
    }

    // Join threads
    for (i = 0; i < N; i++) 
    {
        pthread_join(tid[i], NULL);
    }
    return 0;
}
