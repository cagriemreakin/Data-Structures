
/**
  *     Word Count
  *
  *     @Author:  Çaðrý Emre Akin 
  *              
  *
  *
  *		 
  *	    This assignment aims to help you practice binary tree abstract data types, specifically BST (Binary
		Search Tree) and AVL trees. You will write a program that processes a text file and counts the
		number of occurrences of words in that word file. You will implement this both with BST and AVL
		trees. The purpose of this assignment is to produce a file that lists these words in a file in an
		alphabetical order and also compares the performance of search with a BST and an AVL tree
		implementation. 
  *
  */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
//#include <locale.h>


#include "bst.h"
#include "avlt.h"

#define TRUE 1
#define FALSE 0


void WriteFileBST (Tree, char*);
void WriteFileAVLT (AVLTree, char*);



struct Stats
{
	clock_t Start, Finish;
	double BST_Left_Start, BST_Left_Finish, BST_Right_Start, BST_Right_Finish;
	double AVLT_Left_Start, AVLT_Left_Finish, AVLT_Right_Start, AVLT_Right_Finish;
	double BST_Random[8], AVLT_Random[8];

};




int main()
{
//    setlocale(LC_ALL,"C");
//    printf ("Locale is: %s\n\n", setlocale(LC_ALL,NULL) );

    int i, k, opselect, loopLock = TRUE, count, chCount, contentSize = 0, contentCount = 0, cleanContentSize = 0, cleanContentCount = 0, *space, randomNum;
    char ch, command[80], inputFile[30], outputFile[30], outputBST[30], outputAVLT[30], *string, *val, *content, *cleanContent, wordTemp[80], *word, *key, randomKeys[20];

	struct AVLTreeNode * AVLT;
    struct BSTreeNode * BST;

	struct Stats TimeStats;

	FILE *inFile;
	FILE *outFile;

	word = NULL;
	content = NULL;
	cleanContent = NULL;
	space = NULL;
	//randomKeys = NULL;

	srand(time(NULL));

    BST = CreateBSTree();
    AVLT = CreateAVLTree();

	





    printf("--------------------------------------------------------------------------------");
    printf("--------------------------------------------------------------------------------");
    printf("--------------------------------------------------------------------------------");
    printf("--------------------------------------------------------------------------------\n");
    printf("\t\t\t\t    WORD COUNT\n");

    while (loopLock == TRUE)
    {
        fflush(stdin);
        printf("\n--------------------------------------------------------------------------------\n");
        printf("---------------------------------- SYSTEM MENU ---------------------------------\n\n\t\t\t1 : Initialize Trees \n\t\t\t2 : Enter Command \n\t\t\t3 : Search Performance Check \n\t\t\t4 : About \n\n\t\t\t5 : Create Files and Exit \n\n\t\t\tSelection: ");
        scanf("%d", &opselect);
        fflush(stdin);

        switch(opselect)
        {
            case 1:
                BST = MakeEmptyBSTree(BST);
                AVLT = MakeEmptyAVLTree(AVLT);
                break;


            case 2:
                printf("\n--------------------------------------------------------------------------------\n");
                printf("Enter command: ");

                i = 0;
                while ((ch = getchar()) != '\n')
                {
                    command[i] = ch;
                    i++;
                }
                command[i] = '\0';

             //   printf("\n--->%s<---\n",command);

                string = strtok(command," ");

                if (strcmp(string,"WordCount") != 0)
                {
                    printf("\n--------------------------------------------------------------------------------\n");
                    printf("WARNING: Command not recognized\n");
                }
                else
                {
                    count = 0;

                    while (string != NULL)
                    {
                        string = strtok(NULL," ");

                        if (count == 0)
                            strcpy(inputFile,string);
                        //   strncpy ( inputFile, string, sizeof(string) - 4 );

                        else if (count == 1)
                            strcpy(outputFile,string);

                        count++;
                    }


                    if ( inputFile != NULL && outputFile != NULL )
                    {
                        loopLock = TRUE;
                    }



                    if ( ( inFile = fopen(inputFile,"r")) == NULL)
                    {
                        printf("\nFailed to open the file.\n");
                        exit(1);
                    }
                    else
                    {
                        while ( fscanf(inFile,"%s", wordTemp) != EOF )
                        {
							
				//			word[i+1] = '\n';
                            for(i = 0; wordTemp[i]; i++)
                            {
                                wordTemp[i] = tolower(wordTemp[i]);
                            }

							i = 0;
							chCount = strlen(wordTemp);

			//				printf("\n%d\n",chCount);
			//				
							
                                word = (char*) realloc (word, sizeof(char)*chCount);

                                while (i <= chCount)
                                {
                                    word[i] = wordTemp[i];

                                    i++;
                                }

                                word[i] = '\0';

								contentSize = contentSize + chCount + 1;
			//					puts(word);
								content = (char*) realloc (content, sizeof(char)*contentSize);
			//					printf("%d\n",contentSize);

								for (i = 0; i < chCount ; i++)
								{
			//						printf("check\n");
									content[contentCount] = word[i];

									contentCount++;
								}
								content[contentCount] = ' ';
								contentCount++;
								content[contentCount] = '\0';

			//					printf("%s - %d\n",content,strlen(content));

                        }
                    }

                    fclose(inFile);

                    puts(content);						// tek bir string e atýlmýþ olan temizlenmemiþ file icerigini bastýrýr
				
					val = strtok(content," \",.'-?!()");

                    while (val != NULL)
                    {
						chCount = strlen(val);
						cleanContentSize = cleanContentSize + chCount + 1;

						cleanContent = (char*) realloc (cleanContent, sizeof(char) * cleanContentSize);

						for (i = 0; i < chCount ; i++)
						{

							cleanContent[cleanContentCount] = val[i];

							cleanContentCount++;
						}
						cleanContent[cleanContentCount] = ' ';
						cleanContentCount++;
						cleanContent[cleanContentCount] = '\0';



							//                printf ("string: %s\n",val);
							// 				  printf("%d\n",strlen(val));
                        BST = InsertElementBS(val, BST);
                        AVLT = InsertElementAVL(val, AVLT);
							//                printf ("-------------------------\n");
							//                DisplayAVLTreeStructure(AVLT,0);
							//                printf ("-------------------------\n");
						val = strtok(NULL," \",.'-?!()");
				
							//                printf ("string: %s\n",val);
                    }

					puts(cleanContent);					// tek bir string e atýlmýþ olan temizlenmiþ file icerigini bastýrýr

                }

                break;


			case 3:
				printf("\n------------------------------ PERFORMANCE CHECK -------------------------------\n");

				

				printf("PROCESS: Seaching the word in far left child of BS Tree.\n\n");
				TimeStats.Start = clock();
				TimeStats.BST_Left_Start = TimeStats.Start;
				printf("SYSTEM: The search process is started.\t\t Current Clock: %lf \n", ((double)TimeStats.BST_Left_Start) / CLOCKS_PER_SEC);
				key = IterativeFindMinimumBST (BST);
				TimeStats.Finish = clock();
				TimeStats.BST_Left_Finish = TimeStats.Finish;
				printf("SYSTEM: Searched Keyword: %s\n",key);
				printf("SYSTEM: The search process is completed.\t Current Clock: %lf \n\n", ((double)TimeStats.BST_Left_Finish) / CLOCKS_PER_SEC);
				Sleep(500);


				printf("\n--------------------------------------------------------------------------------\n");
				printf("PROCESS: Seaching the word in far right child of BS Tree.\n\n");
				TimeStats.Start = clock();
				TimeStats.BST_Right_Start = TimeStats.Start;
				printf("SYSTEM: The search process is started.\t\t Current Clock: %lf \n", ((double)TimeStats.BST_Right_Start) / CLOCKS_PER_SEC);
				key = IterativeFindMaximumBST (BST);
				TimeStats.Finish = clock();
				TimeStats.BST_Right_Finish = TimeStats.Finish;
				printf("SYSTEM: Searched Keyword: %s\n",key);
				printf("SYSTEM: The search process is completed.\t Current Clock: %lf \n\n", ((double)TimeStats.BST_Right_Finish) / CLOCKS_PER_SEC);
				Sleep(500);

				printf("\n--------------------------------------------------------------------------------\n");
				printf("PROCESS: Seaching the word in far left child of AVL Tree.\n\n");
				TimeStats.Start = clock();
				TimeStats.AVLT_Left_Start = TimeStats.Start;
				printf("SYSTEM: The search process is started.\t\t Current Clock: %lf \n", ((double)TimeStats.AVLT_Left_Start) / CLOCKS_PER_SEC);
				key = IterativeFindMinimumAVLT (AVLT);
				TimeStats.Finish = clock();
				TimeStats.AVLT_Left_Finish = TimeStats.Finish;
				printf("SYSTEM: Searched Keyword: %s\n",key);
				printf("SYSTEM: The search process is completed.\t Current Clock: %lf \n\n", ((double)TimeStats.AVLT_Left_Finish) / CLOCKS_PER_SEC);
				Sleep(500);

				printf("\n--------------------------------------------------------------------------------\n");
				printf("PROCESS: Seaching the word in far right child of AVL Tree.\n\n");
				TimeStats.Start = clock();
				TimeStats.AVLT_Right_Start = TimeStats.Start;
				printf("SYSTEM: The search process is started.\t\t Current Clock: %f \n", ((double)TimeStats.AVLT_Right_Start) / CLOCKS_PER_SEC);
				key = IterativeFindMaximumAVLT (AVLT);
				TimeStats.Finish = clock();
				TimeStats.AVLT_Right_Finish = TimeStats.Finish;
				printf("SYSTEM: Searched Keyword: %s\n",key);
				printf("SYSTEM: The search process is completed.\t Current Clock: %f \n\n", ((double)TimeStats.AVLT_Right_Finish) / CLOCKS_PER_SEC);
				

				Sleep(500);
				printf("\n--------------------------------------------------------------------------------\n");


				i = 0;
				k = 0;

				while (i < strlen(cleanContent))
				{
					if (cleanContent[i] == ' ')
					{
						space = (int*) realloc (space, sizeof(int) * (k + 1));
						space[k] = i;
						k++;
					}
					i++;
				}

				randomNum = rand() % k;

			//	printf("====> %d", randomNum);

			//	randomKeys = (char*) realloc (randomKeys, sizeof(char) * (space[randomNum] - space[randomNum - 1] + 1) );

				i = space[randomNum - 1];


				while ( i < space[randomNum] )
				{
					randomKeys[i] = cleanContent[i];
					i++;
				}
				randomKeys[i + 1] = '\0';
		//		puts(randomKeys);
		

				printf("\n--------------------------------------------------------------------------------\n");
				Sleep(2000);

				printf("\nALL DONE!\n");

		/*
				printf("SYSTEM: Randomly 8 words are selected.\n\n");

				for (i = 0; i < 8; i++)
				{
					printf("%s ",randomKeys[i]);
				}


				printf("\n\nPROCESS: Seaching these 8 word in BS Tree.\n\n");   No time to finish
		*/	

				break;






            case 4:
                printf("\n-------------------------------- IMPLEMENTATION --------------------------------\n");
                printf("\t\t\t\t  Authors:\n\n\t\t\tGuray Sun - 1862838 \n\t\t\tEmre Akin - 1862457 \n\n\t\t\tLecturer: Yeliz Yesilada \n\t\t\tLab Instructor: Pinar Uyanik Sonmez \n\n\t\t\t");
                break;


			case 5:
                loopLock = FALSE;
                break;


            default:
                printf("\n\n");
                printf("WARNING: Command not recognized\n");
                break;
        }
    }



    strcpy(outputBST,"BST.txt");
    strcpy(outputAVLT,"AVLT.txt");



    if ( ( outFile = fopen(outputBST,"w")) == NULL)
    {
        printf("\nFailed to create the file.\n");
        exit(1);
    }

    if ( ( outFile = fopen(outputAVLT,"w")) == NULL)
    {
        printf("\nFailed to create the file.\n");
        exit(1);
    }

    if ( ( outFile = fopen(outputFile,"w")) == NULL)
    {
        printf("\nFailed to create the file.\n");
        exit(1);
    }


    WriteFileBST (BST, outputBST);
	WriteFileBST (BST, outputFile);

    WriteFileAVLT (AVLT, outputAVLT);
	WriteFileAVLT (AVLT, outputFile);

  //     BST = PrintBinaryTreeStructure(BST,0);

  //  printf("\n\n--------\n\n%s\n\n--------\n\n",content);




    printf("\nterminating...\n");
    system("PAUSE");
    return 0;
}








void WriteFileBST (Tree t, char* outputFile)
{
    FILE *outFile;


    if (t !=NULL)
    {
        WriteFileBST(t->left,outputFile);


        if ( ( outFile = fopen(outputFile,"a+")) == NULL)
        {
            printf("\nFailed to create the file.\n");
            exit(1);
        }
        else
        {
            fprintf(outFile,"%d\t%s\n",t->count,t->val);
        }


        fclose(outFile);

        WriteFileBST(t->right,outputFile);
    }
}



void WriteFileAVLT (AVLTree t, char* outputFile)
{
    FILE *outFile;


    if (t !=NULL)
    {
        WriteFileAVLT(t->left,outputFile);


        if ( ( outFile = fopen(outputFile,"a+")) == NULL)
        {
            printf("\nFailed to create the file.\n");
            exit(1);
        }
        else
        {
            fprintf(outFile,"%d\t%s\n",t->count,t->val);
        }


        fclose(outFile);

        WriteFileAVLT(t->right,outputFile);
    }
}









