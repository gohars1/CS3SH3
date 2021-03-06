#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h> 
#include <unistd.h>
  
#define NUMPHILO 5 
#define HUNGRYSTATE 1 
#define THINKSTATE 2 
#define EATINGSTATE 0 
#define RIGHTFORK (phnum + 1) % NUMPHILO
#define LEFTFORK (phnum + 4) % NUMPHILO

  
int state[NUMPHILO]; 
int phil[NUMPHILO] = { 0, 1, 2, 3, 4 }; 
sem_t mutex; 
sem_t S[NUMPHILO]; 
  
void neighbours(int phnum) 
{ 
    if (state[phnum] == HUNGRYSTATE && state[LEFTFORK] != EATINGSTATE && state[RIGHTFORK] != EATINGSTATE) { 

        state[phnum] = EATINGSTATE; 
  
        sleep(2); 
  
        printf("Philosopher %d takes fork %d and %d\n", 
                      phnum + 1, LEFTFORK + 1, phnum + 1); 
  
        printf("Philosopher %d is currently eating\n", phnum + 1); 
  
        sem_post(&S[phnum]); 
    } 
} 
  
void pickup_forks(int phnum) 
{ 
    sem_wait(&mutex); 
  
    state[phnum] = HUNGRYSTATE; 
  
    printf("Philosopher %d is currently hungry\n", phnum + 1); 
  
    neighbours(phnum); 
  
    sem_post(&mutex); 
  
    sem_wait(&S[phnum]); 
  
    sleep(1); 
} 
  
void return_forks(int phnum) 
{ 
  
    sem_wait(&mutex); 
  
    state[phnum] = THINKSTATE; 
  
    printf("Philosopher %d putting fork %d and %d down\n", 
           phnum + 1, LEFTFORK + 1, phnum + 1); 
    printf("Philosopher %d is currently thinking\n", phnum + 1); 
  
    neighbours(LEFTFORK); 
    neighbours(RIGHTFORK); 
  
    sem_post(&mutex); 
} 
  
void* philospher(void* num) 
{ 
  
    while (1) { 
  
        int* i = num; 
  
        sleep(1); 
  
        pickup_forks(*i); 
  
        sleep(0); 
  
        return_forks(*i); 
    } 
} 
  
int main() 
{ 
  
    int i; 
    pthread_t thread_num[NUMPHILO]; 
  
    sem_init(&mutex, 0, 1); 
  
    for (i = 0; i < NUMPHILO; i++) 
  
        sem_init(&S[i], 0, 0); 
  
    for (i = 0; i < NUMPHILO; i++) { 
  
        pthread_create(&thread_num[i], NULL, 
                       philospher, &phil[i]); 
  
        printf("Philosopher %d is currently thinking\n", i + 1); 
    } 
  
    for (i = 0; i < NUMPHILO; i++) 
        pthread_join(thread_num[i], NULL); 
} 