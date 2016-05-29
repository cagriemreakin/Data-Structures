/*

*/
#include <stdio.h>
#include <stdlib.h>

/*True or False declaration*/
#define FALSE 0
#define TRUE 1

/*Node declaration of a Linked List*/

struct Node {
     int data;
     struct Node *next;
};

void staticBuild1234(void);
void printList(struct Node *);
struct Node *dynamicBuild1234(void);
void recursivePrintList(struct Node *);
struct Node * copyList(struct Node *);

int main()
{
        int command;
        int exit = FALSE;

        struct Node *list;
        struct Node *copylist;

        while (!exit)
        {
               fflush(stdin);
               printf("\nEnter command: ");

               scanf("%c", &command);


               switch(command)
                  {
                         case 'a':
                                staticBuild1234();
                                break;

                         case 'b':
                                list = dynamicBuild1234();
                                printList(list);
                                break;

                         case 'c':
                                list = dynamicBuild1234();
                                recursivePrintList(list);
                                break;

                         case 'd':
                                list = dynamicBuild1234();
                                copylist = copyList(list);
                                recursivePrintList(copylist);
                                break;

                         case 'x':
                                exit = TRUE;
                                break;

                         default:
                                printf("command not recognized\n");
                                break;
                  }

        }


        printf("\n\n");
        system("PAUSE");
        return 0;
}

void staticBuild1234(void)
{
     struct Node nd1,nd2,nd3,nd4;
     struct Node *head;

     nd1.data = 4;
     nd1.next = &nd2;

     nd2.data = 5;
     nd2.next = &nd3;

     nd3.data = 6;
     nd3.next = &nd4;

     nd4.data = 7;
     nd4.next = NULL;

     head = &nd1;

     printList(head);
}

struct Node *dynamicBuild1234(void)
{
     struct Node *head;
     struct Node *temp;

     head = (struct Node*)malloc(sizeof(struct Node));
     head->data = 4;
     temp = head;

     temp->next = (struct Node*)malloc(sizeof(struct Node));
     temp = temp->next;
     temp->data = 5;


     temp->next = (struct Node*)malloc(sizeof(struct Node));
     temp = temp->next;
     temp->data = 6;

     temp->next = (struct Node*)malloc(sizeof(struct Node));
     temp = temp->next;
     temp->data = 7;

     temp->next = NULL;
     return head;
}


void printList(struct Node *p)
{
     while (p != NULL)
     {
           printf("Address: %d    Data: %d    Next: %d\n",p,p->data,p->next);
           p = p->next;
     }
}

void recursivePrintList(struct Node *p)
{
     if (p != NULL)
     {                                        /*  reverse print  */
           recursivePrintList(p->next);
           printf("Address: %d    Data: %d    Next: %d\n",p,p->data,p->next);

     }
}


struct Node * copyList(struct Node *p)
{
     struct Node *newhead;
     struct Node *temp;

     newhead = (struct Node*)malloc(sizeof(struct Node));
     newhead->data = p->data;
     temp = newhead;

     while (p->next != NULL)
     {
           temp->next = (struct Node*)malloc(sizeof(struct Node));
           temp = temp->next;
           p = p->next;
           temp->data = p->data;
     }

     temp->next = NULL;

     return newhead;
}


