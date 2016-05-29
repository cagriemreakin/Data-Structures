#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

//A linked list node declaration
struct Node
{
    int  val;
    struct Node *next;
};

//A Link list declaration
struct ListRecord
{
    struct Node *head;
    struct Node *tail;
    int size;
};

typedef struct ListRecord *List;


List CreateList(void);
void MakeEmptyList(List);
int ListSize(List);
int HeadOfList(List);
int TailOfList(List);
int IsEmptyList(List);
void DisplayList(List);
void InsertList(List, int, int);
int DeleteList(List, int);
int GetElementAtPosition(List, int);
int GetPositionOfElement(List, int);
void sortedInsert (List, int);


int main()
{
    List myList;
    int exit, val, pos;
    char command;


        myList = CreateList();

        exit = FALSE;

        while (!exit)
        {
               fflush(stdin);
               printf("\nEnter command \n\ni)nitialize \nn)ew element \nd)elete element \nf)ind element \np)osition of element \nh)ead of list \nt)ail of list \ns)orted insert \ne)xit\n\nCOMMAND: ");
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
                                InsertList(myList, pos, val);
                                break;
                         case 'd':
                                printf("enter value: ");
                                scanf("%d", &val);
                                DeleteList(myList, val);
                                break;
                         case 'p':
                                printf("enter value: ");
                                scanf("%d", &val);
                                pos = GetPositionOfElement(myList, val);
                                if (pos > 0)
                                    printf("element %d at position %d\n", val, pos);
                                break;
                         case 'f':
                                printf("enter position: ");
                                scanf("%d", &pos);
                                val = GetElementAtPosition(myList, pos);
                                if (val >= 0)
                                    printf("element at position %d is %d\n", pos, val);
                                break;
                          case 'h':
                                val = HeadOfList(myList);
                                if (val != -1)
                                       printf("front element is %d\n", val);
                                break;
                          case 't':
                                val = TailOfList(myList);
                                if (val != -1)
                                       printf("rear element is %d\n", val);
                                break;
                         case 'e':
                                exit = TRUE;
                                break;

                         case 's':

                              printf("enter value: ");
                              scanf("%d", &val);
                              sortedInsert (myList, val);

                              break;
                         default:
                                 printf("command not recognized\n");
                                 break;
                  }
                  DisplayList(myList);

        }

        printf("\n\n");
        system("PAUSE");
        return 0;
}


/*
This function initialises a list record and creates an empty list
*/
List CreateList()
{
    List l;

    l = (struct ListRecord *) malloc(sizeof(struct ListRecord));
    if (l == NULL)
        printf("Out of memory!\n");

    MakeEmptyList(l);

    return l;
}


/*
This function creates an empty list. It mainly creates a dummy node and assigns it to both head and tail pointers of the list
*/
void MakeEmptyList(List l)
{
	l->head = (struct Node *) malloc(sizeof(struct Node));
    if (l->head == NULL)
        printf("Out of memory!\n");

    l->head->next = NULL;
    l->tail = l->head;
    l->size = 0;
}


/*
This function checks if a given list is empty or not
*/
int IsEmptyList(List l)
{
	return (l->size == 0);
}


/*
This function returns the size of the list
*/
int ListSize(List l)
{
	return (l->size);
}

/*
This function returns the head of the list
*/
int HeadOfList(List l)
{
    if (!IsEmptyList(l))
		return l->head->next->val;
    else
    {
        printf("The linked list is empty\n");
            return -1;
    }
}


/*
This function returns the tail of the list
*/
int TailOfList(List l)
{
	if (!IsEmptyList(l))
	    return l->tail->val;
     else
     {
         printf("The linked list is empty\n");
         return -1;
     }
}

/*
This function traverses list elements and displays their values
*/
void DisplayList(List l)
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

/*
This function inserts an element to a list in the given position
*/
void InsertList(List l, int pos, int val)
{
    struct Node *newNode,*p;
    int i;

    newNode = (struct Node *) malloc(sizeof(struct Node));

     newNode->val = val;
     newNode->next = NULL;


     if (pos > l->size)
     {
         pos = l->size + 1;
     }
     if (pos == (l->size + 1))
     {
          l->tail->next = newNode;
          l->tail = newNode;
     }
     else{
          p = l->head;

          for (i = 0; i < pos; i++)
          {
              p = p->next;
          }

          newNode->next = p->next;
          p->next = newNode;

     }

     l->size++;
}



void sortedInsert (List l, int val)
{
     struct Node *newNode,*p;
     int i = 0;

     newNode = (struct Node *) malloc(sizeof(struct Node));

     newNode->val = val;
     newNode->next = NULL;


     if (val > l->tail->val)
     {
         l->tail->next = newNode;
         l->tail = newNode;
     }

     else
     {
         p = l->head->next;

         while (p->val < val)
         {
             p = p->next;
             i++;
      //       printf("check ");
         }

         InsertList(l,i,val);
     }
}



/*
This function first finds the node with the given value and then deletes that node from the list
*/
int DeleteList(List l, int val)
{
    struct Node *remove, *temp;

    if (!IsEmptyList(l))
    {
         temp = temp->next;
         while ((temp->next != NULL) && (temp->next->val != val))
              temp = temp->next;

         if (temp->next == NULL)
            printf("Element %d not found in linked list\n",8);
         else
         {
             remove = temp->next;
             temp->next = temp->next->next;
             free(remove);
             l->size--;
         }

         if (l->size == 0)
         l->tail = l->head;
    }
    else
    {
        printf("The linked list is empty\n");
    }

}

/*
This function first finds the node at the given position and returns the element stored at that node
*/
int GetElementAtPosition(List l, int pos)
{
	struct Node *Search;
	int i;

	if (pos > l->size)
	{
         printf("Linked list is shorter..");
	     return -1;
    }
    else
    {
        Search = l->head;
	    for (i = 0; i < pos; i++)
	    {
            Search = Search->next;;
        }
        return (Search->val);
    }
}

/*
This function finds the node that stores the given value and returns its position
*/
int GetPositionOfElement(List l, int val)
{
    struct Node * search;
    int i = 0;
    search = l->head->next;

    while ((search != NULL) && (search->val != val))
    {
          search = search->next;
          i++;
    }

    if (search == NULL)
    {
        printf("Element %d not found in linked list\n",8904734);
        return 0;
    }
    else
        return (i+1);
}

