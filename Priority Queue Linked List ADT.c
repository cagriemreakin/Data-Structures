#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

/*A Node declaration to store a value, pointer to the next node and a priority value*/
struct Node
{
	int priority;
	int val;
	struct Node *next;
};

/*Queue Record that will store the following:
  size: total number of elements stored in the list
  front: it shows the front node of the queue (front of the queue)
  rear: it shows the rare node of the queue (rear of the queue)*/
struct QueueRecord
{
	struct Node *front;   /* pointer to front of queue */
	struct Node *rear;    /* pointer to rear of queue */
	int size;             /* number of items in queue */
};

typedef struct QueueRecord *Queue;

Queue CreateQueue(int);
void MakeEmptyQueue(Queue);
int QueueSize(Queue);
int FrontOfQueue(Queue);
int RearOfQueue(Queue);
int IsFullQueue(Queue);
int IsEmptyQueue(Queue);
void DisplayQueue(Queue);
void InsertWithPriority(Queue,int,int);
void Enqueue(Queue ,int, int);
int Dequeue(Queue);
int DeleteWithPriority(Queue);

int main()
{
    int queueSize;
    Queue myQueue;
    int exit, val, priority;
    char command;
        
    myQueue = CreateQueue(0);    
    exit = FALSE;
        
    while (!exit)
    {
          fflush(stdin);
          printf("Menu:\n i)nitialize\n f)ront queue\n r)ear queue\n a)Insert with Priority\n s)Enqueue\n e)xit \nEnter command:");
          scanf("%c", &command);  
          fflush(stdin);
               
          switch(command) 
          {       
                  case 'i':
                       MakeEmptyQueue(myQueue);
                       break;
                  case 'f':
                       val = FrontOfQueue(myQueue);
                       if (val != -1)
                          printf("front element is %d\n", val);
                       break; 
                  case 'r':
                       val = RearOfQueue(myQueue);
                       if (val != -1)
                          printf("rear element is %d\n", val);
                       break;                      
                  
                  case 'a':
                       printf("enter value: ");
                       scanf("%d", &val);
                       printf("enter priority: ");
                       scanf("%d", &priority);
                       InsertWithPriority(myQueue, priority, val);
                  
                       break;
                       
                  case 's':
                       Enqueue(myQueue, 2, 78);
                       Enqueue(myQueue, 4, 58);
                       Enqueue(myQueue, 1, 12);
                       Enqueue(myQueue, 0, 23);
                       Enqueue(myQueue, 8, 34);
                       break;
                       
                  case 'd':
                       
                       printf("Value deleted is %d\n",DeleteWithPriority(myQueue));
                       break;
                       
                  case 'e':
                       exit = TRUE;
                       break;       
                  default:
                       printf("command not recognized\n");
                       break;
          }
          DisplayQueue(myQueue);
                  
    }
    printf("\n\n");              
    system("PAUSE");	
    return 0;
}

/*This function initialises the queue*/
Queue CreateQueue(int maxElements)
{
	Queue q;
              
    q = (struct QueueRecord *) malloc(sizeof(struct QueueRecord));      
    if (q == NULL)
        printf("Out of memory space\n");
    else
       MakeEmptyQueue(q);
    return q;
}

/*This function sets the queue size to 0, and creates a dummy element 
and sets the front and rear point to this dummy element*/
void MakeEmptyQueue(Queue q)
{
	q->size = 0;
	q->front = (struct Node *) malloc(sizeof(struct Node));
    if (q->front == NULL)
	       printf("Out of memory space\n");
    else{   
            q->front->next = NULL;
	        q->rear = q->front;
    }
}

/*Shows if the queue is empty*/
int IsEmptyQueue(Queue q)
{
	return (q->size == 0);
}


/*Returns the queue size*/
int QueueSize(Queue q)
{
	return (q->size);
}

/*Shows the queue is full or not*/
int IsFullQueue(Queue q)
{
	return FALSE;
}

/*Returns the value stored in the front of the queue*/
int FrontOfQueue(Queue q)
{
    if (!IsEmptyQueue(q))
		return q->front->next->val;
    else	
    {
        printf("The queue is empty\n");
            return -1;
    }
}

/*Returns the value stored in the rear of the queue*/
int RearOfQueue(Queue q)
{
	if (!IsEmptyQueue(q))
	    return q->rear->val;
     else	
     {
         printf("The queue is empty\n");
         return -1;
     }
}

/*Displays the content of the queue*/
void DisplayQueue(Queue q)
{
    struct Node *pos;
     
    pos=q->front->next;
    printf("Queue content:\n");
    
    printf("-->Priority   Value\n");
    while (pos != NULL)
    {
        printf("--> %d\t     %d\n", pos->priority, pos->val);
        pos = pos->next;
    }
}


void InsertWithPriority(Queue q, int prio, int val)
{
   struct Node *newNode, *p;
   
   newNode = (struct Node*)malloc(sizeof(struct Node));
   if (newNode == NULL)
        printf("Out of memory!\n");
   
   p = (struct Node*)malloc(sizeof(struct Node));
   if (p == NULL)
        printf("Out of memory!\n");
        
      
        
         newNode->val = val;
         newNode->next = NULL;
         newNode->priority = prio;
       
         if (q->rear == NULL)
         {
              q->rear->next = newNode;
              q->size++; 
              
         }
         
         else
         { 
              p = q->rear;
         
              while ((p->next != NULL) && (p->next->priority <= prio))
              {
                  p = p->next;
              }
              
              newNode->next = p->next;
              p->next = newNode;
              q->size++; 
              
         
         }
   
}



void Enqueue(Queue q ,int prio, int val)
{
   struct Node *newNode;
   newNode = (struct Node*)malloc(sizeof(struct Node));
   
   newNode->val = val;
   newNode->next = NULL;
   newNode->priority = prio;
   
   q->rear->next = newNode;
   
   q->rear = newNode;
   q->size++; 
}


int Dequeue(Queue q)
{
    struct Node *remove;
    int val;
    
    if (!IsEmptyQueue(q))
    {
        remove = q->front->next;
        q->front->next = q->front->next->next;
        val = remove->val;
        q->size--;
        
        
        if (IsEmptyQueue(q))
            q->rear = q->front;
            
        free(remove);
	    return val;
    }
    else	
    {
         printf("The queue is empty\n");
             return -1;
    }
}

int DeleteWithPriority(Queue q)
{
    int min;
    
    struct Node *search, *p;
   
    search = (struct Node*)malloc(sizeof(struct Node));
    if (search == NULL)
        printf("Out of memory!\n");
   
    p = (struct Node*)malloc(sizeof(struct Node));
    if (p == NULL)
        printf("Out of memory!\n");
        
   
    if (!IsEmptyQueue(q))
    {
      
        
    p = q->front;
    min = q->front->next->priority;
    
    while ((p->next != NULL))
    {
        if (p->next->priority <= min)
        min = p->next->priority;
        
        p = p->next;
    }
    
    
    if (q->rear->priority == min)
    {
                          
    p = q->front->next;
    
    while (p->next != NULL)
    {
         p = p->next;
    }    
    
    search = p->next;
    q->rear = p;
    free(search);
    q->size--;
    
    }
    
    else
    {
        p = q->front->next;
        
        while (p->next != NULL && p->next->priority != min)
        {
              p = p->next;              
        }    
    
        search = p->next;
        p->next = p->next->next;
        free(search);
        q->size--;
    
    }
    
    if (q->size == 0)
    q->rear = q->front;
    
    
    
    return min;
    }
    
    else
    {
        printf("Queue is empty!\n");
        return -1;
    }
}













