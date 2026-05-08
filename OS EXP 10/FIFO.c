// FIFO Page Replacement Algorithm

#include <stdio.h>

// Define a maximum limit to avoid the "constant value" error
#define MAX 100

int main() {

    int n, frames;

    // ==============================
    // INPUT NUMBER OF PAGES
    // ==============================

    printf("Enter number of pages in reference string: \n");
    scanf("%d", &n);

    /*
    Example:
    n = 7 pages
    Reference String: 1 3 0 3 5 6 3
    */

    // ==============================
    // DECLARE REFERENCE STRING ARRAY
    // ==============================
    // FIX: Using a fixed maximum size instead of a variable
    int ref[MAX];

    // ==============================
    // INPUT REFERENCE STRING
    // ==============================

    printf("Enter the reference string: \n");

    for(int i = 0; i < n; i++) {
        scanf("%d", &ref[i]);
    }

    // ==============================
    // INPUT NUMBER OF FRAMES
    // ==============================

    printf("Enter number of frames: \n");
    scanf("%d", &frames);

    /*
    Frames = Number of memory slots available
    Example: frames = 3
    */

    // ==============================
    // DECLARE FRAME ARRAY
    // ==============================
    // FIX: Using a fixed maximum size instead of a variable
    int frame[MAX];

    // Initialize frames as empty (-1)
    for(int i = 0; i < frames; i++) {
        frame[i] = -1;
    }

    // ==============================
    // FIFO POINTERS AND COUNTERS
    // ==============================

    int front = 0;   // points to the oldest page in frames
    int faults = 0;  // counts page faults
    int hits = 0;    // counts page hits

    // ==============================
    // FIFO PAGE REPLACEMENT LOOP
    // ==============================

    for(int i = 0; i < n; i++) {

        int found = 0; // flag to check if page is already in frame

        // ==============================
        // CHECK FOR PAGE HIT
        // ==============================

        for(int j = 0; j < frames; j++) {

            if(frame[j] == ref[i]) {

                /*
                Page is already in memory
                → HIT
                */

                found = 1;
                hits++;
                break;
            }
        }

        // ==============================
        // PAGE FAULT HANDLING
        // ==============================

        if(!found) {

            /*
            Page is not in memory → FAULT

            FIFO Replacement:

            - Replace the oldest page (pointed by `front`)
            - Move `front` to next frame cyclically
            */

            frame[front] = ref[i];
            front = (front + 1) % frames;

            faults++;
        }
    }

    // ==============================
    // FINAL OUTPUT
    // ==============================

    printf("\nTotal Page Faults: %d\n", faults);
    printf("Total Page Hits: %d\n", hits);

    return 0;
}
