#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

double sum = 0;
struct targs
{
    long long start;
    long long end;
};
//Synchronizing Threads With Mutexes
pthread_mutex_t mu;

void *threadMulti(void *p)
{
    pthread_mutex_lock(&mu);
    struct targs *value = (struct targs *)p;
    long long start = value->start;
    long long end = value->end;
    long long num;

    for (num = start; num <= end; num++) {
        sum = sum + pow(-1, num) / (2 * num + 1);       //calculation PI 
    }
    pthread_mutex_unlock(&mu);
    pthread_exit(0);
}

void main(int argc)
{

    long long iteration;
    int threadn;

    printf("Enter the numbers of Iteration: ");
    scanf("%lld", &iteration);

    printf("Enter the numbers of thread: ");
    scanf("%d", &threadn);

    //Multithread slicing
    int sliceL[threadn];
    int i,j,c;
    int rem = iteration % threadn;

    for (i = 0; i < threadn; i++) {
        sliceL[i] = iteration / threadn;
    }

    for (j = 0; j < rem; j++) {
        sliceL[j] = sliceL[j] + 1;
    }

    int startL[threadn]; 
    int endL[threadn];

    for (c = 0; c < threadn; c++) {
        if (c == 0) {
            startL[c] = 0;
        }
        else {
            startL[c] = endL[c - 1] + 1;
        }

        endL[c] = startL[c] + sliceL[c] - 1;
    }
    struct targs p[threadn];
    pthread_t threadIds[threadn];  //using threadids variable to identify the thread after it has been created
    int l, n;
    for (l = 0; l < threadn; l++) {
        p[l].start = startL[l];
        p[l].end = endL[l];
        pthread_create(&threadIds[l], NULL, threadMulti, &p[l]);  //starting thread 
    }
    
    pthread_mutex_init(&mu, NULL);  //initializing mutex
 
    for (n = 0; n < threadn; n++) {
        pthread_join(threadIds[n], NULL); //waiting for a thread to finish,
    }
    
    pthread_mutex_destroy(&mu);    //Destroying mutex

    printf("The value of Pi is: %lf\n", sum * 4);  //printing the value of PI
}
