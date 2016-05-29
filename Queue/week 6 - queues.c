/*
    Week 6: Queues
*/


#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

#define MIN_QUEUE_SIZE 5
#define MAX_QUEUE_SIZE 100



int main ()
{
    int opselect, num;
    
    Queue myQueue;
    int numOfElements;
    
    printf("Please enter the size of queue: ");
    scanf("%d",&numOfElements);
    
    myQueue = createQueue (numOfElements);
    
    while (1)
    {
        printf("\nSelect an operation:\n\t1. Enqueue\n\t2. Dequeue\n\t3. Show the front of queue\n\t4. Show the rear of queue\n\nSELECTION: ");
        scanf("%d",&opselect);
        
        switch (opselect)
        {
             case 1:
                  printf("Enter a number to enqueue: ");
                  scanf("%d",&num);
                  Enqueue(num,myQueue);
                  DisplayQueue(myQueue);
                  break;
                  
             case 2:
                  Dequeue(myQueue);
                  DisplayQueue(myQueue);
                  break;  
                  
             case 3:
                  printf("Front of Queue: %d\n",FrontOfQueue (myQueue));
                  break;
                  
             case 4:
                  printf("Rear of Queue: %d\n",RearOfQueue (myQueue));
                  break;
                  
             default:
                  printf("You should enter an option from menu!\n");
                  break;
               
        }    
    }
    system("pause");
    return 0;
}

