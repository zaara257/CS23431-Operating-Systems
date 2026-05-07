//receiver

#include <stdio.h>      // for printf
#include <sys/ipc.h>    // for key_t
#include <sys/shm.h>    // for shared memory functions

int main() {
    key_t key = 1234;   // Same key used by sender
    int shmid;          // Variable to store shared memory ID

    // Access existing shared memory
    // No IPC_CREAT → it must already exist
    shmid = shmget(key, 1024, 0666); // Get

    // Attach shared memory to this process
    char *str = (char*) shmat(shmid, (void*)0, 0); // Attach

    // Read and print data from shared memory
    printf("Data read from shared memory: %s\n", str);

    // Detach shared memory after use
    shmdt(str);

    return 0;   // End program
}
