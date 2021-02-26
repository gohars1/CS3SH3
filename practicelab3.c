#include  <pthread.h>
#include  <stdio.h>
#include  <stdlib.h>
#include <limits.h>

#define  NUMBER_OF_THREADS          3


void *averagelist(void *params);
void *minimumval(void *params);
void *maximumval(void *params);
int  average;
int min = INT_MAX;
int max = INT_MIN;

// int  result[SIZE];

typedef  struct
{   int  from_index;
    int to_index;
} parameters;

typedef  struct
{
      int* listofnums;
      int size;

} listofint;

int  main (int argc , const  char * argv[]){

    listofint* intdata = malloc(sizeof(listofint));
    
    intdata->listofnums = (int *)malloc((argc-1)*sizeof(int));
    intdata->size = argc-1;

    for (int i = 1; i < argc; i++){
        intdata->listofnums[i-1] = strtol(argv[i], NULL, 10);
    }

    int i;
    pthread_t workers[NUMBER_OF_THREADS];

    pthread_create (& workers[0], 0, averagelist , intdata);

    pthread_create (& workers[1], 0, minimumval , intdata);

    pthread_create (& workers[2], 0, maximumval , intdata);

    pthread_join(workers[0], NULL);
    pthread_join(workers[1], NULL);
    pthread_join(workers[2], NULL);

    free(intdata->listofnums);
    free(intdata);
    
}

/*** Sorting  thread.** This  thread  can  essentially  use any  algorithm  for  sorting*/
void *averagelist(void *params)
{   
    listofint* intdata = (listofint*)params;
    int sum = 0;
    for (int i = 0; i < intdata->size; i++){
        sum += intdata->listofnums[i];
    }
    average = sum / intdata->size;
    printf("The average value is %d \n", average);


}

void *minimumval(void *params)
{   
    listofint* intdata = (listofint*)params;
    // printf("%d", intdata->size);
    for (int i = 0; i < intdata->size; i++){
        if (intdata->listofnums[i] < min){
            min = intdata->listofnums[i];
        }
    }
    printf("The minimum value is %d \n", min);
}

void *maximumval(void *params)
{   
    listofint* intdata = (listofint*)params;
    for (int i = 0; i < intdata->size; i++){
        if (intdata->listofnums[i] > max){
            max = intdata->listofnums[i];
        }
    }
    printf("The maximum value is %d \n", max);
}