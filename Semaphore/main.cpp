//
//  main.cpp
//  CECS 326 - Semaphore project
//
//  Created by Kacy Rowe on 12/7/18.
//  Copyright © 2018 Kacy Rowe. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "semaphore.h"

using namespace std;

// Prototypes
void personalCheckingDeposit(SEMAPHORE& semaphore, float* pointer, int& reference);
void personalCheckingWithdraw(SEMAPHORE& semaphore, float* pointer, int& reference);
void personalCheckingTransfer(SEMAPHORE& semaphore, float* point, int& reference);
void bankerFunction10(SEMAPHORE& semaphore, float* pointer, int& reference);
void parent_cleanup(SEMAPHORE& semaphore, float value);

// Global variables
const int BUFFERSIZE = 3; //buffer size constant
float CHECKINGDEPOSIT = 200; 
float WITHDRAWFROM = 100; 
float TRANSFERTO = 75; 
float SPEND = 60; 
enum {deposit, withdraw, transfer}; //from bounded buffer problem


int main()
{
  //Shared variable initialization
  int counter = 0;
  float sharedfloat = 500;
  float sharedfloat2 = 500; 
  float sharedfloat3 = 500; 
  int count = 1; //operations
  long childPID;
    
  //Buffer initialization
  float shmid;
  float* shmBUF;
  shmid = shmget(IPC_PRIVATE, BUFFERSIZE*sizeof(float& ), PERMS);
  shmBUF = (float *)shmat(shmid, 0, SHM_RND); //shmBUF points to new buffer memory
  *(shmBUF + 0) = sharedfloat;//load the shared variables into buffer
  *(shmBUF + 1) = sharedfloat2;
  *(shmBUF + 2) = sharedfloat3;

  //Semaphore initialization
  SEMAPHORE semaphore(3);
  semaphore.V(deposit);
  semaphore.V(withdraw);
  semaphore.V(transfer);

  while (counter < 3)
  {
    childPID = fork(); //fork process
    if (childPID == -1)
    {
      cout << "Failed to create child process" << endl;
      exit(0);
    }
    else if (childPID == 0)
    {
      bankerFunction10(semaphore, shmBUF, count);
      exit(0);
    }
    else
    {
        cout << "Child process: " << counter + 1 << " pid: " << getpid() << endl;
    }
    counter++;
  }
  bankerFunction10(semaphore, shmBUF, count);
  for (int i = 0; i < 3; i++)
  {
    //ending child processes
    wait(NULL);
  }
  parent_cleanup(semaphore, shmid); // cleaning house
  cout << "Cleaning house, closed all semaphores" << endl;
  return 0;
}

void depositSavings(SEMAPHORE& semaphore, float* shmBUF, int& count)
{
    float* sharedfloat;
    semaphore.P(deposit); //put deposit into semaphore
    sharedfloat = shmBUF; //deposit amount into buffer
    *sharedfloat = *sharedfloat + deposit; //make deposit into savings
    cout << getpid() << ": " << count << endl;
    cout << "Depositing to savings: " << deposit << " with " << *sharedfloat << endl;
    count++;
    semaphore.V(deposit);
}

void withdrawChecking(SEMAPHORE &semaphore, float *shmBUF, int& count)
{
    float* sharedfloat2; //shared value pointer
    semaphore.P(withdraw); //put withdraw into semaphore
    sharedfloat2 = shmBUF + 1; //put shared variable into buffer
    if (withdraw < *sharedfloat2)
    {
        *sharedfloat2 = *sharedfloat2 - withdraw;
        cout << getpid() << ": " << count << endl;
        cout << "Withdrawing from checking: " << withdraw << " with " << *sharedfloat2  << endl;
        count++; //increment counter
    }
    semaphore.V(withdraw);
}

void personalCheckingTransfer(SEMAPHORE& semaphore, float* shmBUF, int& count)
{
    float* sharedfloat; //point to shared variable
    float* sharedfloat3; //shared variable
    semaphore.P(deposit);
    semaphore.P(transfer);
    sharedfloat = shmBUF; //put shared variables into buffer
    sharedfloat3 = shmBUF + 2;
    
}

void bankerFunction10(SEMAPHORE& semaphore, float* shmBUF, int& count)
{
    srand( unsigned(time(NULL)));
    double randomNumber;
    while (count < 11)
    {
        //generate random number between -0.5 and 0.5 inclusive
        randomNumber =  ((rand() % 11) * .1) + (-.5);
        if (randomNumber > 0)
        {
            depositSavings(semaphore, shmBUF, count);
        }
        else if (randomNumber < 0)
        {
            withdrawChecking(semaphore, shmBUF, count);
        }
        else if(randomNumber == 0)
        {
            personalCheckingTransfer(semaphore, shmBUF, count);
        }
    }
}

void parent_cleanup (SEMAPHORE& semaphore, float shmid)
{
    // cleaning house of parent processes
    int status;            /* child status */
    wait(0);            /* wait for child to exit */
    //deallocates the shared memory
    shmctl(shmid, IPC_RMID, NULL);    /* cleaning up */
    semaphore.remove();            //deallocates the semaphores
} // parent_cleanup
