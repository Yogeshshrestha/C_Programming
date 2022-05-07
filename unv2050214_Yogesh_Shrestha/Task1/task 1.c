#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<math.h>

int main() { 		//merging 4 file into 1
	FILE *f1, *f2, *f3, *f4, *f5;
	char ch;
	f1=fopen("datasetLR1.txt","r");
	f2=fopen("datasetLR2.txt","r");
	f3=fopen("datasetLR3.txt","r");
	f4=fopen("datasetLR4.txt","r");
	f5=fopen("datasetLR5.txt","w");
	if(f1==NULL||f2==NULL||f3==NULL||f4==NULL||f5==NULL){
		printf("\nError : This file cannot be open");
		exit(1);
	} 
	while(1){			//copying dataset 1 into data set 5
		ch = fgetc(f1);
		if(ch==EOF)
			break;
		fputc(ch,f5);	
	}
	fclose(f1);
	while(1){			//copying dataset 2 into data set 5
		ch = fgetc(f2);
		if(ch==EOF)
			break;
		fputc(ch,f5);	
	}
	fclose(f2);
	while(1){			//copying dataset 3 into data set 5
		ch = fgetc(f3);
		if(ch==EOF)
			break;
		fputc(ch,f5);	
	}
	fclose(f3);
	while(1){			//copying dataset 4 into data set 5
		ch = fgetc(f4);
		if(ch==EOF)
			break;
		fputc(ch,f5);	
	}
	fclose(f4);
	fclose(f5);
	
	int  X,y;
	float sum_of_X = 0, sum_of_y = 0; 
	float sum_of_X2, sum_of_y2, sum_of_Xy;
	int count = 0;  
	int X_x, Y_y;
    printf( "Opening the file data in read mode\n" ) ;      //reading data from file
    f5 = fopen( "datasetLR5.txt","r" ) ;
    if ( f5 == NULL )
    	{
            printf( "Could not open file " ) ;
            return 1;
        }
        printf( "Reading the file " ) ;
        while(fscanf(f5,"%d, %d",&X,&y) != EOF)
        {
    		printf( "%d, %d\n" , X,y ) ;
    		sum_of_X = sum_of_X + X;         //finding summation of X
    		sum_of_y = sum_of_y + y;		 //finding summation of y
    		sum_of_X2 = sum_of_X2 + (X * X); //finding summation of X
    		sum_of_y2 = sum_of_y2 + (y * y); //finding summation of X
    		sum_of_Xy = sum_of_Xy + (X * y); //finding summation of X
    		count++;
		}
		 
		printf("The value of N is: %d\n", count);
		printf("The value of summation X: %f\nThe value of summation Y:%f\n", sum_of_X, sum_of_y);
		printf("The value of summation X2: %f\nThe value of summation Y2:%d\nThe value of summation XY: %f\n", sum_of_X2, sum_of_y2, sum_of_Xy);

		float A,B;		//Linear Regression (Fitting y = a+bx)
		A = ((sum_of_y * sum_of_X2) - (sum_of_X * sum_of_Xy)) / ((count * sum_of_X2) - (sum_of_X * sum_of_X));
		B = ((count * sum_of_Xy) - (sum_of_X * sum_of_y)) / ((count * sum_of_X2) - (sum_of_X * sum_of_X)); 
    	printf("The value of A is: %f\nThe value of B is: %f", A,B);
    	printf("\nEnter the value of x: ");
    	scanf("%f", &X_x); 
    
    	Y_y = (B * X_x) + A;
 		printf("The Value of Y is: %d", Y_y);

    fclose(f5) ;
    return (0);
}
