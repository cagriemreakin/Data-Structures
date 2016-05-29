#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTS 16
#define FALSE 0
#define TRUE 1

/*A tree Node declaration*/
struct Node
{
	     int val;
		 struct Node* left;
	     struct Node* right;
};

/*A tree decleration which is mainly a pointer to a Node*/
typedef struct Node *Tree;

/*Function signatures*/
Tree CreateTree(void);
Tree MakeEmptyTree(Tree);
Tree InsertElement(int, Tree);
void DisplayTree(Tree);
int IterativeFindMinimum(Tree);
int IterativeFindMaximum(Tree);
int RecursiveFindMinimum (Tree);
int RecursiveFindMaximum (Tree);
Tree findElement(int, Tree);
Tree PrintBinaryTreeStructure(Tree, int);
int CountNodes (Tree);
int CountLeaves(Tree);
int IdenticalTrees(Tree, Tree);



int main()
{
    Tree myTree, myTree2, pos;
    int exit, val, height, key;
    int command;
        
        
        myTree = CreateTree();  
        myTree2 = CreateTree();        
        exit = FALSE;

        while (!exit)
        {
               fflush(stdin);
               printf("\nMenu:\n 1) initialize\n 2) new element \n 3) find minimum iteratively \n 4) find maximum iteratively \n 5) find minimum recursively \n 6) find maximum recursively \n 7) find element\n 8) print tree\n 9) show the number of nodes and leaves\n 10) check identical\n 11) new element (2nd tree)\n 0) exit\nEnter command: ");
               scanf("%d", &command);  
               fflush(stdin);
               
                  switch(command) 
                  {       
                         case 1:
                                myTree = MakeEmptyTree(myTree);
                                myTree2 = MakeEmptyTree(myTree2);
        
                                break;
                         case 2:
                                printf("enter value: ");
                                scanf("%d", &val);
                                myTree = InsertElement(val, myTree);
                                DisplayTree(myTree);
                                break;                 
                                
                         case 3:
                                printf("Min: %d \n",IterativeFindMinimum(myTree));
                                break;
                                
                         case 4:
                                printf("Max: %d \n",IterativeFindMaximum(myTree));
                                break;       
                         
                         case 5:
                                printf("Min: %d \n",RecursiveFindMinimum(myTree));
                                break;
                                
                         case 6:
                                printf("Max: %d \n",RecursiveFindMaximum(myTree));
                                break;  
                         
                         case 7:
                                printf("Enter a number to search: ");
                                scanf("%d",&key);
                                pos = findElement(key,myTree);
                                if (pos ->val == key)
                                printf("Its founded\n");
                                else
                                printf("Its not founded\n");
                                break;  
                                         
                                
                         case 8:
                                PrintBinaryTreeStructure(myTree,0);
                                break;  
                                
                         case 9:
                                printf("Number of Nodes: %d \n",CountNodes(myTree));
                                printf("Number of Leaves: %d \n",CountLeaves(myTree));
                                break; 
                         
                         case 10:
                                if (IdenticalTrees(myTree, myTree2) == 1)
                                    printf("They are identical\n");
                                else
                                    printf("They are not identical\n");
                                break; 
                                
                         case 11:
                                printf("enter value: ");
                                scanf("%d", &val);
                                myTree2 = InsertElement(val, myTree2);
                                DisplayTree(myTree2);
                                break; 
                                   
                         case 0:
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

/*Function that mainly creates a tree which is initially NULL*/
Tree CreateTree(void)
{
    return NULL;
}

/*Function that takes a tree and makes it an empty tree by removing all the nodes from that tree*/
Tree MakeEmptyTree(Tree t)
{
     if (t != NULL)
     {
         MakeEmptyTree(t->left);
         MakeEmptyTree(t->right);
         free(t);
     }
     return NULL;
}



/*This function takes an integer value and a tree,
  and inserts that value to the tree*/
Tree InsertElement(int val, Tree t)
{
     if (t == NULL)
     {  /* Create and return a one-node tree */
          t = (Tree) malloc(sizeof(struct Node));
          
          if (t == NULL)
          printf("Out of space!!!");
          else
          {
               t->val = val;
               t->left = t->right = NULL;
          }
     }
     else
      
     if (val < t->val)
          t->left = InsertElement(val, t->left);
     else if (val > t->val)
          t->right = InsertElement(val, t->right);
         
     /* else val is in the tree already. We'll do nothing */
     return t; /* Don't forget this line!! */
}



/*This function takes a tree and displays its content on the screen*/
void DisplayTree(Tree t)
{
   if (t !=NULL) 
   {
		DisplayTree(t->left);
		printf("%d\n", t->val);
		DisplayTree(t->right);
   }
}


int IterativeFindMinimum (Tree t)
{
    if (t != NULL)
    {
         while (t->left != NULL)
         {
              t = t->left;
         }
         
         return t->val;
    }
    else
         printf("Tree is empty!\n");
    
}


int IterativeFindMaximum (Tree t)
{
    if (t != NULL)
    {
         while (t->right != NULL)
         {
              t = t->right;
         }
         
         return t->val;
    }
    else
         printf("Tree is empty!\n");   
}



int RecursiveFindMinimum (Tree t)
{
    if (t->left == NULL)
         return t->val;
         
    else
        RecursiveFindMinimum (t->left);
}



int RecursiveFindMaximum (Tree t)
{
    if (t->right == NULL)
         return t->val;
         
    else
        RecursiveFindMaximum (t->right);
}


Tree findElement (int key, Tree t)
{
    if (t != NULL)
    {
         while (t != NULL)
         {
              if (key < t->val)
                  t = t->left;
              else if  (key > t->val)  
                  t = t->right;
              else if (key == t->val)
                  return t;
              else
                  printf("The number you searched is not in tree!\n");
         }
    }
    else
        printf("Tree is empty!\n");
}



Tree PrintBinaryTreeStructure(Tree t, int depth)
{   
    int i; 
     
    if (t !=NULL) 
    {
         PrintBinaryTreeStructure(t->right,depth+1);
         for (i = 0; i < depth; i++)
         printf("\t");
         
 		 printf("%d\n", t->val);
 		 PrintBinaryTreeStructure(t->left,depth+1);
		 if (depth == 0)
		 printf("\n");
    }
}


int CountNodes(Tree t)
{
    if (t == NULL)
        return 0;
    else
        return ((CountNodes (t->left)) + (CountNodes(t->right)) + 1);
}



int CountLeaves(Tree t)
{
    if (t == NULL)
        return 0;
    else if (t->left == NULL && t->right == NULL)
        return 1;
    else
        return CountLeaves(t->left) + CountLeaves(t->right);

}


int IdenticalTrees(Tree t1, Tree t2)
{
    if (t1 == NULL && t2 == NULL)
        return 1;
    else if (t1 != NULL && t2 != NULL)
    {
        if ( (t1->val == t2->val) && IdenticalTrees (t1->left,t2->left) && IdenticalTrees (t1->right,t2->right) )
        {
            return 1;
        }
    }
    else
        return 0;
}



