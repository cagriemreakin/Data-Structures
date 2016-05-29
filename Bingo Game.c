/*
	CNG 213: Data Structures
	Assignment 1: Bingo Game
	Date: 20.10.2012
 	Description:Bingo is a game of chance played with randomly drawn numbers, which players match against
                numbers that have been pre-printed. The matrices may be printed on paper, card stock or
                electronically represented and are referred to as cards. Many versions conclude the game
                when the first person achieves a specified pattern from the drawn numbers. The winner is usually
                required to call out the word "Bingo!", which alerts the other players and caller of a possible win.


	Çagri Emre Akin 
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CARD_ROW 3
#define CARD_COLUMN 9


struct BingoCardNumber  
{
	int number;
	int flag;
};

struct BingoCard
{
	struct BingoCardNumber cell[CARD_ROW][CARD_COLUMN];			
};


struct BingoCard generateBingoCard (int, int); //--->It is used for genereting Bingo Cards 
void DisplayBingoCard (struct BingoCard);      //--->It is used for displaying Bingo Cards 
int drawNumber (int *,int *);                  //--->It is used for drawing random number 
void checkNumber (struct BingoCard *, int);    //--->It is used for checking number
void checkWinner (struct BingoCard *,int);     //--->It is used for checking winner
void SelectionSort (int *, int );              //--->It is used for sorting the numbers


void main (void)
{
	int i, j, playerNum, opselect, selection, allOrOne, randomNum = -1, handNum;
	struct BingoCard *cards;

	int drawArray[90];
	int limit = 90;

	//	This is our bag..
	for (i = 0; i < 90; i++)
	{
		drawArray[i] = i + 1;
	}

	srand ( (unsigned)time ( NULL ) );		

	printf("\n\t\t:::\tBINGO GAME\t:::\n\n");
	printf("    Enter the number of players that will play the game\n\n>> ");   
	scanf("%d",&playerNum);                                                     //---------> gets the number of player

	cards = (struct BingoCard *) malloc(playerNum * sizeof(struct BingoCard));  //--------->dynamic memory allocation for cards

	if (cards == (struct BingoCard *) NULL)                                     //--------->checking the memory allocated or not
    {
         printf("\nFailed to allocate integer array of size %d\n", playerNum);
         exit(1);
    }

	for (i = 1; i <= playerNum; i++)                                            //----->calling generate function for each card
	{
		*(cards + i) = generateBingoCard (CARD_ROW, CARD_COLUMN);
//		DisplayBingoCard (cards[i]);
	}

	printf("\nPlayer Cards has been generated!\n");

	while (1)                                                                   
	{
		printf("\nPlease select an option:\n");
		printf("\n\t 1) Draw a number\n\t 2) Check Cards\n\t 3) Display the card of a player\n\t 4) Boost up the program :)\n\n>> ");
		scanf("%d",&opselect); 

		switch (opselect)               
		{
			case 1:                                                     
				randomNum = drawNumber(drawArray, &limit);            
				printf("\nLucky Number: %d\n",randomNum);
				break;

			case 2:                                                     
				printf("\n>> Automatically checking all cards!\n");

				for (i = 1; i <= playerNum; i++)
				{
					printf("\n\n>> For Player %d\n",i);
					checkNumber(&cards[i],randomNum);            //-------->calling the checkNumber function
				}
				

				for (i = 1; i <= playerNum; i++)
				{
					printf("\n\n>> For Player %d\n",i);
					checkWinner (&cards[i],i);                   //-------->calling the checkWinner function
				}

				break;

			case 3:
				printf("\n>> Do you want to show all cards or only one?\n   (for all enter 0, for one enter 1)\n>> ");
				scanf("%d",&allOrOne);

				if (allOrOne == 0)
				{
					for (i = 1; i <= playerNum; i++)
					{
						printf("\n\n>> Player %d\n",i);
						DisplayBingoCard (cards[i]);             //-------->calling DisplayBingoCard function
					}
				}

				else if (allOrOne == 1)
				{
					printf("\nChoose a player: ");
					scanf("%d",&selection);
					printf("\n\n>> Player %d\n",selection);
					DisplayBingoCard (cards[selection]);
				}
				printf("\nPress any key to continue!\n");
				getchar();
				getchar();
				break;
			case 4:
				printf("\n>> How many numbers do you want to draw and check automatically?\n   (Maximum: %d)\n>> ",limit);
				scanf("%d",&handNum);

				for (j = 0; j < handNum; j++)
				{
					randomNum = drawNumber(drawArray,&limit);

					for (i = 1; i <= playerNum; i++)
					{
						checkNumber(&cards[i],randomNum);
						checkWinner (&cards[i],i);
					}
				}

				break;
			default:
				printf("\n>> You have to choose a number from menu!\n");
				break;
		}
		
	printf("\n\t::::::\t::::::\t::::::\t::::::\t::::::\n");
	}

	getchar();
	getchar();
}

struct BingoCard generateBingoCard (int cardRow, int cardColumn)
{
	int i, j, k, temp, check = 0;
	int columnCheck[9], cells[27], killList[12];
	struct BingoCard tempCards;

	//	Generating random unique numbers for all 27 cells

	for (i = 0; i < 9; i++)
    {
		columnCheck[i] = 0;
	}

//	cells[0] = ( rand() % 90 ) + 1;

	for (i = 0; i < 27; i++)                   //----->assings the random number to card cells 
    {
		check = 0;

		if (columnCheck[0] != 3)
		{	temp = ( rand() % 10 ) + 1;   }
		else if (columnCheck[1] != 3)
		{	temp = ( rand() % 10 ) + 10;   }
		else if (columnCheck[2] != 3)
		{	temp = ( rand() % 10 ) + 20;   }
		else if (columnCheck[3] != 3)
		{	temp = ( rand() % 10 ) + 30;   }
		else if (columnCheck[4] != 3)
		{	temp = ( rand() % 10 ) + 40;   }
		else if (columnCheck[5] != 3)
		{	temp = ( rand() % 10 ) + 50;   }
		else if (columnCheck[6] != 3)
		{	temp = ( rand() % 10 ) + 60;   }
		else if (columnCheck[7] != 3)
		{	temp = ( rand() % 10 ) + 70;   }
		else if (columnCheck[8] != 3)
		{	temp = ( rand() % 11 ) + 80;   }

		for (j = 0; j < i; j++)
		{
		    if (temp == cells[j])
		    {
		        check = 1;
		    }
		}

		if (check == 0)
		{   
			cells[i] = temp;

			if (cells[i] / 10 == 0)
			{	columnCheck[0]++;	}
			if (cells[i] / 10 == 1)
			{	columnCheck[1]++;	}
			if (cells[i] / 10 == 2)
			{	columnCheck[2]++;	}
			if (cells[i] / 10 == 3)
			{	columnCheck[3]++;	}
			if (cells[i] / 10 == 4)
			{	columnCheck[4]++;	}
			if (cells[i] / 10 == 5)
			{	columnCheck[5]++;	}
			if (cells[i] / 10 == 6)
			{	columnCheck[6]++;	}
			if (cells[i] / 10 == 7)
			{	columnCheck[7]++;	}
			if (cells[i] / 10 == 8)
			{	columnCheck[8]++;	}
		}
		else
		{	i--;	}
	}
	
	SelectionSort(cells, 27);	//  Sorting the list
	
/*							
	printf("\n\n");				//	Showing the list to test..
	for (i = 0; i < 27; i++)
    {
		if (i % 3 == 0)
		printf("\n");
		printf("\t%d",cells[i]);	
	}
	printf("\n\n");
*/
	
	//	Generating a kill list to remove 4 random unique cells in each row

	for (i = 0; i < 12; i++)
	{
		check = 0;
		if (i < 4)
		{
			temp = 3*(rand() % 8);
		}
		else if (i >= 4 && i < 8)
		{
			temp = 3*(rand() % 8) + 1;
		}
		else
		{
			temp = 3*(rand() % 8) + 2;
		}


		for (j = 0; j < i; j++)
		{
		    if (temp == killList[j])
		    {
		        check = 1;
		    }
		}

		if (check == 0)
		{   killList[i] = temp;	}
		else
		{	i--;	}
	}

	//	Killing the cells :)

//	printf("Killing Cells: ");
	for (i = 0; i < 12; i++)
	{
		cells[killList[i]] = 0;
//		printf("%d ",killList[i]);
	}

/*
	printf("\n\n");					//	Showing the lastest list after killing... to test.. :)
	for (i = 0; i < 27; i++)
    {
		if (i % 3 == 0)
		printf("\n");
		printf("\t%d",cells[i]);	
	}
*/	

	//	Merging the latest list to our Structure
	k=0;

	for (j = 0; j < cardColumn; j++)
	{
		for (i = 0; i < cardRow; i++)
		{
			tempCards.cell[i][j].number = cells[k];

			if (cells[k] != 0)
			{
				tempCards.cell[i][j].flag = 1;
			}
			else
			{
				tempCards.cell[i][j].flag = -1;
			}

			k++;
		}
	}
	/* End of generateBingoCard */
	return (tempCards);
}


void DisplayBingoCard (struct BingoCard cards)      //--->Display the cards of each player
{
	int i, j;
	// Showing the Structure Table

	for (j = 0; j < CARD_COLUMN; j++)
	{
		for (i = 0; i < CARD_ROW; i++)
		{
			printf("%d\t",cards.cell[i][j].number);			
		}
		printf("\n");
	}
//	printf("\nCHECK!\n");
}





int drawNumber (int *tempArray, int *limit)           // drawing random number 
{
	int randomNum, chance;
/*	int j;														// Showing drawNumber bag :) to test...
	printf("\n-------------------left numbers in array-------------------\n\n");
	for (j = 0; j < 90; j++)
	{
		printf("%d ",tempArray[j]);
	}
	printf("\nlimit %d\n",*limit);
*/
	chance = (rand() % *limit);           

	randomNum = tempArray[chance];
	tempArray[chance] = tempArray[*limit - 1];
	tempArray[*limit - 1] = 0;
	*limit = *limit - 1;  

	return randomNum;
}





void checkNumber (struct BingoCard *tempCard, int randomNum)
{
	int i,j,check = 0;

	for (i = 0; i < CARD_COLUMN; i++)
	{
		for (j = 0; j < CARD_ROW; j++)
		{
			if (tempCard->cell[j][i].number == randomNum)
			{
				tempCard->cell[j][i].flag = 0;
				printf("\n\t The number %d is on the card! It's crossed!",randomNum);
				check = 1;
			}	
		}
	}

	if (check == 0)
		printf("\n\t No match!");
}





void checkWinner (struct BingoCard *tempCard, int player)
{
	int i, j, counter = 0;

	for (i = 0; i < CARD_COLUMN; i++)
	{
		for (j = 0; j < CARD_ROW; j++)
		{
			if (tempCard->cell[j][i].flag == 0)
			{
				counter++;
			}	
		}
	}

	if (counter == 15)
	{
		printf("\a\n\n\t::: BINGO :::\n\n");
		printf(">> Player %d Won the game!\n\n",player);
		
		getchar();
		getchar();
		exit(1);
	}
	else
	{
		printf("\n>> %d number of player %d has crossed so far. %d number left to win\n\n",counter,player,15-counter);
	}
}





void SelectionSort(int *a, int n)
{
    int i, j, min, minIndex, temp, numberSwaps;
       
    numberSwaps = 0;
       
    for (i = 0; i < n - 1; i++)
    {
        min = a[i];
        minIndex = i;
               
        for (j = i + 1; j < n; j++)
        {
            if (a[j] < min)
            {
                    min = a[j];
                    minIndex = j;
            }
        }
               
        if (min < a[i])
        {
            temp = a[i];
            a[i] = min;
            a[minIndex] = temp;
            numberSwaps++;
        }
    }
//    return numberSwaps;
}
