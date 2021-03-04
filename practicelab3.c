#include  <pthread.h>
#include  <stdio.h>
#include  <stdlib.h>
#define  SIZE                        13
#define  NUMBER_OF_THREADS          3

void *sorter(void *params);      /*  thread  that  performs  basic  sorting  algorithm*/
void *merger(void *params);      /*  thread  that  performs  merging  of  results  */
int  list[SIZE] = {7,12,19,17,23,3,18,4,2,6,15,1,8};
int  result[SIZE];

typedef struct
{

}

typedef  struct
{
      int* listofnums;

} parameters;

int  main (int argc , const  char * argv[]){

    parameters* data = malloc(sizeof(parameters));
    
    data->listofnums = (int *)malloc((argc-1)*sizeof(int));

    for (int i = 1; i < argc; i++){
        data->listofnums[i] = strtol(argv[i], NULL, 10);
	printf("%d ", data->listofnums[i]);
    }

    int i;
    pthread_t workers[NUMBER_OF_THREADS];
    /*  establish  the  first  sorting  thread  */
    parameters *data = (parameters  *)  malloc (sizeof(parameters));
    data ->from_index = 0;
    data ->to_index = (SIZE /2) - 1;
    pthread_create (& workers[0], 0, sorter , data);
/*  establish  the  second  sorting  thread  */
    data = (parameters  *)  malloc (sizeof(parameters));
    data ->from_index = (SIZE /2);
    data ->to_index = SIZE - 1;
    pthread_create (& workers[1], 0, sorter , data);
/* now  wait  for  the 2 sorting  threads  to  finish  */
    for (i = 0; i < NUMBER_OF_THREADS  - 1; i++)
        pthread_join(workers[i], NULL);/*  establish  the  merge  thread  */
    data = (parameters  *)  malloc(sizeof(parameters));
    data ->from_index = 0;
    data ->to_index = (SIZE /2);
    pthread_create (& workers[2], 0, merger , data);
    /* wait  for  the  merge  thread  to  finish  */
    pthread_join(workers[2], NULL);
    /*  output  the  sorted  array */
    for (i = 0; i < SIZE; i++)
        printf ("%d   ",result[i]);
        printf ("\n");
        return  0;
        }

/*** Sorting  thread.** This  thread  can  essentially  use any  algorithm  for  sorting*/
void *sorter(void *params)
{   
}
/** Merge  thread** Uses  simple  merge  sort  for  merging  two  sublists*/
void *merger(void *params){
    parameters* p = (parameters  *) params;
    int i,j;
    i = p->from_index;
    j = p->to_index;
    int  position = 0;         /*  position  being  inserted  into  result  list */
    while (i < p->to_index  && j < SIZE) {
        if (list[i]  <= list[j]) {
            result[position ++] = list[i];
            i++;
            }
        else {
            result[position ++] = list[j];
            j++;
            }
        }/* copy  the  remainder  */
        if (i < p->to_index) {
            while (i < p->to_index) {
                result[position] = list[i];
                position ++;
                i++;
            }
        }
        else {
            while (j < SIZE) {
                result[position] = list[j];
                position ++;
                j++;
            }
        }
        pthread_exit (0);
    }
