#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int available_packets; // shared variable
int thread_index_for_next = 1;  // index of the next user thread
int user_served = 0; // number of users served
// N: number of user threads; X: number of packets; M: number of kernel threads
int X, N, M;

pthread_mutex_t mutex_lock; // mutex 
// condition variables for user and kernel threads
pthread_cond_t user_condition_var, kernel_condition_var; 

// function to add random delay - for user threads when they are going to put data in a packet
void add_random_delay(int my_id) {
   usleep(10000 + 10000 * (my_id * 1000 % 5));
}


// user thread function
void* user_thread(void* arg) {
    int my_id = *((int*)arg);

    pthread_mutex_lock(&mutex_lock); // lock the mutex

    // wait if not your turn or packets not available
    while (my_id != thread_index_for_next || available_packets <= 0) {
        printf("No packet available or not my turn to produce, user level thread %d going to sleep\n", my_id);
        pthread_cond_wait(&user_condition_var, &mutex_lock); // wait for signal
    }

    available_packets--; // decrement the available packets since user thread is going to put data in a packet
    printf("User level thread %d is going to put data in a packet\n", my_id);

   // call to add_random_delay
    add_random_delay(my_id);

    thread_index_for_next++; // incrementing the thread index for next user thread
    pthread_cond_broadcast(&kernel_condition_var); // signal to kernel threads
    pthread_mutex_unlock(&mutex_lock); // unlock the mutex

   pthread_exit((void*) 0); // exit the thread
}

// kernel thread function
void* kernel_thread(void* arg) {
    int kernel_id = *((int*)arg); // get the id of the kernel thread

    // loop until all users are served
    while (user_served < N) {
        pthread_mutex_lock(&mutex_lock); // lock the mutex

        // wait if packets are not available or all users are served
        while (available_packets == X && user_served < N) {
            printf("No data available, Going to sleep kernel thread %d\n", kernel_id);
            pthread_cond_wait(&kernel_condition_var, &mutex_lock);
        }

        // exit when all users are served
        if (user_served >= N) {
            pthread_mutex_unlock(&mutex_lock);
            break;
        }

        user_served++; // increment the user served
        printf("user thread %d getting served\n", user_served);
        available_packets++; // increment the available packets
        pthread_cond_broadcast(&user_condition_var); 
        pthread_mutex_unlock(&mutex_lock);
    }

    pthread_exit((void*) 0);
}



// Our Beloved Main Function
int main(int argc, char* argv[]) {


    if (argc != 4) { // check for correct number of arguments
        printf("Usage: %s <X> <N> <M>\n", argv[0]);
        exit(1); 
    }

    X = atoi(argv[1]); // number of packets
    N = atoi(argv[2]); // number of user threads
    M = atoi(argv[3]); // number of kernel threads

    available_packets = X;

    // array to store user threads and kernel threads
    pthread_t user_threads[N];
    pthread_t kernel_threads[M];

  // array to store user ids and kernel ids
    int user_ids[N];
    int kernel_ids[M];

    // initialize mutex and condition variables
    pthread_mutex_init(&mutex_lock, NULL);
    pthread_cond_init(&user_condition_var, NULL);
    pthread_cond_init(&kernel_condition_var, NULL);


    // create N user threads and M kernel threads
    for (int i = 0; i < N; i++) {
        user_ids[i] = i + 1;
        pthread_create(&user_threads[i], NULL, user_thread, &user_ids[i]);
    }
    for (int i = 0; i < M; i++) {
        kernel_ids[i] = i + 1;
        pthread_create(&kernel_threads[i], NULL, kernel_thread, &kernel_ids[i]);
    }


    // wait for all threads to finish
    for (int i = 0; i < N; i++) {
        pthread_join(user_threads[i], NULL);
    }
    for (int i = 0; i < M; i++) {
        pthread_join(kernel_threads[i], NULL);
    }



  // destroy mutex and condition variables
    pthread_mutex_destroy(&mutex_lock);
    pthread_cond_destroy(&user_condition_var);
    pthread_cond_destroy(&kernel_condition_var);
    pthread_exit(NULL);
}
