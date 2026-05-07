// LRU Page Replacement Algorithm

#include <stdio.h>

// FIX: Define a maximum size for the arrays to avoid "constant value" error
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
    n = 5 pages
    Reference String: 1 2 3 4 5
    */

    // ==============================
    // DECLARE REFERENCE STRING ARRAY
    // ==============================
    // FIX: Using a fixed constant size
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
    frames = number of memory slots available
    Example: frames = 3
    */

    // ==============================
    // DECLARE FRAME AND TIME ARRAYS
    // ==============================
    // FIX: Using fixed constant sizes
    int frame[MAX];    // stores pages in memory
    int time[MAX];     // stores “last used time” for each frame

    // ==============================
    // INITIALIZATION
    // ==============================

    for(int i = 0; i < frames; i++) {
        frame[i] = -1;  // empty frame
        time[i] = 0;    // time = 0 initially
    }

    int faults = 0;    // counts page faults
    int hits = 0;      // counts page hits
    int counter = 0;   // global counter to track page usage

    // ==============================
    // LRU PAGE REPLACEMENT LOOP
    // ==============================

    for(int i = 0; i < n; i++) {

        int found = 0;  // flag to check if page is already in memory

        // ==============================
        // CHECK FOR PAGE HIT
        // ==============================

        for(int j = 0; j < frames; j++) {
            if(frame[j] == ref[i]) {

                /*
                Page is already in memory → HIT
                Update time of this frame to current counter
                */

                hits++;
                counter++;
                time[j] = counter;  // most recently used
                found = 1;
                break;
            }
        }

        // ==============================
        // PAGE FAULT HANDLING
        // ==============================

        if(!found) {

            /*
            Page is not in memory → FAULT

            Find **Least Recently Used (LRU)** frame:
            - Frame with smallest `time[]` value
            - Replace that frame with new page
            */

            int lruIndex = 0;  // assume frame 0 is LRU initially

            for(int j = 1; j < frames; j++) {
                if(time[j] < time[lruIndex]) {
                    lruIndex = j;
                }
            }

            counter++;                // increment global time
            frame[lruIndex] = ref[i]; // load new page
            time[lruIndex] = counter; // update its usage time

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
