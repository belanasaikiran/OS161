#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define QUEUE_SIZE 30 // This will vary

pthread_mutex_t mutex;
pthread_cond_t cond_producer, cond_consumer;
int queue[QUEUE_SIZE]; // Shared queue
int count = 0; // Number of items in queue
int items_produced = 0; // Number of items produced
int items_consumed = 0; // Number of items consumed

int producer_sleep_count[2] = {0, 0}; // Two producers, one counter for each
int consumer_sleep_count[2] = {0, 0}; // Two consumers, one counter for each

void *producer(void *arg) {
    int id = *((int *)arg); // Producer ID (0 or 1)
    while (items_produced < 500) {
        pthread_mutex_lock(&mutex);
        
        // Sleep if queue is full
        while (count == QUEUE_SIZE) {
            producer_sleep_count[id]++;
            pthread_cond_wait(&cond_producer, &mutex);
        }
        
        // Produce an item (for simplicity, assume an int)
        queue[count] = items_produced++;
        count++;
        
        // Signal to consumer that queue is not empty
        pthread_cond_signal(&cond_consumer);
        
        pthread_mutex_unlock(&mutex);
    }
}

void *consumer(void *arg) {
    int id = *((int *)arg); // Consumer ID (0 or 1)
    while (items_consumed < 500) {
        pthread_mutex_lock(&mutex);
        
        // Sleep if queue is empty
        while (count == 0) {
            consumer_sleep_count[id]++;
            pthread_cond_wait(&cond_consumer, &mutex);
        }
        
        // Consume an item
        int item = queue[--count];
        items_consumed++;
        
        // Signal to producer that queue is not full
        pthread_cond_signal(&cond_producer);
        
        pthread_mutex_unlock(&mutex);
    }
}

int main() {
    pthread_t producers[2], consumers[2];
    int producer_ids[2] = {0, 1}; // IDs for the producers
    int consumer_ids[2] = {0, 1}; // IDs for the consumers
    
    // Initialize mutex and condition variables
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_producer, NULL);
    pthread_cond_init(&cond_consumer, NULL);
    
    // Create 2 producer and 2 consumer threads
    for (int i = 0; i < 2; i++) {
        pthread_create(&producers[i], NULL, producer, &producer_ids[i]);
        pthread_create(&consumers[i], NULL, consumer, &consumer_ids[i]);
    }
    
    // Wait for all threads to finish
    for (int i = 0; i < 2; i++) {
        pthread_join(producers[i], NULL);
        pthread_join(consumers[i], NULL);
    }
    
    // Print final sleep counts
    printf("Producer 1 went to sleep %d times\n", producer_sleep_count[0]);
    printf("Producer 2 went to sleep %d times\n", producer_sleep_count[1]);
    printf("Consumer 1 went to sleep %d times\n", consumer_sleep_count[0]);
    printf("Consumer 2 went to sleep %d times\n", consumer_sleep_count[1]);

    return 0;
}
