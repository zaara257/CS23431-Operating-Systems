#include <stdio.h>

/**
 * BEST FIT MEMORY MANAGEMENT
 * 
 * Logic: This algorithm searches for the smallest block that is 
 * large enough to accommodate the process. This minimizes the 
 * "leftover" space (fragmentation) in the block.
 */

int main() {
    int m, n;

    // ==========================================
    // 1. INPUT NUMBER OF MEMORY BLOCKS
    // ==========================================
    // This defines how many separate partitions 
    // of memory are available for use.
    printf("Enter number of memory blocks: ");
    scanf("%d", &m);

    // ==========================================
    // 2. DECLARING BLOCK ARRAYS
    // ==========================================
    int blockSize[m];   // Stores the current/remaining size of each block
    int original[m];    // Stores the original size for final display
    int allocation[m];  // Tracks which block is used (optional for tracking)

    // ==========================================
    // 3. INPUT BLOCK SIZES
    // ==========================================
    // Example: 100, 500, 200, 300, 600
    printf("Enter size of each block:\n");
    for(int i = 0; i < m; i++) {
        printf("Block %d size: ", i + 1);
        scanf("%d", &blockSize[i]);
        
        /* 
           Save original block size because blockSize[] 
           will be reduced as memory is allocated.
        */
        original[i] = blockSize[i];
    }

    // ==========================================
    // 4. INPUT NUMBER OF PROCESSES
    // ==========================================
    // This defines how many programs are 
    // requesting a spot in memory.
    printf("\nEnter number of processes: ");
    scanf("%d", &n);

    // ==========================================
    // 5. DECLARING PROCESS ARRAY
    // ==========================================
    int processSize[n];

    // ==========================================
    // 6. INPUT PROCESS SIZES
    // ==========================================
    // Example: 212, 417, 112, 426
    printf("Enter size of each process:\n");
    for(int i = 0; i < n; i++) {
        printf("Process %d size: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    printf("\n--- Allocation Results ---\n");

    // ==========================================
    // 7. BEST FIT ALGORITHM STARTS
    // ==========================================
    /*
      Best Fit Strategy:
      - For each process, scan EVERY memory block.
      - Find the block that fits the process AND results
        in the smallest possible leftover space.
    */

    for(int i = 0; i < n; i++) {
        
        // bestIndex stores the index of the best suitable block
        // -1 means no suitable block has been found yet
        int bestIndex = -1;

        // ==============================
        // SEARCH ALL BLOCKS
        // ==============================
        for(int j = 0; j < m; j++) {
            
            /* Check if the current block is large enough for the process */
            if(blockSize[j] >= processSize[i]) {
                
                /*
                  Select this block if:
                  1. It's the first fitting block we found (bestIndex == -1)
                  2. OR it's smaller than the previous 'best' block found.
                  (This ensures we find the "tightest" fit).
                */
                if(bestIndex == -1 || blockSize[j] < blockSize[bestIndex]) {
                    bestIndex = j;
                }
            }
        }

        // ==========================================
        // 8. IF BEST BLOCK FOUND
        // ==========================================
        if(bestIndex != -1) {
            
            /*
              Internal Fragmentation:
              The leftover space inside the block after the 
              process takes what it needs.
            */
            int fragment = blockSize[bestIndex] - processSize[i];

            printf("Process %d (%d) -> Block %d (%d) | Fragment: %d\n",
                   i + 1, processSize[i], bestIndex + 1,
                   original[bestIndex], fragment);

            /*
              Reduce the current block size.
              The remaining memory is still available 
              for other processes in this simulation.
            */
            blockSize[bestIndex] -= processSize[i];
        }

        // ==========================================
        // 9. IF NO BLOCK FOUND
        // ==========================================
        else {
            printf("Process %d (%d) -> Not Allocated (Insufficient Memory)\n",
                   i + 1, processSize[i]);
        }
    }

    return 0;
}
