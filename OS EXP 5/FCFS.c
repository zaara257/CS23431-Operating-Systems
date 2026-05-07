#include <stdio.h>

int main()
{
    int n; // number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Arrays to store process information
    int AT[n];  // Arrival Time of each process
    int BT[n];  // Burst Time (CPU execution time required)
    int CT[n];  // Completion Time
    int TAT[n]; // Turnaround Time
    int WT[n];  // Waiting Time

    int i;

    // ==============================
    // INPUT SECTION
    // ==============================
    for(i = 0; i < n; i++)
    {
        printf("Enter Arrival Time and Burst Time for P%d: ", i+1);
        scanf("%d %d", &AT[i], &BT[i]);
    }

    /*
    FCFS executes processes in the order they arrive.

    Example timeline:

    P1 AT=0 BT=3
    P2 AT=1 BT=4
    P3 AT=2 BT=2

    CPU timeline:

    0----3----7----9
      P1   P2   P3
    */

    // ==============================
    // COMPLETION TIME CALCULATION
    // ==============================

    // First process finishes at:
    // arrival time + burst time
    CT[0] = AT[0] + BT[0];

    /*
    Example:

    P1 arrives at 0
    executes for 3 units

    CT1 = 0 + 3 = 3
    */

    for(i = 1; i < n; i++)
    {
        /*
        Two cases are possible:

        Case 1: CPU is idle before process arrives
        Example:
        previous CT = 3
        next process AT = 5

        CPU waits from 3 → 5

        Case 2: Process already waiting
        Example:
        previous CT = 3
        next process AT = 1

        process already waiting in queue
        */

        if(CT[i-1] < AT[i])
        {
            // CPU was idle until this process arrived
            CT[i] = AT[i] + BT[i];
        }
        else
        {
            // process already waiting in ready queue
            CT[i] = CT[i-1] + BT[i];
        }
    }

    /*
    Visual Example

    P1 AT=0 BT=3
    P2 AT=1 BT=4
    P3 AT=2 BT=2

    Step1:
    CT1 = 0+3 = 3

    Step2:
    CT2 = 3+4 = 7

    Step3:
    CT3 = 7+2 = 9
    */

    float totalTAT = 0;
    float totalWT = 0;

    // ==============================
    // TAT AND WT CALCULATION
    // ==============================

    for(i = 0; i < n; i++)
    {
        /*
        Turnaround Time

        Total time spent in the system

        TAT = Completion Time - Arrival Time
        */
        TAT[i] = CT[i] - AT[i];

        /*
        Waiting Time

        time spent waiting in the ready queue

        WT = TAT - Burst Time
        */
        WT[i] = TAT[i] - BT[i];

        totalTAT += TAT[i];
        totalWT += WT[i];
    }

    printf("\nAverage Turnaround Time: %.2f\n", totalTAT/n);
    printf("Average Waiting Time: %.2f\n", totalWT/n);

    return 0;
}
