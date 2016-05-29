
///     AVL Tree Header File

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct AVLTreeNode
{
	     char* val;
		 struct AVLTreeNode * left;
	     struct AVLTreeNode * right;
	     int height;
	     int count;
};

typedef struct AVLTreeNode *AVLTree;

AVLTree CreateAVLTree(void);
AVLTree MakeEmptyAVLTree(AVLTree);
AVLTree InsertElementAVL(char*, AVLTree);
AVLTree SingleRotateWithLeft(AVLTree);
AVLTree SingleRotateWithRight(AVLTree);
AVLTree DoubleRotateWithLeft(AVLTree);
AVLTree DoubleRotateWithRight(AVLTree);
void DisplayAVLTree(AVLTree);
void DisplayAVLTreeStructure(AVLTree, int);
int AVLTreeHeight(AVLTree);
int Max(int, int);
AVLTree findElementAVLT (char* key, AVLTree t);
char* IterativeFindMinimumAVLT (AVLTree);
char* IterativeFindMaximumAVLT (AVLTree);
char* RecursiveFindMinimumAVLT (AVLTree);
char* RecursiveFindMaximumAVLT (AVLTree);


AVLTree CreateAVLTree(void)
{
    return NULL;
}


AVLTree MakeEmptyAVLTree(AVLTree t)
{
     if (t != NULL)
     {
         MakeEmptyAVLTree(t->left);
         MakeEmptyAVLTree(t->right);
         t->val = NULL;
         free(t);
     }
     return NULL;
}


AVLTree InsertElementAVL(char* val, AVLTree t)
{
    char spaceVal[] = " ";


	if (t == NULL)
    {
		/*Create and return a one-node tree */
		t = (AVLTree) malloc(sizeof(struct AVLTreeNode));
		t->val = NULL;
		if (t == NULL)
        {
            printf("\nOut of space!!!  AVL 1");
        }
		else
        {
   //         printf("val size: %d\n",strlen(val));
            t->val = (char *) realloc(NULL,(strlen(val)));
            strcpy(t->val,val);
            t->left = NULL;
			t->right = NULL;
            t->count = 1;
            t->height = 0;

  //          printf("t->val size: %d\n\n",strlen(t->val));
  //          printf("\nHoooooooop!!!    eklendi\n");


       //     t = newNode;

        }
    }
	else if (strcmp(t->val,val) > 0)
    {					//			printf("\nHoooooooop!!!    sola gitti\n");
		t->left = InsertElementAVL(val, t->left);

		if (AVLTreeHeight(t->left) - AVLTreeHeight(t->right) == 2)
        {
   //         printf("rotate left\n");

   //         if (t->left->val == NULL)
   //            strcpy(t->left->val,spaceVal);

            if (strcmp(t->left->val,val) > 0)
		        t = SingleRotateWithLeft(t);
		    else
		        t = DoubleRotateWithLeft(t);
        }
    }
	else if (strcmp(t->val,val) < 0)
    {					//			printf("\nHoooooooop!!!    saga gitti\n");
        t->right = InsertElementAVL(val, t->right);
	    if (AVLTreeHeight(t->right) - AVLTreeHeight(t->left) == 2)
        {
  //          printf("rotate right\n");

  //          if (t->left->val == NULL)
  //              strcpy(t->left->val,spaceVal);


		    if (strcmp(t->right->val,val) < 0)
                t = SingleRotateWithRight(t);
		    else
		        t = DoubleRotateWithRight(t);
        }
    }
    else if (strcmp(t->val,val) == 0)
    {
        t->count++;
   //     printf("\nHoooooooop!!!    esit, 1 artti\n");
    }
	/* else val is in the tree already ... do nothing */
	t->height=Max(AVLTreeHeight(t->left), AVLTreeHeight(t->right)) + 1;

 //   printf("\nHoooooooop!!!    insert avl 1 kez calisti bitti\n");
//    free(val);
	return t;
}


void DisplayAVLTree(AVLTree t)
{
   if (t !=NULL)
   {
		DisplayAVLTree(t->left);
		printf("%d\n", t->val);
		DisplayAVLTree(t->right);
   }
}


void DisplayAVLTreeStructure(AVLTree t, int depth)
{
   int i;

   if (t !=NULL)
   {
		DisplayAVLTreeStructure(t->right, depth + 1);

		for (i = 0; i < depth; i++)
            printf("\t");
        printf("%s\n", t->val);

		DisplayAVLTreeStructure(t->left, depth + 1);
   }
}


int AVLTreeHeight(AVLTree t)
{
	if(t == NULL)
		return -1;
	else
		return t->height;
}



AVLTree SingleRotateWithLeft(AVLTree k2)
{
	AVLTree k1;

	k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;

	k2->height=Max(AVLTreeHeight(k2->left), AVLTreeHeight(k2->right)) + 1;
	k1->height=Max(AVLTreeHeight(k1->left), k2->height) + 1;
	return k1;
}


AVLTree SingleRotateWithRight(AVLTree k1)
{
   AVLTree k2;
   k2=k1->right;
   k1->right=k2->left;
   k2->left=k1;

   k1->height=Max(AVLTreeHeight(k1->left), AVLTreeHeight(k1->right)) + 1;
   k2->height=Max(AVLTreeHeight(k2->right), (k1->height)) + 1;
   return k2;

}


AVLTree DoubleRotateWithLeft(AVLTree k3)
{

	k3->left=SingleRotateWithRight(k3->left);
	return SingleRotateWithLeft(k3);
}


AVLTree DoubleRotateWithRight(AVLTree k1)
{
	k1->right=SingleRotateWithLeft(k1->right);
	return SingleRotateWithRight(k1);
}



int Max(int x, int y)
{
    if (x >= y)
        return x;
    else
        return y;
}



AVLTree findElementAVLT (char* key, AVLTree t)
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
                  printf("The number you searched is not in AVL tree!\n");
         }
    }
    else
        printf("AVL Tree is empty!\n");
}



char* IterativeFindMinimumAVLT (AVLTree t)
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
         printf("AVL Tree is empty!\n");

}


char* IterativeFindMaximumAVLT (AVLTree t)
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
         printf("AVL Tree is empty!\n");
}



char* RecursiveFindMinimumAVLT (AVLTree t)
{
    if (t->left == NULL)
         return t->val;

    else
        RecursiveFindMinimumAVLT (t->left);
}



char* RecursiveFindMaximumAVLT (AVLTree t)
{
    if (t->right == NULL)
         return t->val;

    else
        RecursiveFindMaximumAVLT (t->right);
}