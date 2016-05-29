#include <stdio.h>
#include <stdlib.h>

/*  CustomerQueue Header File */


struct customerNode
{
    int ID;
	float arrivalTime;
	float serviceTime;
	struct customerNode *next;
};

struct CustomerRecord
{
	struct customerNode *front;
	struct customerNode *rear;
	int numOfCustomers;
};


typedef struct CustomerRecord *CustomerQueue;


CustomerQueue CreateCustomerQueue ();
void MakeEmptyCustomerQueue (CustomerQueue);
int CustomerQueueSize (CustomerQueue);
int FrontOfCustomerQueue (CustomerQueue);
int RearOfCustomerQueue (CustomerQueue);
int IsFullCustomerQueue (CustomerQueue);
int IsEmptyCustomerQueue (CustomerQueue);
void DisplayCustomerQueue (CustomerQueue);
void InsertCustomer (CustomerQueue, float, float, int);
void DequeueCustomer (CustomerQueue);




CustomerQueue CreateCustomerQueue()
{
	CustomerQueue q;

    q = (struct CustomerRecord *) malloc(sizeof(struct CustomerRecord));
    if (q == NULL)
        printf("Out of memory space\n");
    else
        MakeEmptyCustomerQueue(q);
    return q;
}


void MakeEmptyCustomerQueue(CustomerQueue q)
{
	q->numOfCustomers = 0;
	q->front = (struct customerNode *) malloc(sizeof(struct customerNode));

    if (q->front == NULL)
        printf("Out of memory space\n");
    else
    {
        q->front->next = NULL;
        q->rear = q->front;
    }
}


int IsEmptyCustomerQueue(CustomerQueue q)
{
	return (q->numOfCustomers == 0);
}



int CustomerQueueSize(CustomerQueue q)
{
	return (q->numOfCustomers);
}


int IsFullCustomerQueue(CustomerQueue q)
{
	return 0;
}


int FrontOfCustomerQueue(CustomerQueue q)
{
    if (!IsEmptyCustomerQueue(q))
		return q->front->next->ID;
    else
    {
        printf("The queue is empty\n");
            return -1;
    }
}


int RearOfCustomerQueue(CustomerQueue q)
{
	if (!IsEmptyCustomerQueue(q))
	    return q->rear->ID;
     else
     {
         printf("The queue is empty\n");
         return -1;
     }
}


void DisplayCustomerQueue(CustomerQueue q)
{
    struct customerNode *p;

    p = q->front->next;
    printf(" Queue:\n\n");

    while (p != NULL)
    {
        printf("Customer ID: %d\t Arrival Time: %.3f\t Service Time: %.3f\n", p->ID, p->arrivalTime, p->serviceTime);
        p = p->next;
    }
}


void InsertCustomer(CustomerQueue q, float arrivalTime, float serviceTime, int ID)
{
   struct customerNode *newNode, *p;

   newNode = (struct customerNode*)malloc(sizeof(struct customerNode));
   if (newNode == NULL)
        printf("Out of memory!\n");

   p = (struct customerNode*)malloc(sizeof(struct customerNode));
   if (p == NULL)
        printf("Out of memory!\n");



         newNode->serviceTime = serviceTime;
         newNode->arrivalTime = arrivalTime;
         newNode->ID = ID;
         newNode->next = NULL;

         if (q->rear == NULL)
         {
              q->rear->next = newNode;
              q->numOfCustomers++;

         }

         else
         {
              p = q->rear;

              while ((p->next != NULL) && (p->next->arrivalTime <= arrivalTime))
              {
                  p = p->next;
              }

              newNode->next = p->next;
              p->next = newNode;
              q->numOfCustomers++;
         }
}



void DequeueCustomer(CustomerQueue q)
{
    struct customerNode *remove;


    if (!IsEmptyCustomerQueue(q))
    {
        remove = q->front->next;
        q->front->next = q->front->next->next;
        q->numOfCustomers--;


        if (IsEmptyCustomerQueue(q))
        {
            q->rear = q->front;
        }

        free (remove);
    }
    else
    {
        printf("Customer Queue is empty\n");
    }


}


