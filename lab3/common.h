//+
//  common.h - Common definiton of the shared
//     memory segment and prototypes for semaphore functions
// 
//  Created by Thomas Dean
//  Copyright 2005 Queen's University.
//
//-

#define MEMSIZE 200
#define BUFFSIZE 5

struct shared {
    // synchronization variable
    int lock;
    //keep track of producers how many producers are generating data
    int numProducers;
    //shared buffer
    char buffer[BUFFSIZE];
    int in;
    int out;
    int count;
};


void getMutex(int * lock);
void releaseMutex(int * lock);
