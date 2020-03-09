/***********************************
Purpose : Distributions Assignment i.e. implementing normal,lorentizan,poisson and rayleigh distributions
Authors : Nisharg_Manvar(EE19B094) , Neham_Jain(EE19B084)
Date    : 28/08/2019
Input   : Number of random nnumbers and type of distribution (Command Line)
Output  : Text file with random numbers corresponding to input by user
*************************************/

//Header files and initial declarations
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#define PI 3.1415
#define E 2.71828 
#include<string.h>
//Functions in Programs
void nrandn (int n);
void lrandn (int n);
void prandn (int n);
void rrandn (int n);
double mean(double* values, int n);
double stddev(double* values, int n);

void main(int argc, char *argv[])
{
	//Calling appropriate function as per input by user
	srand(time(NULL));
	if(strcmp(argv[2],"normal")==0)
		nrandn(atoi(argv[1]));
	else if(strcmp(argv[2],"lorentizan")==0)
		lrandn(atoi(argv[1]));
	else if(strcmp(argv[2],"poisson")==0)
		prandn(atoi(argv[1]));
	else if(strcmp(argv[2],"rayleigh")==0)
		rrandn(atoi(argv[1]));
	else{
		printf("Run the program again and give N and distribution name as command line input.\n");
		printf("Possible options are-\nnormal\nlorentizan\npoission and\nrayleigh");
	}
}
//Normal Distribution values generator function
void nrandn (int n)
{
	//Variables Declartion
	double U1, U2, W, mult;
	static double X1, X2;
	double mu=0,sigma=0.25;
	int i;
	int m = n + (n%2);
	double f[n];
	double min=10000,max=0,binwidth;
	FILE *fptr;
	fptr=fopen("normald.txt","w");
	// Generating values
	for(i=0;i<m;i=i+2)
	{
		do
		{
			U1 = -1 + ((double) rand () / RAND_MAX) * 2;
			U2 = -1 + ((double) rand () / RAND_MAX) * 2;
			W = pow (U1, 2) + pow (U2, 2);
		}			
		while (W >= 1 || W == 0);
		mult = sqrt ((-2 * log (W)) / W);
		X1 = U1 * mult;
		X2 = U2 * mult;
		f[i]= (mu + sigma * (double) X1);
		//Finding Max and Min
		if(f[i]>max)
			max = f[i];
		if(f[i]<min)
			min = f[i];
		f[i+1]= (mu + sigma * (double) X2);
		if(f[i]>max)
			max = f[i+1];
		if(f[i]<min)
			min = f[i+1];
		fprintf(fptr,"%lf\n",f[i]);
		fprintf(fptr,"%lf\n",f[i+1]); //Saving values in file called "normald.txt"
	}
	binwidth = (max-min)/(1+(log(n)/log(2))); //Calculating BinWidth
	printf("Recommended binwidth for this normal dist. is %.2lf\n \n Mean is  %lf and standard deviation is %lf",binwidth,mean(f,n),stddev(f,n));
	fclose(fptr);
} //End of Function

//Lorentz Distribution values generator function
void lrandn (int n)
{
	//Variables Declartion
	double f[n];
	double min=10000,max=0,binwidth;
	FILE *fptr;
	fptr=fopen("lorentzd.txt","w");
	int i;
	// Generating values
	for ( i = 0; i < n; i ++ )
    {
		double x,y,rsq;
		do{
			x = (PI * rand() / (double)RAND_MAX) - 1.0;
			rsq=tan(x);
		}while(rsq>10 || rsq<-10);	
		f[i] = rsq;
		//Finding Max and Min
		if(f[i]>max)
			max = f[i];
		if(f[i]<min)
			min = f[i];
		fprintf(fptr,"%lf\n",f[i]);	//Saving values in file called "lorentzd.txt"
	}
	binwidth = (max-min)/(1+(log(n)/log(2)));	//Calculating BinWidth
	printf("Recomended binwidth for this lorentizan is %.2lf\n\n Mean is  %lf and standard deviation is %lf",binwidth,mean(f,n),stddev(f,n));
	fclose(fptr);
}	//End of Function

//Poisson Distribution values generator function
void prandn (int n)
{
	//Variables Declartion
	double f[n];
	double min=10000,max=0,binwidth;
	FILE *fptr;
	fptr=fopen("poissond.txt","w");
	int i;
	// Generating values
	for ( i = 0; i < n; i ++ )
	{
		int k=0;
		do{  
		const int max_k = 1000;           
		double p = (2 * rand() / (double)RAND_MAX) - 1.0;
		if(p<0)
			p=-p;
		double P = exp(-50); //To change the mean and Std. Dev. of distribution from 50 change "-50" to desired to value         
		double sum=P;                              
		for (k=1; k<max_k; ++k) {        
			P*=50/(double)k;	//Change "50" here as well (Refer above comment)
			sum+=P;                   
			if (sum>=p) 
				break;
			}
		}while(k>100);	
		f[i] = k;
		//Finding Max and Min
		if(f[i]>max)
			max = f[i];
		if(f[i]<min)
			min = f[i];
		fprintf(fptr,"%lf\n",f[i]);	//Saving values in file called "poissond.txt"
	}
	binwidth = (max-min)/(1+(log(n)/log(2)));	//Calculating BinWidth
	printf("Recomended binwidth for this poission dist is %.2lf\n Mean is  %lf and standard deviation is %lf\n",binwidth,mean(f,n),stddev(f,n));
	fclose(fptr);
}	//End of Function

//Rayleigh Distribution values generator function
void rrandn (int n)
{
	//Variables Declartion
	double f[n];
	double min=10000,max=0,binwidth;
	FILE *fptr;
	fptr=fopen("rayleighd.txt","w");
	int i;
	// Generating values
	for ( i = 0; i < n; i ++ )
	{
		double x,y,rsq;
		do{
			x= (2.0 * rand() / (double)RAND_MAX) - 1.0;
		}while( x > 1 || x <= 0 );
		f[i]= sqrt( -2.0 * log(x));
		//Finding Max and Min
		if(f[i]>max)
			max = f[i];
		if(f[i]<min)
			min = f[i];
		fprintf(fptr,"%lf\n",f[i]);	//Saving values in file called "rayleighd.txt"
	}
	binwidth = (max-min)/(1+(log(n)/log(2)));	//Calculating BinWidth
	printf("Recomended binwidth for this rayleigh dist is %.2lf\n\n Mean is  %lf and standard deviation is %lf \n",binwidth,mean(f,n),stddev(f,n));
	fclose(fptr);
}	//End of Function

//Mean calculator function
double mean(double* values, int n)
{
    int i;
    double s = 0;
 
    for ( i = 0; i < n; i++ )
        s += values[i];
    return s / n;
}
 
// Standard Deviation calculator function
double stddev(double* values, int n)
{
    int i;
    double average = mean(values,n);
    double s = 0;
 
    for ( i = 0; i < n; i++ )
        s += (values[i] - average) * (values[i] - average);
    return sqrt(s / (n - 1));
}
 

