// sender

#include <stdio.h>      // for printf, scanf
#include <sys/ipc.h>    // for key_t
#include <sys/shm.h>    // for shared memory functions
#include <string.h>     // for string operations

int main() {
    key_t key = 1234;   // Unique key to identify shared memory
    int shmid;          // Variable to store shared memory ID

    // Create shared memory segment of size 1024 bytes
    // 0666 = read/write permission for all users
    // IPC_CREAT = create memory if it doesn't exist
    shmid = shmget(key, 1024, 0666 | IPC_CREAT); // Create

    // Attach shared memory to this process
    // Returns pointer to the shared memory
    char *str = (char*) shmat(shmid, (void*)0, 0); // Attach

    printf("Enter message: ");

    // Read a full line (including spaces) and store directly in shared memory
    scanf(" %[^\n]", str);

    // Print the data written into shared memory
    printf("Data written to shared memory: %s\n", str);

    return 0;   // End program
}
