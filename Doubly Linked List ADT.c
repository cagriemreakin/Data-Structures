#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

struct Node 
{ 
	int val; 
	struct Node *next;
    struct Node *prev;
};

struct ListRecord
{
    struct Node *head;
    struct Node *tail;
    int length;
}; 

typedef struct ListRecord *DoubleList;

DoubleList CreateList(int);
void MakeEmptyList(DoubleList);
void InsertListAtPosition(DoubleList, int, int); 
void DisplayList(DoubleList);
int DeleteListAtPosition(DoubleList, int);
int IsEmptyList(DoubleList);


int main()
{
    DoubleList myList;
    int exit, val, pos;
    char command;
    exit = FALSE;    
        
        myList = CreateList(0);        
                
        while (!exit)
        {
               fflush(stdin);
               printf("\nMenu: \n i)nitialize\n n)ew element\n d)elete element at a position\n e(x)it\nEnter command: ");
               scanf("%c", &command);  
               fflush(stdin);
               
                  switch(command) 
                  {       
                         case 'i':
                                MakeEmptyList(myList);
                                break;
                         case 'n':
                                printf("enter value: ");
                                scanf("%d", &val);
                                printf("enter position: ");
                                scanf("%d", &pos);
                                InsertListAtPosition(myList, pos, val);
                                break;   
                         case 'd':
                                printf("enter position: ");
                                scanf("%d", &pos);
                                printf("Element %d at position %d is deleted!\n",DeleteListAtPosition(myList, pos),pos);
                                break;           
                         case 'x':
                                exit = TRUE;
                                break;       
                         default:
                                 printf("command not recognized\n");
                                 break;
                  }
                  printf("\n");
                  DisplayList(myList);
                  
        }
     
        printf("\n\n");              
        system("PAUSE");	
        return 0;
}

DoubleList CreateList(int size) 
{ 
    DoubleList l;
   			
    l = (struct ListRecord *) malloc(sizeof(struct ListRecord));
    if (l == NULL){
        printf("Out of memory!\n");
        return NULL;
    }
    else{  
        MakeEmptyList(l); 
        return l;
    }
} 


void MakeEmptyList(DoubleList l)
{
    l->head = (struct Node *) malloc(sizeof(struct Node));
    if (l->head == NULL)
        printf("Out of memory!\n");
    
    else
    {   
        l->head->next = NULL;
        l->head->prev = NULL;
        l->tail = l->head;
        l->length = 0;
    }
}

void InsertListAtPosition(DoubleList l, int pos, int val) 
{ 
     struct Node *newNode,*p;
     int i;
     
     newNode = (struct Node *) malloc(sizeof(struct Node));
     if (newNode == NULL)
        printf("Out of memory!\n");
        
     else
     {
         newNode->val = val;
         newNode->next = NULL;
         newNode->prev = NULL;
         
         if (pos > l->length)
         {
              pos = l->length + 1;
         }
         
         if (pos == l->length + 1)
         {
              l->tail->next = newNode;
              newNode->prev = l->tail;
              l->tail = newNode;
                
         }
         
         else
         {
             p = l->head;
          
             for (i = 0; i < pos; i++)
             {
                 p = p->next;
             }
             newNode->next = p;
             newNode->prev = p->prev;
             p->prev->next = newNode;
             p->prev = newNode;         
             
         }
         l->length++;
     }

}


int DeleteListAtPosition(DoubleList l, int pos)
{
    struct Node *remove, *temp;
    int i,val;
    
    if (!IsEmptyList(l))
    {
         temp = l->head;
         if (pos > l->length)
         {     
             printf("daha kucuk!!! \n");
         }
         else
         {
             for (i = 1; i < pos; i++)
             temp = temp->next;
             
             remove = temp->next;
             remove->prev->next = remove->next;
             remove->next->prev = remove->prev;
             val = remove->val;
             free(remove);
             
             l->length--;
         }
         
         if (l->length == 0)
         l->tail = l->head;
         
         
         return val;
    }
    else
    {
        printf("The linked list is empty\n");
    }
    return -1;
}


int IsEmptyList(DoubleList l)
{
	return (l->length == 0);
}


void DisplayList(DoubleList l)
{
    struct Node *p;
     
    p=l->head->next;
    printf("List content:\n");
    
    while (p != NULL)
    {
        printf("--> %d\t", p->val);
        p = p->next;
    }
}


