// ASSIGNMENT 1

// NAME: JABER-UL HUDA
// STUDENT ID: 101137524



#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <sys/time.h>

#include <sys/types.h> 
#include <sys/wait.h>

#include <signal.h>

#include <sys/shm.h>
#include "shm_com.h"

#include <stdbool.h>

#define MICRO_SEC_IN_SEC 1000000


void ex_done(int sig) 
{
	exit(0); 
}

int main()
{
	pid_t pid;
	char *message;
	int n;
	int exit_code; 
	// wait() variables
	
	int M[] = {20, 20, 50, 10, 6, 70, 40, 3, 2}; // the mandatory test data a,b,c,d,e,f,g,h,i
									     //	0,1,2,3,4,5,6,7,8
	//int child_idn[] = {10, 20, 30}; // the mandatory test data
	int child_id;
	
	int i;
	
	int running = 1;
	void *shared_memory = (void *)0;
	struct shared_use_st *shared_stuff;
	int shmid;
	
	struct timeval start, end;
	
	// Creates the shaired memory and points to the shaired memeory
	// shaired memory
	shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
	
	if (shmid == -1) {
		fprintf(stderr, "shmget failed\n");
		exit(EXIT_FAILURE);
	}

	shared_memory = shmat(shmid, (void *)0, 0);
	if (shared_memory == (void *)-1) {
		fprintf(stderr, "shmat failed\n");
		exit(EXIT_FAILURE);
	}
	// shaired memory
	
	printf("Memory attached at %X\n", (int)shared_memory);
	shared_stuff = (struct shared_use_st *)shared_memory; 
	shared_stuff->flag_i = 0;
	(shared_stuff->D)[0] = 0;
	(shared_stuff->D)[1] = 0;
	(shared_stuff->D)[2] = 0;
	
	//printf("D value in mm: %d %d %d\n", (shared_stuff->D)[0], (shared_stuff->D)[1], (shared_stuff->D)[2]);

	
	// 3 child creation code 
	// start
	i = 0; // child 1 i=1, child 1 i=2, child 1 i=3
	gettimeofday(&start, NULL); // second parameter is for time zone; usually is NULL
	while(i<3) {
		// make sure only parent can call fork().
		//if(pid != 0) {
		pid = fork();
		//} 
		if(pid == 0) {
			break;
		}	
		i++;
	}	
	
	switch(pid)
	{
	case -1:
		perror("fork failed");
		exit(1);
		break;
	case 0:
		
		
		//printf("Child %d has i: %d  \n", i+1,i);
		printf("Child Process %d: working with element of D-> %d  \n", i+1,i);
		
		if (i == 0) {
			int determinant1;
			determinant1 = (M[4]*M[8]) - (M[5]*M[7]);
			(shared_stuff->D)[0] = determinant1;
			printf("Determinant 1 is %d calculated by child %d \n", determinant1, i+1);
			
			exit_code = i;
			
			
			// shared memory detached
			if (shmdt(shared_memory) == -1) { 
				fprintf(stderr, "shmdt failed\n"); exit(EXIT_FAILURE);
			}
			
			
		} 
		
		if (i == 1) {
			int determinant2;
			determinant2 = (M[3]*M[8]) - (M[5]*M[6]);
			(shared_stuff->D)[1] = determinant2;
			printf("Determinant 2 is %d calculated by child %d \n", determinant2, i+1);
			
			exit_code = i;
			
			
			// shared memory detached
			if (shmdt(shared_memory) == -1) { 
				fprintf(stderr, "shmdt failed\n"); exit(EXIT_FAILURE);
			}
			
			
		}
		
		if (i == 2) {
			int determinant3;
			determinant3 = (M[3]*M[7]) - (M[4]*M[6]);
			(shared_stuff->D)[2] = determinant3;
			printf("Determinant 3 is %d calculated by child %d \n", determinant3, i+1);
			
			exit_code = i;
			
			
			// shared memory detached
			if (shmdt(shared_memory) == -1) { 
				fprintf(stderr, "shmdt failed\n"); exit(EXIT_FAILURE);
			}
			
			
		}
		
		exit(exit_code);
	default:
		
		exit_code = 0;
		break;
	}
	
	
	if (pid != 0) {
		int stat_val;
		pid_t child_pid;
		int determinant_M;
		
		printf("Parent entres wait: %d \n", pid);	
		
		child_pid = wait(&stat_val);
		child_pid = wait(&stat_val);
		child_pid = wait(&stat_val);
		gettimeofday(&end, NULL);
			
		printf("Parent exit wait: %d \n", child_pid); 
		
		// Calc Determinant M
		determinant_M = ((shared_stuff->D)[0] * M[0]) - ((shared_stuff->D)[1] * M[1]) + ((shared_stuff->D)[2] * M[2]);
		printf("Determinant M calculated by Parent is: %d \n", determinant_M);
		printf("Determinant M1 is: %d \n", (shared_stuff->D)[0]);
		printf("Determinant M2 is: %d \n", (shared_stuff->D)[1]);
		printf("Determinant M3 is: %d \n", (shared_stuff->D)[2]);
		
		printf("Start Time: %lf sec from Epoch (1970‐01‐01 00:00:00 +0000 (UTC))\n", start.tv_sec + (double)start.tv_usec/MICRO_SEC_IN_SEC);
		printf("End Time: %lf sec from Epoch (1970‐01‐01 00:00:00 +0000 (UTC))\n", end.tv_sec + (double)end.tv_usec/MICRO_SEC_IN_SEC);
		printf("\nElapsed Time: %ld micro sec\n", ((end.tv_sec * MICRO_SEC_IN_SEC + end.tv_usec) - (start.tv_sec * MICRO_SEC_IN_SEC + start.tv_usec)));
		
		// shared memory detached
		if (shmdt(shared_memory) == -1) { 
			fprintf(stderr, "shmdt failed\n"); exit(EXIT_FAILURE);
		}
		
		// shared memory deleted
		if (shmctl(shmid, IPC_RMID, 0) == -1) {
		 	fprintf(stderr, "shmctl(IPC_RMID) failed\n");
			exit(EXIT_FAILURE); 
		}
		
		
		

	}
	
	exit(exit_code);		
	
}
	
