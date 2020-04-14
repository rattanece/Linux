#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details. 
#include <pthread.h> 
#include <errno.h>
  
// A normal C function that is executed as a thread  
// // when its name is specified in pthread_create() 
int global_x=0;
pthread_mutex_t lock;

void *myThreadFun1(void *vargp) 
{ 
	pthread_mutex_lock(&lock);
//	sleep(1); 
//	while(1)
	{
    		printf("Thread 1 \n"); 
		//sleep(1);
	}
	global_x += 30;
	pthread_mutex_unlock(&lock);
	return NULL; 
} 

void *myThreadWithinThreadFun()//void * arg)
{
	global_x += 5;
//	while(global_x--)
	{
		printf("thread within thread2\n");
		sleep(1);
	}
}

void *myThreadFun2(void *vargp) 
{ 
//	sleep(1); 
	pthread_mutex_init(&lock,NULL);
    	pthread_t thread_id;
	pthread_create(&thread_id,NULL,myThreadWithinThreadFun,NULL);
	printf("thread id %ld\n",thread_id);
	printf("random error %d\n",EAGAIN);
//	pthread_exit(NULL);
	pthread_join(thread_id,NULL);
//	while(1)
	{
	    printf("Thread 2\n"); 
//	    sleep(1);
	}
    	global_x += 20;
     	return NULL; 
} 
                
 int main() 
{ 
	pthread_t thread_id1 , thread_id2; 
	int err=0;
        printf("Before Thread\n"); 
        err = pthread_create(&thread_id1, NULL, myThreadFun1, NULL); 
	if(err)
		printf("pthread_create fail\n");
        err = pthread_create(&thread_id2, NULL, myThreadFun2, NULL); 
	if(err)
		printf("pthread_create fail\n");
//	sleep(5);

	err = pthread_join(thread_id1, NULL); 
	if(err)
		printf("pthread_join fail\n");
//	err = pthread_join(thread_id2, NULL); 
	if(err)
		printf("pthread_join fail\n");
//	printf("thread 1 1 %d\n",global_x); 
        err = pthread_create(&thread_id1, NULL, myThreadFun1, NULL); 
//	err = pthread_join(thread_id1, NULL); 
//      printf("thread 1 2 %d\n",global_x); 
        err = pthread_create(&thread_id1, NULL, myThreadFun1, NULL); 
	err = pthread_join(thread_id1, NULL); 
        printf("thread 1 4 %d\n",global_x); 

        printf("____________________________________________________________________________________After Thread , global_x = %d\n",global_x); 
        printf("After Thread , global_x = %d\n",global_x); 
        pthread_exit(NULL); 
	//exit(0);
}
