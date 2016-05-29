#include <stdio.h>
#include <stdlib.h>

/*  EventQueue Header File */


struct eventNode
{
    int eventID;
    int eventType;
	float eventTime;
	struct eventNode *next;
};



struct EventRecord
{
	struct eventNode *front;
	struct eventNode *rear;
	int numOfEvents;
};


typedef struct EventRecord *EventQueue;


EventQueue CreateEventQueue ();
void MakeEmptyEventQueue (EventQueue);
int EventQueueSize (EventQueue);
int FrontOfEventQueue (EventQueue);
int RearOfEventQueue (EventQueue);
int IsFullEventQueue (EventQueue);
int IsEmptyEventQueue (EventQueue);
void DisplayEventQueue (EventQueue);
void InsertEvent (EventQueue,float, int, int);
void DequeueEvent (EventQueue);





EventQueue CreateEventQueue()
{
	EventQueue q;

    q = (struct EventRecord *) malloc(sizeof(struct EventRecord));
    if (q == NULL)
        printf("Out of memory space\n");
    else
        MakeEmptyEventQueue(q);
    return q;
}


void MakeEmptyEventQueue(EventQueue q)
{
	q->numOfEvents = 0;
	q->front = (struct eventNode *) malloc(sizeof(struct eventNode));
    if (q->front == NULL)
        printf("Out of memory space\n");
    else
    {
        q->front->next = NULL;
        q->rear = q->front;
    }
}


int IsEmptyEventQueue(EventQueue q)
{
	return (q->numOfEvents == 0);
}


int EventQueueSize(EventQueue q)
{
	return (q->numOfEvents);
}


int IsFullEventQueue(EventQueue q)
{
	return 0;
}


int FrontOfEventQueue(EventQueue q)
{
    if (!IsEmptyEventQueue(q))
		return q->front->next->eventID;
    else
    {
        printf("The queue is empty\n");
            return -1;
    }
}


int RearOfEventQueue(EventQueue q)
{
	if (!IsEmptyEventQueue(q))
	    return q->rear->eventID;
     else
     {
         printf("The queue is empty\n");
         return -1;
     }
}


void DisplayEventQueue(EventQueue q)
{
    struct eventNode *p;

    p = q->front->next;
    printf("\t\t\t\t Event Queue:\n\n");

    while (p != NULL)
    {
        printf("\t      Event ID: %d\t Event Type: %d\t Event Time: %.3f\n", p->eventID, p->eventType, p->eventTime);
        p = p->next;
    }
}


void InsertEvent(EventQueue q, float eventTime, int eventType, int eventID)
{
   struct eventNode *newNode, *p;

   newNode = (struct eventNode*)malloc(sizeof(struct eventNode));
   if (newNode == NULL)
        printf("Out of memory!\n");

   p = (struct eventNode*)malloc(sizeof(struct eventNode));
   if (p == NULL)
        printf("Out of memory!\n");



         newNode->eventTime = eventTime;
         newNode->eventType = eventType;
         newNode->eventID = eventID;
         newNode->next = NULL;

         if (q->rear == NULL)
         {
              q->rear->next = newNode;
              q->numOfEvents++;

         }

         else
         {
              p = q->rear;

              while ((p->next != NULL) && (p->next->eventTime <= eventTime))
              {
                  p = p->next;
              }

              newNode->next = p->next;
              p->next = newNode;
              q->numOfEvents++;


         }

}


void DequeueEvent(EventQueue q)
{
    struct eventNode *remove;

    if (!IsEmptyEventQueue(q))
    {
        remove = q->front->next;
        q->front->next = q->front->next->next;
        q->numOfEvents--;


        if (IsEmptyEventQueue(q))
            q->rear = q->front;

        free(remove);
    }
    else
        printf("Event Queue is empty\n");

}
