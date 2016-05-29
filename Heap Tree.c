#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define FALSE 0
#define TRUE 1



struct HeapStruct
{
	     int capacity;
	     int size;
	     int *elements;
};

typedef struct HeapStruct *PriorityQueue;

PriorityQueue InitializePriorityQueue (int);
PriorityQueue BuildPriorityQueue(int, int[]);
void MakeEmptyPriorityQueue (PriorityQueue);
int IsEmptyPriorityQueue (PriorityQueue);
int IsFullPriorityQueue (PriorityQueue);
void DisplayPriorityQueue (PriorityQueue);
void InsertPriorityQueue(int, PriorityQueue);
void Heapify(int [],int,int);




int main()
{
    int i,queueSize;
    PriorityQueue myQueue,a;
    int exit, val, priority, cap,x,*arr;
    char command;
         
    exit = FALSE;
        
    while (!exit)
    {
          fflush(stdin);
          printf("Menu:\n\n\ti)nitialize\n\tm)ake empty queue\n\tn)ew element\n\te)xit\n\nEnter command:");
          scanf("%c", &command);  
          fflush(stdin);
               
          switch(command) 
          {       
                  case 'i':
                  printf("\nEnter the capacity: ");
                       scanf("%d",&cap);
                       myQueue = InitializePriorityQueue (cap);
                       break;
                  case 'b':
                   
                       arr=(int *) malloc (sizeof (int) * cap);
                       for(i=0;i<cap;i++)
                          {
                             scanf("%d",&arr[i]);
                          }
                       a=BuildPriorityQueue(cap,arr);
                       system("pause");
                       break;
                  case 'n':
                       printf("\nEnter a number: ");
                       scanf("%d",&val);
                       InsertPriorityQueue(val, myQueue);
                       break;
                       
                       
                       
                  case 'e':
                       exit = TRUE;
                       break;       
                       
                  default:
                       printf("command not recognized\n");
                       break;
          }
          
          DisplayPriorityQueue (myQueue);
          
                  
    }
    printf("\n\n");              
    system("PAUSE");	
    return 0;
}



PriorityQueue InitializePriorityQueue (int maxElements)
{
    PriorityQueue HeapQueue;
    
    HeapQueue = (struct HeapStruct *) malloc (sizeof (struct HeapStruct));
    if (HeapQueue == NULL)
        printf("Out of memory space\n");
        
        
    HeapQueue->elements = (int *) malloc (sizeof (int) * maxElements);
    if (HeapQueue->elements == NULL)
        printf("Out of memory space\n");
    
    HeapQueue->capacity = maxElements;
    HeapQueue->size = 0;
    HeapQueue->elements[0] = INT_MIN;
    
    return HeapQueue;
}

void MakeEmptyPriorityQueue (PriorityQueue h)
{
    h->size = 0;
}


int IsEmptyPriorityQueue (PriorityQueue h)
{
    return (h->size == 0);
}


int IsFullPriorityQueue (PriorityQueue h)
{
    return (h->size == h->capacity);
}

void DisplayPriorityQueue (PriorityQueue h)
{
    int i;
     
    for (i = 1; i <= h->size; i++)
    {
        printf("%d ",h->elements[i]);
    }
    printf("\n");
}


void InsertPriorityQueue(int val, PriorityQueue h)
{
    
    int pos;
    if (IsFullPriorityQueue(h))
    {
         printf("\nQueue is full!\n");
    }
    else
    {   
        h->size++;     
        pos = h->size;
        
        while (val < h->elements[pos / 2])
        {
              h->elements[pos] = h->elements[pos / 2];
              pos = pos / 2;
        }
        h->elements[pos] = val;
    }
}

PriorityQueue BuildPriorityQueue(int n, int x[])
{
 PriorityQueue Q;
 int i,min;
 Q=(struct HeapStruct *) malloc (sizeof (struct HeapStruct));
 if(Q==NULL)
   printf("out of memory");
 
 Q->elements = (int *) malloc (sizeof (int) * n);
 Q->capacity = n;
 Q->size = 0;
 Q->elements[0] = INT_MIN;
 
 for(i=0; i>0 ;i--)
 {  Q->elements[i+1]=x[i];
    Q->size++;
 }

 for(i=n/2;i<n;i++)
  Heapify(Q->elements,i,n);

 
 return Q;
}


void Heapify(int arr[],int index, int y)
{
int left,right,temp,smallest;
left=2*index;
right=2*index+1;
if(arr[index]>arr[left])
   smallest=left;
else
  smallest = index;
if(arr[smallest]>arr[right])
  smallest=right;

if(smallest!=index)
 {
   temp=arr[index];
   arr[index]=arr[smallest];
   arr[smallest]=temp;
 
  Heapify(arr,smallest,y);
 }
}











