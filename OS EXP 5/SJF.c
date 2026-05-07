#include <stdio.h>

int main()
{
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int AT[n];      // Arrival Time
    int BT[n];      // Burst Time
    int CT[n];      // Completion Time
    int TAT[n];     // Turnaround Time
    int WT[n];      // Waiting Time
    int visited[n]; // marks if process is finished

    int i;

    for(i=0;i<n;i++)
    {
        printf("Enter Arrival Time and Burst Time for P%d: ", i+1);
        scanf("%d %d",&AT[i],&BT[i]);

        visited[i] = 0; // initially no process is completed
    }

    /*
    SJF Logic:

    At any time:
    choose the process with SMALLEST burst time
    among processes that have already arrived.

    Example:

    P1 AT=0 BT=6
    P2 AT=2 BT=2
    P3 AT=4 BT=4
    P4 AT=6 BT=1
    */

    int time = 0;      // current CPU time
    int completed = 0; // number of completed processes
    int min;           // index of shortest job

    /*
    CPU keeps running until all processes finish
    */
    while(completed < n)
    {
        min = -1;

        /*
        Search all processes to find
        the shortest job that has arrived
        */

        for(i=0;i<n;i++)
        {
            /*
            AT[i] <= time
            means process has already arrived
            visited[i]==0
            means process not completed
            */

            if(AT[i] <= time && visited[i]==0)
            {
                /*
                If no process selected yet
                OR
                current process has smaller burst time
                */

                if(min == -1 || BT[i] < BT[min])
                {
                    min = i;
                }
            }
        }

        /*
        If no process has arrived yet
        CPU stays idle
        */

        if(min == -1)
        {
            time++; // move time forward
        }
        else
        {
            /*
            Execute selected shortest job
            */

            time += BT[min];

            CT[min] = time;

            visited[min] = 1;

            completed++;
        }
    }

    /*
    Example timeline

    P1 AT0 BT6
    P2 AT2 BT2
    P3 AT4 BT4
    P4 AT6 BT1

    Timeline

    0------6------7------9------13
       P1     P4     P2      P3
    */

    float totalTAT=0;
    float totalWT=0;

    for(i=0;i<n;i++)
    {
        TAT[i] = CT[i] - AT[i];
        WT[i] = TAT[i] - BT[i];

        totalTAT += TAT[i];
        totalWT += WT[i];
    }

    printf("\nAverage Turnaround Time = %.2f\n", totalTAT/n);
    printf("Average Waiting Time = %.2f\n", totalWT/n);

    return 0;
}
