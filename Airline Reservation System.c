/*
    Çaðrý Emre Akýn     1862457

    Project 2 - Airline Reservation System
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct passengerNode
{
	char *Name;
	struct passengerNode *Next;
};

struct flightRecord
{
	int flightNo;
	int capacity;
	int reservationCount;
	struct passengerNode * passengerListHead;
	struct passengerNode * waitingListHead;
	struct passengerNode * waitingListTail;
	struct passengerNode * passengerListTail;
};

typedef struct flightRecord *Flight;

/*
Flight CreateRecord (void);
void MakeEmptyRecord (Flight);
*/
Flight initialise (int *);
void processCommands (Flight, int *);
void reserve (Flight, char *, int, int*);
void status (Flight, int *);
void cancel ();
void inquire ();



int main()
{
	int opselect, totalFlight;

    Flight myRecord;

    while (1)
    {
        printf("\nAirline Reservation System\n");
        printf("MENU\n");
        printf("\t1. Initialise Records \n\t2. Enter a command \n\nSELECTION: ");
        scanf("%d",&opselect);

        switch (opselect)
        {
            case 1:
                myRecord = initialise (&totalFlight);
                break;

            case 2:
                processCommands (myRecord,&totalFlight);
                break;

            default:
                printf("ERROR \n\n");
                break;

        }

   //     printf("--> total flight: %d",totalFlight);
    }


	return 1;
}



/*
Flight CreateRecord (void)
{
	Flight record;

	record = (struct flightRecord *) malloc (sizeof(struct flightRecord));

	if (record == NULL)
	{
		printf("\nFailed to allocate enough memory\n");
		exit(1);
	}

	MakeEmptyRecord (record);
	return record;
}

void MakeEmptyRecord (Flight record)
{
	record->passengerListHead = (struct passengerNode *) malloc(sizeof(struct passengerNode));
	if (record->passengerListHead == NULL)
		printf("Out of memory!\n");

	record->passengerListHead->Next = NULL;
	record->passengerListTail = record->passengerListHead;
	record->capacity = 0;
}

*/


Flight initialise (int *totalFlight)
{
	char line[81];
	int count = -1;
	int i = 0, j = 0,n,c=0;
	char string[81];
    Flight record;
//  -------------------------------------------------------------------------

//  -------------------------------------------------------------------------

	FILE *inFile;

	inFile = fopen("airline.txt","r");

	if (inFile == NULL)
	{
		printf("\nFailed to open the file.\n");
		exit(1);
	}

	while (fgets(line,81,inFile) != NULL)
	{
		if (count == -1)
		{
			*totalFlight = atoi(line);
//			printf("--> total flight: %d",*totalFlight);

			record = (struct flightRecord *) malloc ((*totalFlight)*sizeof(struct flightRecord));

            if (record == NULL)
            {
                printf("\nFailed to allocate enough memory!    3\n");
                exit(1);
            }

            while ( c != *totalFlight)
            {
                record[c].passengerListHead = (struct passengerNode *) malloc(sizeof(struct passengerNode));

                if (record[c].passengerListHead == NULL)
                    printf("Out of memory!\n");

                record[c].waitingListHead = (struct passengerNode *) malloc(sizeof(struct passengerNode));

                if (record[c].waitingListHead == NULL)
                    printf("Out of memory!\n");

                record[c].passengerListHead->Next = NULL;
                record[c].waitingListHead->Next = NULL;
                record[c].passengerListHead->Name = " ";
                record[c].waitingListHead->Name = " ";

     //           record[c].passengerListTail = record[c].passengerListHead;
     //           record[c].waitingListTail = record[c].waitingListHead;

                c++;
            }

		}
		else
		{
            while (line[j] != '\0')
		    {
                if (line[j] == ' ')
                {
                    record[count].flightNo = atoi(string);
                    for (c = 0; c < 81; c++)
					string[c] = ' ';
                    i = 0;
                    j++;

                }
                else
                {
                    string[i] = line[j];
                    string[i+1] = '\0';
                    i++;
                    j++;
                }
            }
            i = 0;
            j = 0;

            record[count].capacity = atoi(string);
            record[count].reservationCount = 0;
		}
		printf("flight no: %d\n",record[count].flightNo);
		printf("capacity: %d\n",record[count].capacity);
		count++;

		printf("count: %d\n",count);
	}

    fclose(inFile);

    return (record);
}



void processCommands (Flight record, int *totalFlight)
{
    char *number, *line, entry[81], tempEntry[81], command[81], string[81], name[81];
    int i = 0,j = 0,check = 0,flightNo,c;

    char key[] = "0123456789";

    fflush(stdin);
    printf("Enter your command: ");
    gets(entry);
    fflush(stdin);

//	printf("Rewrite --> %s\n",entry);

	if (strcmp (entry,"STATUS") == 0)
	{
        status(record, totalFlight);
    }
	else
	{

		strcpy(tempEntry,entry);
		line = strtok(tempEntry,key);
		number = strpbrk(entry,key);

		while (line[j] != '\0')
		{
			if (line[j] == ' ' && check == 0)
			{
				strcpy(command,string);
				for (c = 0; c < 81; c++)
				string[c] = ' ';
				check = 1;
				i = 0;
				j++;
			}
			else if (check == 1)
			{
				name[i] = line[j];
				name[i+1] = '\0';
				i++;
				j++;
			}
			else
			{
				string[i] = line[j];
				string[i+1] = '\0';
				i++;
				j++;
			}
		}
		i = 0;
		j = 0;


	//	printf("flightno: %d",flightNo);
		printf("line: %s\n",line);
		printf("number: %s\n",number);
		printf("command: %s\n",command);
		printf("name: %s\n",name);


		if (strcmp (command,"CANCEL") == 0)
		{
			flightNo = atoi(number);
			cancel();
		}
		else if (strcmp (command,"RESERVE") == 0)
		{
			flightNo = atoi(number);
			reserve(record,name,flightNo,totalFlight);
		}
		else if (strcmp (command,"INQUIRE") == 0)
		{
			inquire();
		}
		else
		{
			printf("\a\nWARNING: Command is not proper\n");
		}
	}


}



void reserve (Flight record, char *passengerName, int flightNum, int *totalFlight)
{
    int n, i = 0;
    struct passengerNode *newNode;

    newNode = (struct passengerNode *) malloc(sizeof(struct passengerNode));

	strcpy (newNode->Name,passengerName);
	newNode->Next = NULL;


    if (newNode == NULL)
    {
        printf("Failed to allocate enough memory!\n");
        exit(1);
    }

    while (i != *totalFlight)
    {
        if (record[i].flightNo == flightNum)
        {
            n = i;
        }
        i++;
    }


    if (record[n].capacity <= record[n].reservationCount)
    {                                                           /*    Assigning Nodes to waitingList   */
        printf("There is no capacity any more\nPassenger is in waiting list now.\n");

        record[n].flightNo = flightNum;

        record[n].waitingListHead->Next = newNode;
        record[n].waitingListHead = newNode;
    }
    else
    {                                                           /*    Assigning Nodes to passengerList   */
        record[n].flightNo = flightNum;
        record[n].reservationCount++;

        record[n].passengerListHead->Next = newNode;
		record[n].passengerListHead = newNode;

    }

//    printf("-->  %s\n",record[n].passengerListHead->Name);

}

void status (Flight record, int *totalFlight)
{
	struct passengerNode *p;
	int count,i=0;

	while (i != *totalFlight)
	{
		count = 1;
        printf("\n-------------------------------------------------------------------------\n");
		printf("FlightNo: %d\tCapacity: %d\t Number of Reservation: %d\n", record[i].flightNo,record[i].capacity,record[i].reservationCount);
		printf("Flight Passenger Details:\n");

        p = record[i].passengerListHead;

		while (p != NULL)
		{
			printf("    %d. %s",count,p->Name);
			p = p->Next;
			count++;
		}
        i++;
	}

}
void cancel ()
{
    /*


    */

}
void inquire ()
{

}





