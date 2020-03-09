/*
***********************************************************************************************************************************************
EE1103-Numerical Methods
Assignment 4b) Model creation Develop an equation to predict area as a function of height and weight.
This program will:
	-use lu decomposition and multiple regression to estimate area for a given height and weight.
Done by: Pranav Phatak(EE19B105),Nisharg Manvar(EE19B094)	
Data of 9 areas and corresponding heights and weights is taken as input(within the program) and a general equation is predicted.
General formula used:A=c(W^a)*(H^b) where a,b and c are constants to be determined.
Input: Height and Weight.
Output: Area of body from the formula generated. 
Date: 19th September 2019
Run command: cc ModelCreation.c -lm 
	     ./a.out
	     'H'and'W'values.
***********************************************************************************************************************************************
*/




#include<stdio.h>
#include<math.h>
void main()
{
	int N=3; int i,j,k;
	float A[10][10],B[100],l[10][10],u[10][10],V[10][10],Y[10],X[10];
	float H[9]= {1.82,1.80,1.79,1.87,1.89,1.94,1.95,1.93,2.00};		/*Known data*/
	float W[9]={74,88,94,78,84,98,76,86,96};
	float a[9]={1.92,2.11, 2.15, 2.02, 2.09, 2.31 ,2.02, 2.16,2.31};
	float we=0,he=0,wes=0,hes=0,wehe=0,ahe=0,bh=0,kl=0;
	for(int i=0;i<9;i++)
	 {//creating the matrix that contains all values necessary to do multiple regression
		we+=log(W[i]);
		he+=log(H[i]);
		wes=wes+(log(W[i])*log(W[i]));
		hes=hes+(log(H[i])*log(H[i]));
		wehe=wehe+(log(W[i])*log(H[i]));
		ahe=ahe+log(a[i]);
		bh=bh+log(a[i])*log(W[i]);
		kl=kl+log(a[i])*log(H[i]);
	 }
 	A[0][0]=9;A[0][1]=we;A[0][2]=he;A[1][0]=we;A[1][1]=wes;A[1][2]=wehe;A[2][0]=he;A[2][1]=wehe;A[2][2]=hes;B[0]=ahe;B[1]=bh;B[2]=kl;
/*Code for decomposition into lower and upper matrices*/	
	for(int i=0;i<N;i++)
		for(int j=0;j<N	;j++)
		{
		u[i][j]=A[i][j];
		if(i<j)
		    l[i][j]=0;
		else if(i==j)
		    l[i][j]=1;

		}
	    for(int m=0;m<N;m++)
		for(int i=m+1;i<N;i++)
	    	{
		double factor=u[i][m]/u[m][m];
		for(int j=0;j<N;j++)
		   {
		       u[i][j]-=(factor*u[m][j]);
		        l[i][m]=factor;
		   }
	    }
/*Generation of intermediate matix Y while solving the matrix equation*/
	  for(i=0; i<N; i++)
	    {
		Y[i]=B[i];
		for(j=0; j<i; j++)
		{
		    Y[i]-=l[i][j]*Y[j];
		}
	    }
	    printf("\n\n[Y]: \n");
	  for(i=0; i<N; i++)
	    {
		printf("%9.3f",Y[i]);
	    }
/*Generation of solution matrix X*/
	  for(i=N-1; i>=0; i--)
	    {
		X[i]= Y[i];
		for(j=i+1; j<N; j++)
		{
		    X[i]-=u[i][j]*X[j];
		}
		X[i]/=u[i][i];
	    }
    	printf("\n\n[X]: \n");
    for(i=0; i<N; i++)
    {
        printf("%9.3f",X[i]);
    }    
	float h,w,area;
    printf("\nTherefore, x1=%lf,x2=%lf and x3=%lf.\n",X[0],X[1],X[2]);
    printf("Enter height in meters and weight in kg\n");
    scanf("%f %f",&h ,&w);	
    area=pow(2.718,X[0])*pow(w,X[1])*pow(h,X[2]);
    printf("Area is %f\n",area);
}	
