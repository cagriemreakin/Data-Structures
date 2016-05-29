#include <stdio.h>
#include <stdlib.h>

//To represent an empty stack, EMPTY_TOS -1 is used
#define EMPTY_TOS -1 
//Minimim stack size should be 5
#define MIN_STACK_SIZE 5
#define FALSE 0
#define TRUE 1

//Stack record that holds the following data:
//the capacity of the stack, 
//index of the top of stack and 
//the array to hold the data in the stack

struct  StackRecord
{
	int capacity;
	int topOfStack;
	int* array;
};


typedef struct StackRecord *Stack;

//function signatures
Stack CreateStack(int);
void MakeEmptyStack(Stack);
void PushStack(int, Stack);
int PopStack(Stack);
int TopOfStack(Stack);
int IsFullStack(Stack);
int IsEmptyStack(Stack);
void DisplayStack(Stack);
void ReverseStack(Stack);

int main()
{
        int stackSize;
        Stack myStack;
        int exit, val;
        char command;
        
        printf("Enter stack size: ");
        scanf("%d", &stackSize);
        myStack = CreateStack(stackSize);
        if(myStack == NULL)
          exit = TRUE;
        else
          exit = FALSE;
        
        while (!exit)
        {
               fflush(stdin);
               printf("Enter command \n\n\ti)nitialize \n\tp)ush \n\tr)emove (pop) \n\tt)op of stack \n\te)xit: \n\tx)reverse");
               scanf("%c", &command);  
               fflush(stdin);
               
                  switch(command) 
                  {       
                         case 'i':
                                MakeEmptyStack(myStack);
                                break;
                         case 'p':
                                printf("enter value: ");
                                scanf("%d", &val);
                                PushStack(val, myStack);
                                break;
                         case 'r':
                                val = PopStack(myStack);
                                break;
                          case 't':
                                val = TopOfStack(myStack);
                                if (val != -1)
                                       printf("top element is %d\n", val);
                                break;           
                         case 'e':
                                exit = TRUE;
                                break;
                         case 'x':
                                ReverseStack(myStack);
                                break;  
                         default:
                                 printf("command not recognized\n");
                                 break;
                  }
                  DisplayStack(myStack);
                  
        }
     
        printf("\n\n");              
        system("PAUSE");	
        return 0;
}

//This function initialises a stack by initialising the following:
//Initiliases the array that will hold the data
//Sets the capatity to the maximum number of elements
//Calls makeEmptyStack to initialise the top of stack to -1
Stack CreateStack(int maxElements)
{
	Stack s;
	s = (struct StackRecord *)malloc(sizeof(struct StackRecord));
	
	if (s == NULL)
	{
        printf("Canonot create stack");
	    return NULL;
    }
    else
    {
        s->array = (int *)malloc(sizeof(int)*maxElements);
        if (s->array == NULL)
        {
            printf("Canoot create stack");
	        return NULL;
        }
        else
        {
            s->capacity = maxElements;
            MakeEmptyStack(s);
        }
        
    }
    
    return s;
}

//Sets the top of stack to -1 which represents an empty stack
void MakeEmptyStack(Stack s)
{
	s->topOfStack = EMPTY_TOS;
}

//Checks if a stack is empty, if the top of stack is -1 then the stack is empty
int IsEmptyStack(Stack s)
{
    return (s->topOfStack == EMPTY_TOS);
}

//Checks if a stack is full, if the top of stack is equal to the capacity then the stack is full
int IsFullStack(Stack s)
{
	return (s->topOfStack + 1 == s->capacity);
}

//Pushes the given element to the stack and increments the top of stack
void PushStack(int x, Stack s)
{     
    if (IsFullStack(s))
       printf("The stack is full\n");
       
    else
    {   
        s->topOfStack++;
        s->array[s->topOfStack] = x; 
    }
}

//Pops and returns the top element in the stack and decrements the top of stack by one
int PopStack(Stack s)
{
    if (!IsEmptyStack(s))
    {
        int temp;
        
        temp = s->array[s->topOfStack];
        s->topOfStack--;                    
        return temp;
    }
    else
        printf("Stack is empty\n");
}

//Returns the top of the stack 
int TopOfStack(Stack s)
{
	if (!IsEmptyStack(s))
		return s->array[s->topOfStack];
    else{
        printf("The stack is empty\n");
        return -1;
    }
}

//Shows the content of the stack, this does not change the content of the stack
void DisplayStack(Stack s)
{
     int i;
     
     printf("Stack content:\n");
     for (i=s->topOfStack; i>=0; i--)
            printf("\t--> %d\n", s->array[i]);
}


void ReverseStack(Stack s)
{
     int i = 0;
     int done = 0;
     int n, temp;

     while (scanf("%d", &n) != EOF)  //ctrl z girilene kadar al
     {
         
           
         if (IsFullStack(s))  //stack dolduysa whiledan çik
         {      
              break;
              
         }
         else
         {
              PushStack(n,s); // dolu degilse ekle
         }
     }
     
     while (!IsEmptyStack(s))
     {
         printf("%d ",PopStack(s));
     }
     
     
     
     
     
}












