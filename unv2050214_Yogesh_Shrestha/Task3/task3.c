#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// initializing variables
pthread_mutex_t mu; //Synchronizing Threads With Mutexes
int *ptr;
int c;
int num;
FILE *Afile;
struct targs
{
    int start;
    int end;
};
//Prime or not check function
int prime(int a){
	int i;	
	int flag = 0;
	// if(a==0||a==1){
	// 	return 0;
	// }
	for (i = 1; i <= a; i++) {
		if (a % i == 0){
			flag++;
    	}	
	}
	if(flag == 2)
    {
        return 1;
    }
    else{
        return 0;
    }
}

void *threadMulti(void *p)
{
    pthread_mutex_lock(&mu);
    struct targs *value = (struct targs *)p;
    int start = value->start;
    int end = value->end;
    int sum;

    for (int num = start; num <= end; num++)
    {
            int check = prime(ptr[num]);
            if(check == 1){		
                fprintf(Afile,"%d\n",ptr[num]);
                sum++;
            }
    }
    pthread_mutex_unlock(&mu);  //mutex unlock
    pthread_exit(0);
    
}

void main(int argc)
{
    char ch;
    int count = 0;
    FILE *p1, *p2, *p3, *p4;  //file merging
	p1=fopen("PrimeData1.txt","r");
	p2=fopen("PrimeData2.txt","r");
	p3=fopen("PrimeData3.txt","r");
	p4=fopen("PrimeData5.txt","w");
    Afile = fopen("PrimeOutput.txt","w");

	if(p1==NULL||p2==NULL||p3==NULL||p4==NULL){
		printf("\nError : This file cannot be open");
		exit(1);
	} 
	while(1){			//copying dataset 1 into data set 5
		ch = fgetc(p1);
		if(ch==EOF)
        {
            break;
        }	
        if(ch=='\n')
         count++;
		fputc(ch,p4);	
	}
	
	while(1){			//copying dataset 2 into data set 5
		ch = fgetc(p2);
		if(ch==EOF)
        {
            break;
        }	
        if(ch=='\n')
         count++;
		fputc(ch,p4);	
	}

	while(1){			//copying dataset 3 into data set 5
		ch = fgetc(p3);
		if(ch==EOF)
        {
            break;
        }	
        if(ch=='\n')
         count++;
		fputc(ch,p4);	
	}
    printf("%d\n", count);
	

    int index = 0;

    ptr = (int*) malloc(count * sizeof(int));  //Dynamic memory allocation
    int totalcountsize;
    p4=fopen("PrimeData5.txt","r");
    while((fscanf(p4, "%d\n", &ptr[index]))!=EOF)
    {
        index = index + 1;
    }

    int threadn;
    printf("Enter the number of thread: ");
    scanf("%d", &threadn);
    
    int sliceL[threadn];
    int endL[threadn];

    int rem = count % threadn;

    for (int i = 0; i < threadn; i++)
    {
        sliceL[i] = count / threadn;
    }

    for (int j = 0; j < rem; j++)
    {
        sliceL[j] = sliceL[j] + 1;
    }
    

    for (int c = 0; c < threadn; c++)
    {
        if (c == 0)
        {
            startL[c] = 0;
        }

        else
        {
            startL[c] = endL[c - 1] + 1;
        }

        endL[c] = startL[c] + sliceL[c] - 1;
    }

    struct targs p[threadn];
    pthread_t threadIds[threadn];
    for (int l = 0; l < threadn; l++)
    {
        p[l].start = startL[l];
        p[l].end = endL[l];
        pthread_create(&threadIds[l], NULL, threadMulti, &p[l]);
    }
    

    pthread_mutex_init(&mu, NULL);

    for (int n = 0; n < threadn; n++)
    {
        pthread_join(threadIds[n], NULL);
    }

    pthread_mutex_destroy(&mu);
    fclose(p1);
    fclose(p2);
    fclose(p3);
	fclose(p4);
    fclose(Afile);
} 
