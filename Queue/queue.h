/*
    Queue Header File
*/
#include <stdio.h>
#include <stdlib.h>

#define MIN_QUEUE_SIZE 5
#define MAX_QUEUE_SIZE 100


struct QueueRecord
{
	int Capacity;
	int Front;
	int Rear;
	int Size;
	int *Array;
};

typedef struct QueueRecord *Queue;

Queue createQueue (int);
void makeEmptyQueue (Queue);
int IsFullQueue (Queue);
int IsEmptyQueue (Queue);
void DisplayQueue (Queue);
int Succ (int, Queue); 
void Enqueue (int, Queue);
int Dequeue (Queue);
int FrontOfQueue (Queue);
int RearOfQueue (Queue);



Queue createQueue (int maxElements)
{
    Queue q;
    
    if (maxElements > MAX_QUEUE_SIZE)
    {
         printf("Queue size is too large!\n");             
         return NULL;   
    }
    else if (maxElements < MIN_QUEUE_SIZE)
    {
         printf("Queue size is too small!\n");             
         return NULL;   
    }
    else
    {
        q = (Queue) malloc(sizeof(struct QueueRecord));
        
        if (q == NULL)
        {
             printf("Error in dynamic memory allocation!\n");      
             return NULL;
        }
        else
        {
             q->Array = malloc(sizeof(int)*maxElements);
             if (q->Array == NULL)
             {
                  printf("Error in dynamic memory allocation!\n");      
                  return NULL;
             }
             else
             {
                  q->Capacity = maxElements;
                  makeEmptyQueue (q);
                  return q;
             }
        }
    }
}


void makeEmptyQueue (Queue q)
{
    q->Size = 0;
    q->Front = 1;
    q->Rear = 0;
}

int IsFullQueue (Queue q)
{
    if (q->Size == q->Capacity)
    return 1;
    
    else
    return 0;
}

int IsEmptyQueue (Queue q)
{
    if (q->Size == 0)
    return 1;

    else
    return 0;
}



void Enqueue (int x, Queue q)
{
    if (IsFullQueue(q))
    {
         printf("Queue is full!\n");
    }
    else
    {
         q->Size++;
         q->Rear = Succ(q->Rear,q);
         q->Array[q->Rear] = x;
    } 
}



int Dequeue (Queue q)
{
    int value;
    
    if (!IsEmptyQueue(q))
    {
         value = q->Array[q->Front];
         q->Size--;
         q->Front = Succ(q->Front, q);
         return value;
    }
    else
    {
         printf("Queue is empty!\n");
         return -1;
    }
}


void DisplayQueue (Queue q)
{
    int i, pos;
    
    printf("\nFront: %d\n",q->Front);
    printf("Rear: %d\n",q->Rear);
    pos = q->Front; 
    printf("\nQueue Content:\n");
    
    for (i = 0; i < q->Size; i++)
    {
         printf("\t--> %d\n", q->Array[pos]);
         pos = Succ(pos, q);
    }
}


int Succ (int value, Queue q)
{
    value++;
    
    if (value == q->Capacity)
    value = 0;
    
    
    return value;
}


int FrontOfQueue (Queue q)
{
    if (!IsEmptyQueue(q))
    return q->Array[q->Front];
    
    else
    {
        printf("Queue is full!\n");
        return -1;
    }
}



int RearOfQueue (Queue q)
{
    if (!IsEmptyQueue(q))
    return q->Array[q->Rear];
    
    else
    {
        printf("Queue is empty!\n");
        return -1;
    }
}













