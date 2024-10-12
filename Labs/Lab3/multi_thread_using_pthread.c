#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Global Variables
int buffer = 0; // 1-item buffer to hold packet id
int available_packets; // Tracks how many packets are available
int X, N, M; // X = number of packets, N = number of user threads, M = number of kernel threads
int current_turn = 1; // Keeps track of which user thread's turn it is
int threads_served = 0; // Number of user threads served

// Synchronization Primitives
pthread_mutex_t buffer_mutex; // Mutex for shared buffer access
pthread_cond_t packet_available_cond; // Conditional variable to signal that a packet is available
pthread_cond_t packet_consumed_cond; // Conditional variable to signal that a packet has been consumed
pthread_cond_t user_turn_cond; // To signal the turn of the user threads

// Function to add random delay
void add_random_delay(int my_id) {
    usleep(10000 + 10000 * (my_id * 1000 % 5));
}

// User Thread Function
void* user_thread(void* arg) {
    int my_id = *(int*)arg;
    free(arg);

    pthread_mutex_lock(&buffer_mutex);
    while (threads_served < N) {
        // Wait if it's not this thread's turn or no packets are available
        while (available_packets == 0 || current_turn != my_id) {
            printf("No packet available or not my turn to produce, user level thread %d going to sleep\n", my_id);
            pthread_cond_wait(&user_turn_cond, &buffer_mutex);
        }

        // It's this thread's turn, and a packet is available
        add_random_delay(my_id);
        printf("User level thread %d is going to put data in a packet\n", my_id);
        
        buffer = my_id; // Simulate data in the packet
        available_packets--; // Decrease packet count
        current_turn++; // Move to the next user thread's turn
        if (current_turn > N) {
            current_turn = 1; // Loop back to thread 1
        }
        threads_served++; // Increase the served thread count

        pthread_cond_signal(&packet_available_cond); // Notify kernel thread a packet is ready
        pthread_mutex_unlock(&buffer_mutex);
        return NULL;
    }

    pthread_mutex_unlock(&buffer_mutex);
    return NULL;
}

// Kernel Thread Function
void* kernel_thread(void* arg) {
    int kernel_id = *(int*)arg;
    free(arg);

    while (1) {
        pthread_mutex_lock(&buffer_mutex);

        // Wait until a packet is available to process
        while (available_packets == X) { 
            if (threads_served >= N) {
                pthread_mutex_unlock(&buffer_mutex);
                return NULL; // All user threads served, exit
            }

            printf("No data available, Going to sleep kernel thread %d\n", kernel_id);
            pthread_cond_wait(&packet_available_cond, &buffer_mutex);
        }

        // Process the packet
        printf("user thread %d getting served\n", buffer);
        buffer = 0;
        available_packets++; // Increase available packet count

        // Signal user threads that a packet is available
        pthread_cond_broadcast(&user_turn_cond);

        pthread_mutex_unlock(&buffer_mutex);
    }
    return NULL;
}

// Main Function
int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Usage: %s <X> <N> <M>\n", argv[0]);
        exit(1);
    }

    X = atoi(argv[1]); // Number of packets
    N = atoi(argv[2]); // Number of user threads
    M = atoi(argv[3]); // Number of kernel threads
    available_packets = X; // All packets are initially available

    pthread_t user_threads[N];
    pthread_t kernel_threads[M];

    pthread_mutex_init(&buffer_mutex, NULL);
    pthread_cond_init(&packet_available_cond, NULL);
    pthread_cond_init(&packet_consumed_cond, NULL);
    pthread_cond_init(&user_turn_cond, NULL);

    // Create user threads
    for (int i = 0; i < N; i++) {
        int* id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&user_threads[i], NULL, user_thread, id);
    }

    // Create kernel threads
    for (int i = 0; i < M; i++) {
        int* id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&kernel_threads[i], NULL, kernel_thread, id);
    }

    // Join user threads
    for (int i = 0; i < N; i++) {
        pthread_join(user_threads[i], NULL);
    }

    // Join kernel threads
    for (int i = 0; i < M; i++) {
        pthread_join(kernel_threads[i], NULL);
    }

    // Clean up
    pthread_mutex_destroy(&buffer_mutex);
    pthread_cond_destroy(&packet_available_cond);
    pthread_cond_destroy(&packet_consumed_cond);
    pthread_cond_destroy(&user_turn_cond);

    return 0;
}
