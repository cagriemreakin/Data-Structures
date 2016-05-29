#include <stdio.h>
#include <stdlib.h>

/*  ClockQueue Header File */


struct clockNode
{
    int type;
	float clock;
	struct clockNode *next;
};



struct ClockRecord
{
	struct clockNode *front;
	struct clockNode *rear;
	int size;
};


typedef struct ClockRecord *ClockQueue;


ClockQueue CreateClockQueue ();
void MakeEmptyClockQueue (ClockQueue);
int ClockQueueSize (ClockQueue);
int FrontOfClockQueue (ClockQueue);
int RearOfClockQueue (ClockQueue);
int IsFullClockQueue (ClockQueue);
int IsEmptyClockQueue (ClockQueue);
void DisplayClockQueue (ClockQueue);
void InsertClock (ClockQueue, float, int);
void DequeueClock (ClockQueue);




ClockQueue CreateClockQueue()
{
	ClockQueue q;

    q = (struct ClockRecord *) malloc(sizeof(struct ClockRecord));
    if (q == NULL)
        printf("Out of memory space\n");
    else
        MakeEmptyClockQueue(q);
    return q;
}


void MakeEmptyClockQueue(ClockQueue q)
{
	q->size = 0;
	q->front = (struct clockNode *) malloc(sizeof(struct clockNode));
    if (q->front == NULL)
        printf("Out of memory space\n");
    else
    {
        q->front->next = NULL;
        q->rear = q->front;
    }
}


int IsEmptyClockQueue(ClockQueue q)
{
	return (q->size == 0);
}



int ClockQueueSize(ClockQueue q)
{
	return (q->size);
}


int IsFullClockQueue(ClockQueue q)
{
	return 0;
}


int FrontOfClockQueue(ClockQueue q)
{
    if (!IsEmptyClockQueue(q))
		return q->front->next->clock;
    else
    {
        printf("The queue is empty\n");
            return -1;
    }
}


int RearOfClockQueue(ClockQueue q)
{
	if (!IsEmptyClockQueue(q))
	    return q->rear->clock;
     else
     {
         printf("The queue is empty\n");
         return -1;
     }
}


void DisplayClockQueue(ClockQueue q)
{
    struct clockNode *p;

    p = q->front->next;
    printf("Event Queue:\n");

    while (p != NULL)
    {
        printf("Type: %d\t Clock: %.3f\n", p->type, p->clock);
        p = p->next;
    }
}


void InsertClock(ClockQueue q, float clock, int type)
{
   struct clockNode *newNode, *p;

   newNode = (struct clockNode*)malloc(sizeof(struct clockNode));
   if (newNode == NULL)
        printf("Out of memory!\n");

   p = (struct clockNode*)malloc(sizeof(struct clockNode));
   if (p == NULL)
        printf("Out of memory!\n");

         newNode->clock = clock;
         newNode->type = type;
         newNode->next = NULL;

         if (q->rear == NULL)
         {
              q->rear->next = newNode;
              q->size++;
         }

         else
         {
              p = q->rear;

              while ((p->next != NULL) && (p->next->clock <= clock))
              {
                  p = p->next;
              }

              newNode->next = p->next;
              p->next = newNode;
              q->size++;
         }
}


void DequeueClock(ClockQueue q)
{
    struct clockNode *remove;

    if (!IsEmptyClockQueue(q))
    {
        remove = q->front->next;
        q->front->next = q->front->next->next;
        q->size--;


        if (IsEmptyClockQueue(q))
            q->rear = q->front;

        free(remove);
    }
    else
        printf("Event Queue is empty\n");

}
