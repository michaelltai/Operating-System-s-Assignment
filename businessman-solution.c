// C program to demonstrate a simple multi-threaded process using two threads.
#include <stdio.h> 
#include <pthread.h> 
#include <unistd.h>
#include <semaphore.h> 

sem_t A;   //semaphore variable called A is declared
sem_t B;   //semaphore variable called B is declared

int buf_A, buf_B;	//declare global variables buf_A and buf_B

//thread A does the following
void* thread_A(void* arg)		
{ 
	int var_A;

	while(1){
		var_A = 1234;	
		buf_A = var_A;	//Jot down own contact number to buf_A so that thread_B can copy
		sem_post(&B);	//Here is my card
		sem_wait(&A);	//Waiting for yours
		var_A = buf_B;	//Copy thread_B's contact number to var_A
		printf("\nthread_A: var_A = %d", var_A);  //print var_A on screen

		sleep(1);
	}
} 

//thread B does the following
void* thread_B(void* arg)		
{ 
	int var_B;

	while(1){
		var_B = 4321;
		buf_B = var_B;	//Jot down own contact number to buf_B so that thread_A can copy
		sem_post(&A);	//Here is my card
		sem_wait(&B);	//Waiting for yours
		var_B = buf_A;	//Copy thread_A's contact number to var_B
		printf("\nthread_B: var_B = %d", var_B);  //print var_B on screen
		sleep(1);
	}
} 

int main() 
{ 
	//these values are used to identify thread number
	int threadA_id=0, threadB_id=1; 

	//initialize semaphore A and B values as 0 (3rd argument)
	sem_init(&A, 0, 0);
	sem_init(&B, 0, 0);	

	//intialize two variables type pthread_t called t0 and t1
	pthread_t tA,tB; 
	
	//create two threads, passing thread number as the forth argument
	pthread_create(&tA,NULL,thread_A,&threadA_id); 
	pthread_create(&tB,NULL,thread_B,&threadB_id); 

	//join two threads after they finished running
	pthread_join(tA,NULL); 
	pthread_join(tB,NULL); 
	
	//print the value of x and y after threads finished running
	printf("The final value of buf_A is %d\n", buf_A);
	printf("The final value of buf_B is %d\n", buf_B);

	//destroy the semaphore after finished using it
	sem_destroy(&A);
	sem_destroy(&B);

	return 0; 
} 
