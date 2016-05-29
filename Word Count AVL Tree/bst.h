
///     BST Header File

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*A tree Node declaration*/
struct BSTreeNode
{
	     char* val;
		 struct BSTreeNode* left;
	     struct BSTreeNode* right;
	     int count;
};

/*A tree decleration which is mainly a pointer to a Node*/
typedef struct BSTreeNode *Tree;

/*Function signatures*/
Tree CreateBSTree (void);
Tree MakeEmptyBSTree (Tree);
Tree InsertElementBS (char*, Tree);
void DisplayBSTree (Tree);
char* IterativeFindMinimumBST (Tree);
char* IterativeFindMaximumBST (Tree);
char* RecursiveFindMinimumBST (Tree);
char* RecursiveFindMaximumBST (Tree);
Tree findElementBST (char*, Tree);
void PrintBinaryTreeStructure(Tree, int);
int CountNodes (Tree);
int CountLeaves (Tree);
int IdenticalTrees (Tree, Tree);
int Height (Tree);
int IsBalanced (Tree);



/*Function that mainly creates a tree which is initially NULL*/
Tree CreateBSTree(void)
{
    return NULL;
}

/*Function that takes a tree and makes it an empty tree by removing all the nodes from that tree*/
Tree MakeEmptyBSTree(Tree t)
{
     if (t != NULL)
     {
         MakeEmptyBSTree(t->left);
         MakeEmptyBSTree(t->right);
         free(t);
     }
     return NULL;
}



/*This function takes an integer value and a tree,
  and inserts that value to the tree*/
Tree InsertElementBS(char* val, Tree t)
{
    if (t == NULL)
    {  /* Create and return a one-node tree */
        t = (Tree) malloc(sizeof(struct BSTreeNode));
        if (t == NULL)
        {
            printf("\nOut of space!!!  BST 1");
        }

        else
        {

      //      printf("> %d\n",strlen(val));

            t->val = (char *) realloc(NULL,(strlen(val) + 1));
      //      printf("t->val: %d\n",strlen(t->val));
            if (t->val == NULL)
            {
                printf("\nOut of space!!!  BST 2");
            }

            else
            {
                strcpy(t->val,val);
                t->left = t->right = NULL;
                t->count = 1;

       //         printf("> %s\n\n",t->val);
            }
        }
    }
    else



     if (strcmp(t->val,val) > 0)
          t->left = InsertElementBS(val, t->left);
     else if (strcmp(t->val,val) < 0)
          t->right = InsertElementBS(val, t->right);
     else if (strcmp(t->val,val) == 0)
          t->count++;


     /* else val is in the tree already. We'll do nothing */
     return t; /* Don't forget this line!! */
}



/*This function takes a tree and displays its content on the screen*/
void DisplayBSTree(Tree t)
{
   if (t !=NULL)
   {
		DisplayBSTree(t->left);
		printf("%s\n", t->val);
		DisplayBSTree(t->right);
   }
}



char* IterativeFindMinimumBST (Tree t)
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
         printf("BS Tree is empty!\n");

}


char* IterativeFindMaximumBST (Tree t)
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
         printf("BS Tree is empty!\n");
}



char* RecursiveFindMinimumBST (Tree t)
{
    if (t->left == NULL)
         return t->val;

    else
        RecursiveFindMinimumBST (t->left);
}



char* RecursiveFindMaximumBST (Tree t)
{
    if (t->right == NULL)
         return t->val;

    else
        RecursiveFindMaximumBST (t->right);
}


Tree findElementBST (char* key, Tree t)
{
    if (t != NULL)
    {
         while (t != NULL)
         {
              if (strcmp(t->val,key) > 0)
                  t = t->left;
              else if  (strcmp(t->val,key) < 0)
                  t = t->right;
              else if (strcmp(t->val,key) == 0)
                  return t;
              else
                  printf("The number you searched is not in BS tree!\n");
         }
    }
    else
        printf("BS Tree is empty!\n");
}



void PrintBinaryTreeStructure(Tree t, int depth)
{
    int i;

    if (t !=NULL)
    {
         PrintBinaryTreeStructure(t->right,depth+1);
         for (i = 0; i < depth; i++)
         printf("\t");

 		 printf("%s,%d,%d\n", t->val,t->count,Height(t));
 		 PrintBinaryTreeStructure(t->left,depth+1);
		 if (depth == 0)
		 printf("\n");
    }
}

/*
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

*/

int Height (Tree t)
{    if(t==NULL)
         return -1;
     if (Height(t->left) > Height(t->right))
         return Height(t->left) + 1;

     else
         return Height (t->right) + 1;
}

int IsBalanced(Tree t)
{
if (t==NULL)
   return 1;
else if( (abs((Height(t->left)-Height(t->right))) <= 1)&& IsBalanced(t->left) && IsBalanced(t->right))
   return 1;
else
   return 0;

}

