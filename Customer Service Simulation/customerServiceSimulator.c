/*
    Customer Service Simulator

    Authors: Чa№r§ Emre Akin

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "CustomerQueue.h"
#include "EventQueue.h"
#include "ClockQueue.h"

#define FALSE 0
#define TRUE 1
#define BUSY 0
#define AVAILABLE 1


struct Statistics
{
    int numberOfTellers;
    int numberOfCustomers;
    float totalServiceTime;
    float *customerDelayTime;
    float maximumDelayTime;
    float averageSpentTime;
    float previousDepartTime;
};


void GenerateRandomValues (float, float, float *, float *);
void GenerateCustomerQueue (CustomerQueue,int, float, float);
void customerArrive (CustomerQueue, CustomerQueue[], EventQueue, int, int[], float, float, struct Statistics *, int *);
void customerServiceFinished (CustomerQueue, CustomerQueue[], EventQueue, int, int[], float, float, struct Statistics *);
void GenerateReport (EventQueue, struct Statistics *);


int main()
{
    int i, count, exit, opselect, tellers, customers, loopLock = TRUE;
    float simulationTime, avgServiceTime, clock = 0.0;
    char ch, command[80], *string;

    struct Statistics Bank;

    Bank.numberOfCustomers = 0;
    Bank.numberOfTellers = 0;
    Bank.totalServiceTime = 0.0;
//    Bank.customerDelayTime = (float *) malloc(sizeof(float));
    Bank.maximumDelayTime = 0.0;
//    Bank.averageSpentTime = (float *) malloc(sizeof(float));
    Bank.previousDepartTime = 0.0;


    CustomerQueue cQueue, *tellerQueue;
    EventQueue eQueue;
    ClockQueue runTimeQueue;

    cQueue = CreateCustomerQueue();
    eQueue = CreateEventQueue();
    runTimeQueue = CreateClockQueue();

    struct customerNode *customerTraverser;
    struct clockNode *clockTraverser;

    printf("лллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллл");
    printf("лллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллл");
    printf("лллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллллл");
    printf("ФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФ\n");
    printf("\t\t\t  CUSTOMER SERVICE SIMULATOR\n");

    while (loopLock == TRUE)
    {
        fflush(stdin);
        printf("\nФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФ\n");
        printf("ллллллллллллллллллллллллллллллллл SYSTEM MENU лллллллллллллллллллллллллллллллллл\n\n\t\t\t1 : Enter Command \n\t\t\t2 : About \n\n\t\t\tSelection: ");
        scanf("%d", &opselect);
        fflush(stdin);

        switch(opselect)
        {
            case 1:
                printf("\nФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФ\n");
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

                if (strcmp(string,"customerServiceSimulator") != 0)
                {
                    printf("\nФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФ\n");
                    printf("WARNING: Command not recognized\n");
                }
                else
                {
                    loopLock = FALSE;
                    count = 0;

                    while (string != NULL)
                    {
                        string = strtok(NULL," ");

                        if (count == 0)
                            customers = atoi(string);

                        else if (count == 1)
                            tellers = atoi(string);

                        else if (count == 2)
                            simulationTime = atof(string);

                        else if (count == 3)
                            avgServiceTime = atof(string);

                        count++;
                    }

                    Bank.numberOfTellers = tellers;


                    if (IsEmptyCustomerQueue(cQueue))
                    {
                        GenerateCustomerQueue(cQueue, customers, simulationTime, avgServiceTime);
                    }

					tellerQueue = (CustomerQueue *) malloc(tellers * sizeof(CustomerQueue));

                    for (i = 0; i < tellers; i++)
                    {
                        tellerQueue[i] = CreateCustomerQueue();
                    }
                }

                break;

            case 2:
                printf("\nлллллллллллллллллллллллллллллллл IMLEMENTATION ллллллллллллллллллллллллллллллллл\n");
                printf("\t\t\t\t  Authors:\n\n\t\t\tGuray Sun - 1862838 \n\t\t\tEmre Akin - 1862457 \n\n\t\t\tLecturer: Yeliz Yesilada \n\t\t\tLab Instructor: Pinar Uyanik Sonmez \n\n\t\t\t");
                break;


            default:
                printf("\nФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФ\n");
                printf("WARNING: Command not recognized\n");
                break;
        }
    }


    int tellerStatus[tellers];                  //  initialize tellerStatus array

    for (i = 0; i < tellers; i++)
    {
        tellerStatus[i] = AVAILABLE;            //  assigning all tellerStatus elements as AVAILABLE
    }


    printf("\nФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФ\n");

//    printf("Customer");
//    DisplayCustomerQueue(cQueue);               //  displaying cQueue
//    printf("\n\n");
//    printf("\nClock: %f\n",clock);              //  displaying runtime clock

    customerTraverser = cQueue->front->next;

    int atLeastOneAvailable = 0;
    int flagMinQueue = 0;



    while (customerTraverser != NULL)
    {

        for (i = 0; i < tellers; i++)
        {
            if (tellerStatus[i] == AVAILABLE)
            {
                atLeastOneAvailable = 1;
            }
        }


        InsertClock(runTimeQueue, customerTraverser->arrivalTime, 1);

        if (atLeastOneAvailable == 0)    // none of tellers are available
        {
            if (tellerQueue[flagMinQueue]->rear->arrivalTime + tellerQueue[flagMinQueue]->rear->serviceTime > customerTraverser->arrivalTime + customerTraverser->serviceTime)
            {
                InsertClock(runTimeQueue, tellerQueue[flagMinQueue]->rear->arrivalTime + tellerQueue[flagMinQueue]->rear->serviceTime + customerTraverser->serviceTime, 2);
            }
        }
        else
        {
            InsertClock(runTimeQueue, customerTraverser->arrivalTime + customerTraverser->serviceTime, 2);
        }

        customerTraverser = customerTraverser->next;

    }

//    DisplayClockQueue(runTimeQueue);                          //   Displaying runtime Queue
//    system("pause");

    clockTraverser = runTimeQueue->front->next;

    while (clock <= simulationTime && !IsEmptyCustomerQueue(cQueue))
    {
        if (clockTraverser->type == 1)
        {
            clock = clockTraverser->clock;
//            printf("\nClock: %f   Type 1 has run\n",clock);
            DequeueClock(runTimeQueue);
            clockTraverser = runTimeQueue->front->next;
            customerArrive(cQueue, tellerQueue, eQueue, tellers, tellerStatus, clock, simulationTime, &Bank, &flagMinQueue);
        }
        else if (clockTraverser->type == 2)
        {
            clock = clockTraverser->clock;
  //          printf("\nClock: %f   Type 2 has run\n",clock);
            DequeueClock(runTimeQueue);
            clockTraverser = runTimeQueue->front->next;
            customerServiceFinished (cQueue, tellerQueue, eQueue, tellers, tellerStatus, clock, simulationTime, &Bank);
        }
        else
        {
            printf("\nWARNING: RunTime Queue has an element with unknown type!\n");
            printf("\nType: %d\n",clockTraverser->type);
            system("pause");
        }

       // system("pause");
    }



    printf("\nФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФ\n");

    GenerateReport (eQueue, &Bank);


    printf("\n\n");
    system("PAUSE");
    return 0;
}





void GenerateRandomValues(float simulationTime, float averageServiceTime, float *arrTime, float *serTime)
{
    *arrTime = simulationTime * rand() / (float) RAND_MAX;
    *serTime = 2 * averageServiceTime * rand() / (float) RAND_MAX;
}


void GenerateCustomerQueue(CustomerQueue cQueue, int customers, float simulationTime, float avgServiceTime)
{
    int ID;
    float arrTime, serTime;

    srand(time(NULL));

    for (ID = 1; ID <= customers; ID++ )
    {
        GenerateRandomValues(simulationTime, avgServiceTime, &arrTime, &serTime);
        InsertCustomer(cQueue, arrTime, serTime, ID);
    }
}



void customerArrive (CustomerQueue cQueue, CustomerQueue tellerQueue[], EventQueue eQueue, int tellers, int tellerStatus[], float clock, float simulationTime, struct Statistics *Bank, int *flagMinQueue)
{
    int i, min, count, flagAvailable;

    float arrTime, serTime;
    int ID;

    count = tellers - 1;
    flagAvailable = -1;
    *flagMinQueue = 0;

    while (count != -1)
    {
        if (IsEmptyCustomerQueue(tellerQueue[count]))
        {
            flagAvailable = count;
        }
        count--;
    }

    if (flagAvailable == -1)
    {   // none of tellers are available
        min = tellerQueue[0]->numOfCustomers;
        for (i = 1; i < tellers; i++)
        {
            if (min > tellerQueue[i]->numOfCustomers)
            {
                min = tellerQueue[i]->numOfCustomers;
                *flagMinQueue = i;
            }
        }
        InsertCustomer(tellerQueue[*flagMinQueue], cQueue->front->next->arrivalTime, cQueue->front->next->serviceTime, cQueue->front->next->ID);
        DequeueCustomer(cQueue);
        InsertEvent(eQueue, tellerQueue[*flagMinQueue]->front->next->arrivalTime, 1, tellerQueue[*flagMinQueue]->front->next->ID);

  //      printf("\nCHECK: customer Arrived via none empty   \n");
    }
    else
    {   // at least a teller is available
        InsertCustomer(tellerQueue[flagAvailable], cQueue->front->next->arrivalTime, cQueue->front->next->serviceTime, cQueue->front->next->ID);
        DequeueCustomer(cQueue);

        tellerStatus[flagAvailable] = BUSY;
        InsertEvent(eQueue, tellerQueue[flagAvailable]->front->next->arrivalTime, 1, tellerQueue[flagAvailable]->front->next->ID);

 //       printf("\nCHECK: customer Arrived via at least one available  \n");
    }
/*      //      Displaying teller Queues
        printf("\nФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФФ\n");
        for (i = 0; i < tellers; i++)
        {
            printf("%d. Teller",i+1);
            DisplayCustomerQueue(tellerQueue[i]);
            printf("\n");
        }
*/
}


void customerServiceFinished (CustomerQueue cQueue, CustomerQueue tellerQueue[], EventQueue eQueue, int tellers, int tellerStatus[], float clock, float simulationTime, struct Statistics *Bank)
{
    if (clock <= simulationTime && !IsEmptyCustomerQueue(cQueue))
    {
        int i, flagMinQueue = 0, check = 0;
        float minTime, delay, departTime, arrTime;


        for (i = 0; i < tellers; i++)
        {
            if (!IsEmptyCustomerQueue(tellerQueue[i]))
            {
                if ( clock >= (tellerQueue[i]->front->next->arrivalTime + tellerQueue[i]->front->next->serviceTime))
                {
                    flagMinQueue = i;
                }
            }
        }


        if (!IsEmptyCustomerQueue(tellerQueue[flagMinQueue]))
        {
            arrTime = tellerQueue[flagMinQueue]->front->next->arrivalTime;
            departTime = tellerQueue[flagMinQueue]->front->next->arrivalTime + tellerQueue[flagMinQueue]->front->next->serviceTime;
            InsertEvent(eQueue, clock, 2, tellerQueue[flagMinQueue]->front->next->ID);

        // start gathering statistics

        Bank->numberOfCustomers++;
        Bank->totalServiceTime = Bank->totalServiceTime + tellerQueue[flagMinQueue]->front->next->serviceTime;

        Bank->averageSpentTime = Bank->averageSpentTime + (departTime - arrTime);

        if (Bank->numberOfCustomers == 1)
        {
            Bank->customerDelayTime = (float *) malloc(Bank->numberOfCustomers * sizeof(float));
            Bank->customerDelayTime[Bank->numberOfCustomers - 1] = 0;
            Bank->previousDepartTime = clock;
        }
        else if (Bank->previousDepartTime > arrTime)
        {
            Bank->customerDelayTime = (float *) realloc(Bank->customerDelayTime, Bank->numberOfCustomers * sizeof(float));
            Bank->customerDelayTime[Bank->numberOfCustomers - 1] = Bank->previousDepartTime - arrTime;
            Bank->previousDepartTime = clock;
        }
        else
        {
            Bank->customerDelayTime = (float *) realloc(Bank->customerDelayTime, Bank->numberOfCustomers * sizeof(float));
            Bank->customerDelayTime[Bank->numberOfCustomers - 1] = 0;
            Bank->previousDepartTime = clock;
        }
         // end gathering statistics


        DequeueCustomer(tellerQueue[flagMinQueue]);

        if (IsEmptyCustomerQueue(tellerQueue[flagMinQueue]))
        {
            tellerStatus[flagMinQueue] = AVAILABLE;
        }



   //     printf("\nCHECK: customer Service Finished\n");

        }
        else
        {}
    }
    else
    {
        printf("\nTime is up!\n");
    }
}


void GenerateReport (EventQueue eQueue, struct Statistics *Bank)
{
    int i;
    float totalDelay = 0.0, averageDelayTime;

    DisplayEventQueue(eQueue);

    printf("\nлллллллллллллллллллллллллллллл SYSTEM: Statistics лллллллллллллллллллллллллллллл\n");

    printf("\n\t\t   Number of Tellers   :  %d",Bank->numberOfTellers);
    printf("\n\t\t   Number of Customers :  %d",Bank->numberOfCustomers);
    printf("\n\t\t   Total Service Time  :  %f",Bank->totalServiceTime);

    Bank->maximumDelayTime = Bank->customerDelayTime[0];

    for (i = 0; i < Bank->numberOfCustomers; i++)
    {
        totalDelay = totalDelay + Bank->customerDelayTime[i];

        if (Bank->maximumDelayTime < Bank->customerDelayTime[i])
        {
            Bank->maximumDelayTime = Bank->customerDelayTime[i];
        }
    }
    averageDelayTime = (float) (totalDelay / (float) Bank->numberOfCustomers);

    printf("\n\t\t   Average Delay Time  :  %f",averageDelayTime);
    printf("\n\t\t   Maksimum Delay Time :  %f",Bank->maximumDelayTime);
    printf("\n\t\t   Average Spent Time  :  %f",((Bank->averageSpentTime)/Bank->numberOfCustomers) );

    printf("\n\nллллллллллллллллллллллллллллллллллл The End лллллллллллллллллллллллллллллллллллл\n");

}



