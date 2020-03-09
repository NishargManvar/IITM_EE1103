/************************************************
Purpose : Hamming Distance Assignment
			This code takes a random bit stream and induce error and delete some bits to simulate real life conditions.
			Then it gives the stream a random offset and by revealing a limited amount of bits back it calculates the offset and checks its correctness.
			Also calculated are complexity of quantum erasure channel (QBER)
Date    : 12th October 2019
Authors : Pranav Phatak(EE19B105),Nisharg Manvar(EE19B094)
Input   : Number of bits, fraction of bits receiver, fraction of bits having error (Command line input)
Output  : Refer last print statement

*************************************************/
//Start of code
//Including Header Files
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

//Start of main function
int main(int argc,char *argv[])
{
	float random;	//variable for float random number generation throughout the code
	int randomint;	//variable for integer random number generation throughout the code
	int i,j;		//loop control variables
	int count=0,rev=0;
	int N=atoi(argv[1]);		//Number of bits transmitted by transmitter
	float Q=atof(argv[3]);		//Fraction of bits having error
	int P=N*atof(argv[2]);		//The number of bits reaching the receiver

	srand((unsigned)time(NULL));	//Seeding the random number generator

  	int n=ceil(N/P);     //Every n th value to be taken from offseted array
	int s=ceil(1/Q);	//Every s th value have an error

	int M=rand()%N;		//Random offset generated

	int *X;		//Most raw and original array
	X = (int*) malloc(N * sizeof(int));
	int *Xnew;	//Offseted array
	Xnew = (int*) malloc(N * sizeof(int));

	int Y[2][N];	//2D-Array to store bits and its position received by receiver
	
	int *Z;		//will be used to compare with revealed bits by receiver
	Z = (int*) malloc(N * sizeof(int));



	for(i=0;i<N;i++)	//Initalizing X array randomnly
	{
		random=(float)rand()/RAND_MAX;

		if(random<=0.5) //So that we get 0 or 1 randomly with equal probability
			X[i]=0;
		else
			X[i]=1;
	}

			
	for(i = 0; i < N; i++)	//Recreating X such that Mth entry becomes 1st entry thus creating a offset of M by using circular buffer	
    {
		Xnew[i] = X[(i+M)%N];
		
    }


	for (i = 0; i < N; i++)	//Storing the position and value of bits received by receiver 
    {
		randomint=ceil(rand());
		if(randomint%n==1)	//Thus taking randomly every nth value
        {
        	Y[0][count] = i;
        	Y[1][count] = Xnew[i];
        	count++;		//This will ensure we know the exact lenght of the supposed 2*P array
		}

	}


	for (int i = 0; i < count; i++) // flipping some random bits with a certain probablity
	{
		int random=rand();
		if(random%s==1)
		{
			Y[1][i] = ~Y[1][i];
		}
	}
		
		
	int result;	//Final Answer i.e. calculated offset
	int Hammingrevealed,Hammingsecret;	//variables to store hamming distance of revealed, secret bits respectively
	int H[N];	//Array to store hamming distance of revealed bits for all variavle offsets of X
	int H2[N];	//Array to store hamming distance of secret bits for all variable offsets of X


	for(i=0;i<N;i++)	//Varying the offset of array X in the form of i from 0 to N and storing resulting array in Z
	{
		
		for(j=0;j<N;j++)
		{
			Z[j]=X[(j+i)%N];
		}
			 		
	
		Hammingsecret=0;
		Hammingrevealed=0;

		
		for(j=0;j<count;j++)
			{
				randomint=ceil(rand());
		
				if(randomint%5==1)	//to reveal 1/5th of total bits randomly
				{
				if(Y[1][j]^Z[(Y[0][j])]==1)
				{
				Hammingrevealed++;	//counting hamming distance of revealed bits
 				}
				rev++;			//counting the number of bits revealed
				}
		
				else
				{
				if(Y[1][j]^Z[(Y[0][j])]==1)
				Hammingsecret++;	//counting hamming distance of secret bits
				}
			H2[i]=Hammingsecret;
			H[i]=Hammingrevealed;
			}
	}


	rev=ceil(rev/N);	//since rev has been counted in the for loop on i N times , we will need to divide it by N to get the average value of revealed bits

	int minhamming=count;	//Variable to find minimum hamming distance from H[]

	for(int i=0;i<N;i++)	
	{
		
		if(H[i]<minhamming)	//Finding minimum Hamming distance from revealed
		{
			minhamming=H[i];
			result=i;
		}
	}

	float QBER = 100*minhamming/rev;	//QBER for revealed bits
	float QBER2 = 100*H2[result]/(count-rev);	//QBER for secret bits

	//Printing all the results
	printf("Calculated offset : %d\nGenerated Offset : %d\nLeast Hamming Distance : %d\nBits received : %d\nBits revealed : %d\nBER of revealed bits: %f\nHamming distance of unrevealed bits for calculated offset: %d\nBER of unrevealed bits: %f\n",result,M,minhamming,count,rev,QBER,H2[result],QBER2);
	return 0;
}//End of Main
//End of code
