# lab 3


### Defining Varables
Shared Variables:
- buffer: to store the data to be sent (1-buffer)
- N - user thread; M - kernel Thread
- variable for packet counter to check # available packets

Synchronization Primites:

Mutex(pthread_mutex_t): for mutual exclusion for accessing shared buffer
Conditonal Varianbles: `pthread_cond_t` for signal threads when buffer is avaialble


## Task 2: Define user thread function
:
The user thread tries to add a packet to buffer.
- If buffer already has the data i.e., `packets_avaolanle !=0`, it waits for the packet to be consumed, going to sleep(`pthread_cond_wait`)
- When buffer is free, it adds packet (in this case, just its rhreadID) and signal





