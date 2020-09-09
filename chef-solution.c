// Reference: https://www.geeksforgeeks.org/use-posix-semaphores-c/
// C program to demonstrate a simple multi-threaded process using two threads.
#include <stdio.h> 
#include <pthread.h> 
#include <unistd.h> 
#include <semaphore.h> 

sem_t s0;

//thread t0 represents Chef 0
void* thread_t0(void* arg)		
{ 
	int i = 10;
	while(i > 0){
		sem_wait(&s0);
		printf("\nChef 0 is using Pan B to prepare fry 1 ham.\n");	//in Critical Section
		sleep(2);	//simulate frying 1 ham in 2 seconds
		sem_post(&s0);
		i--;
		printf("\nChef 0 finished using Pan B.\n");	//exit Critical Section
		sleep(1);	//transition taking 1 second
	}
} 

//thread t1 represents Chef 1
void* thread_t1(void* arg)		
{ 
	int j = 10;
	while(j > 0){
		sem_wait(&s0);
		printf("\nChef 1 is using Pan B to prepare fry 1 egg.\n");	//in Critical Section
		sleep(2);	//simulate frying 1 egg in 2 seconds
		sem_post(&s0);
		j--;
		printf("\nChef 1 finished using Pan B.\n");	//exit Critical Section
		sleep(1);	//transition taking 1 second
	}
} 

int main() 
{ 
	//these values are used to identify thread number
	int thread0_id=0, thread1_id=1; 

	sem_init(&s0, 0, 1);

	//intialize two variables type pthread_t called t0 and t1
	pthread_t t0,t1; 
	
	//create two threads, passing thread number as the forth argument
	pthread_create(&t0,NULL,thread_t0,&thread0_id); 
	pthread_create(&t1,NULL,thread_t1,&thread1_id); 

	//join two threads after they finished running
	pthread_join(t0,NULL); 
	pthread_join(t1,NULL); 
	
	sem_destroy(&s0);

	return 0; 
} 