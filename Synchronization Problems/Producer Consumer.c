#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 10

// Define item structure
typedef struct 
{
    int value;
} item;

// Buffer and indices
item buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

// Mutex lock and condition variables
pthread_mutex_t mutex;
pthread_cond_t not_empty;
pthread_cond_t not_full;

// Function to produce items
void *producer(void *param)
{
    item next_produced;
    
    while (1)
    {
        // Produce an item
        next_produced.value = rand() % 100;
        printf("Produced: %d\n", next_produced.value);
        
        // Lock the buffer before accessing
        pthread_mutex_lock(&mutex);

        // Wait if the buffer is full
        while (((in + 1) % BUFFER_SIZE) == out)
        {
            pthread_cond_wait(&not_full, &mutex);
        }

        // Add the produced item to the buffer
        buffer[in] = next_produced;
        in = (in + 1) % BUFFER_SIZE;

        // Signal that the buffer is not empty anymore
        pthread_cond_signal(&not_empty);

        // Unlock the buffer
        pthread_mutex_unlock(&mutex);

        // Sleep for a while to simulate production time
        sleep(1);
    }
}

// Function to consume items
void *consumer(void *param)
{
    item next_consumed;
    
    while (1)
    {
        // Lock the buffer before accessing
        pthread_mutex_lock(&mutex);

        // Wait if the buffer is empty
        while (in == out)
        {
            pthread_cond_wait(&not_empty, &mutex);
        }

        // Consume the item from the buffer
        next_consumed = buffer[out];
        out = (out + 1) % BUFFER_SIZE;

        printf("Consumed: %d\n", next_consumed.value);

        // Signal that the buffer is not full anymore
        pthread_cond_signal(&not_full);

        // Unlock the buffer
        pthread_mutex_unlock(&mutex);

        // Sleep for a while to simulate consumption time
        sleep(1);
    }
}

int main()
{
    // Initialize mutex and condition variables
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&not_empty, NULL);
    pthread_cond_init(&not_full, NULL);

    // Declare threads
    pthread_t tid_producer, tid_consumer;

    // Create producer and consumer threads
    pthread_create(&tid_producer, NULL, producer, NULL);
    pthread_create(&tid_consumer, NULL, consumer, NULL);

    // Join threads (this will block the main function)
    pthread_join(tid_producer, NULL);
    pthread_join(tid_consumer, NULL);

    // Clean up
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&not_empty);
    pthread_cond_destroy(&not_full);

    return 0;
}
