#include  <pthread.h>
#include  <stdio.h>
#include  <stdlib.h>
#include <limits.h>
#include <math.h>


#define  NUMBER_OF_THREADS          1


void *primenumbercalculator(void *params);
int isprime();

int  average;
int min = INT_MAX;
int prime;

// int  result[SIZE];

int  main (int argc , const  char * argv[]){

    printf("please enter prime ");

    scanf("%d",& prime);

    pthread_t workers[NUMBER_OF_THREADS];

    pthread_create (& workers[0], 0, primenumbercalculator , NULL);



    pthread_join(workers[0], NULL);

    
}

/*** Sorting  thread.** This  thread  can  essentially  use any  algorithm  for  sorting*/
void *primenumbercalculator(void *params)
{   
    for (int i = 0; i < prime; i++){
        if (isprime(i) == 1){
            printf("%d ", i);
        }
    }
}
int isprime(int n) {
    int i, flag = 1;
    
    // Iterate from 2 to sqrt(n)
    for (i = 2; i <= sqrt(n); i++) {
        // If n is divisible by any number between
        // 2 and n/2, it is not prime
        if (n % i == 0) {
            flag = 0;
            break;
        }
    }
 
    if (n <= 1)
        flag = 0;
 
    return flag;
}