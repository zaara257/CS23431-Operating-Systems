// Producer Consumer

#include <stdio.h>
#include <stdlib.h>

int mutex = 1, full = 0, empty = 5, x = 0;

int wait(int s)
{
    return --s;
}

int signal(int s)
{
    return ++s;
}

void producer()
{
    mutex = wait(mutex);

    empty = wait(empty);
    full = signal(full);

    x++;
    printf("\nProducer produces item %d", x);

    mutex = signal(mutex);
}

void consumer()
{
    mutex = wait(mutex);

    full = wait(full);
    empty = signal(empty);

    printf("\nConsumer consumes item %d", x);
    x--;

    mutex = signal(mutex);
}

int main()
{
    int n;

    printf("\n----- Producer Consumer Problem -----");
    printf("\n1. Producer");
    printf("\n2. Consumer");
    printf("\n3. Exit");

    while(1)
    {
        printf("\nEnter your choice: ");
        scanf("%d",&n);

        switch(n)
        {
            case 1:
                if(mutex==1 && empty!=0)
                {
                    producer();
                }
                else
                {
                    printf("\nBuffer is full!! Producer cannot produce.");
                }
                break;

            case 2:
                if(mutex==1 && full!=0)
                {
                    consumer();
                }
                else
                {
                    printf("\nBuffer is empty!! Consumer cannot consume.");
                }
                break;

            case 3:
                printf("\nExiting program...");
                printf("\nFinal buffer items produced: %d\n", x);
                exit(0);

            default:
                printf("\nInvalid choice. Try again.");
        }
    }

    return 0;
}
