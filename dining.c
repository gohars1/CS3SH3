#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h> 
#include <unistd.h>
  
#define NUMPHILO 5 
#define HUNGRYSTATE 1 
#define THINKSTATE 2 
#define EATINGSTATE 0 
#define RIGHTFORK (philo + 1) % NUMPHILO
#define LEFTFORK (philo + 4) % NUMPHILO

  
int state[NUMPHILO]; 
int phil[NUMPHILO] = { 0, 1, 2, 3, 4 }; 
sem_t mutex; 
sem_t S[NUMPHILO]; 
  
void neighbours(int philo) 
{ 
    if (state[philo] == HUNGRYSTATE && state[LEFTFORK] != EATINGSTATE && state[RIGHTFORK] != EATINGSTATE) { 

        state[philo] = EATINGSTATE; 
  
        sleep(2); 
  
        printf("Philosopher %d takes fork %d and %d\n", 
                      philo + 1, LEFTFORK + 1, philo + 1); 
  
        printf("Philosopher %d is currently eating\n", philo + 1); 
  
        sem_post(&S[philo]); 
    } 
} 
  
void pickup_forks(int philo) 
{ 
    sem_wait(&mutex); 
  
    state[philo] = HUNGRYSTATE; 
  
    printf("Philosopher %d is currently hungry\n", philo + 1); 
  
    neighbours(philo); 
  
    sem_post(&mutex); 
  
    sem_wait(&S[philo]); 
  
    sleep(1); 
} 
  
void return_forks(int philo) 
{ 
  
    sem_wait(&mutex); 
  
    state[philo] = THINKSTATE; 
  
    printf("Philosopher %d putting fork %d and %d down\n", 
           philo + 1, LEFTFORK + 1, philo + 1); 
    printf("Philosopher %d is currently thinking\n", philo + 1); 
  
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