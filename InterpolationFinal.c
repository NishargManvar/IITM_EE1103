// NOTE : This file contains three different programmes as max number of files that can be submitted was 2
// All programmes are seperated by long line of astreiks (*) 


/***********************************
Purpose : Interpolation to find the values of tan(x) by the method of Lagrange's Polynomial
Authors : Nisharg_Manvar(EE19B094) , Neham_Jain(EE19B084)
Date    : 04/09/2019
Input   :Initialization values for the polynomial, Unknown Values for interpolation
Output  :Value of tan(x) from Interpolation and the true value of tan(x) 
*************************************/

//Header files and initial declarations
#include<stdio.h>
#include<math.h>
void main()
{
    float x[100],y[100],a,s=1,t=1,k=0,count;  //Declaring variables
    int n,i,j,d=1;
    printf("\nEnter the number of the terms of the table: ");  // Taking input from the user
    scanf("%d",&n);
    printf("\n\n Enter the value of x: \n");
    for(i=0; i<n; i++)
    {
        scanf ("%f",&x[i]);
        y[i]=tan(x[i]);     // Finding the corresponding tan(x) value from the input from the user
    }
    while(d==1)
    {   
        
    	k=0;
        printf(" \nEnter the value of the x to find the respective value of y\n"); //Unknown Value
        scanf("%f",&a);
        for(i=0; i<n; i++)  // Code for lagrange's Polynomial, source: https://www.codewithc.com/c-program-for-lagrange-interpolation/
        {
            s=1;
            t=1;
            for(j=0; j<n; j++)
            {
                if(j!=i)
                {
                    s=s*(a-x[j]);
                    t=t*(x[i]-x[j]);
                }
            }
            k=k+((s/t)*y[i]);
        }
        printf("\n\n The respective value of tan(x) from interpolation is: %f while the true value is %f ",k,tan(a));
        printf("\n\n Do you want to continue?\n\n Press 1 to continue and any other key to exit");
        scanf("%d",&d);
    }
}

/************************************************************************************************/


/*******************************************
Purpose : Interpolation Assignment (Newtonian Interpolation Method)
Authors : Nisharg_Manvar(EE19B094),Neham_Jain(EE19B084)
Input   : Points which are to be interpolated and the x co-ordinate whose y co-ordinate is intended
Output  : Y co-ordinate of the interpolated polynomial corresponding to x co-ordinate
Date    : 4/09/2019
********************************************/
// Header Files
#include <stdio.h>
// Functions in programme
float divide(int n,int i,float *x,float *y);
float final(float fx,int n,float *x,float *y);
// Main begin
int main()
{
	// Initilization of variables
	float xc[100],yc[100];
	float value;
	float finalx;
	int n,i;
	// Taking points as input from the user and storing them
	printf("\n\n Enter the number of points you want to enter : ");
	scanf("%d",&n);
	printf("Enter x and y co-ordinates seperated by one space\n");
	for(i=0; i<n; i++)
    {
        scanf("%f %f",&xc[i],&yc[i]);
    }
    // Declaring pointers to the array containing the co-ordinates
    float *x=xc;
	float *y=yc;
	// Taking the value of x where function value is intended from user
	printf("Enter the x-cordinate whose function value is desired : ");
	scanf("%f",&finalx);
	value = final(finalx,n-1,x,y); // Calling value function
	printf("\n The value of function at given x-cordinate is %f\n",value); //Printing y co-ordinate
	return 0;
}//main function end

// Function to caluculate divided difference using reccursion
// n is the max order of divided difference i.e. starting value, i is the max index of x co-ordinate in the required nth order divided difference
// x and y are pointers to arrays containing x and y co-ordinates
float divide(int n,int i,float *x,float *y)
{
	float result;
	if(n==1) // Case of 1st order divided difference
	{
		result=(y[i]-y[i-1])/(x[i]-x[i-1]);
		return result;
	}
	// Break nth order divided difference into (n-1)th order divided difference and call function again
	result = (divide(n-1,i,x,y)-divide(n-1,i-1,x,y))/(x[i]-x[i-n]);
	return result;
}// divide function end

// Function for calculating and adding all the interpolating polynomials
// finalx is the x co-ordinate whose function value is needed, n is degree of interpolating polynomial to be formed
// x and y are pointers to arrays containing x and y co-ordinates
float final(float finalx,int n,float *x,float *y)
{
	//Initilaztions
	float temp=1;
	int i;
	if(n==0) // Case where polynomial having only constant term
		return y[0];
	else // Method to calculate interpolating polynomial of degree n
	{
		for(i=0;i<n;i++)
		{
			temp = temp * (finalx-x[i]);
		}
		temp = temp * divide(n,n,x,y); // final interpolating polynomial of degree n
		return (temp + final(finalx,n-1,x,y)) ; //return after adding to old value and calling the function to add the lower degree term 
	}
}// final function end


/***************************************************************************************************/


/*******************************************
Purpose : Interpolation Assignment (Downsampling + Cubic spline + Root mean square error)
Authors : Nisharg_Manvar(EE19B094),Neham_Jain(EE19B084)
Input   : Files containing the points to be in the same directory named as "Subsampling.txt"
Output  : Interpolated values at all points and RMS error between original and interpolated values
Date    : 4/09/2019
********************************************/
// Header Files
#include<stdio.h>
#include<math.h>

// Function to calculate cubic spline polynomials according to algorithm given in the cubicspline.pdf file attached
// x and y are pointers to arrays containing x and y co-ordinates
// k is number of points given by user , xi is the x xo-ordinate whose interpolated function value is intended
float cubicspline(float *x,float *y, int k,int xi)
{
	// Initilization of variables
	int n,i;
	n = k-1;
	float h[n],b[n],v[n],u[n],z[n+1];
	
	// Following complex algorithm as per cubicspline.pdf file attached	
	for(i = 0; i < n; i++)
	{
		h[i] = x[i+1] - x[i];
	}
	
	for(i = 0; i < n; i++)
	{
		b[i] = (y[i+1] - y[i])/h[i];
	}

	for(i = 1; i < n; i++)
	{
		v[i] = 2*(h[i-1]+h[i]);
	}

	for(i = 1; i < n; i++)
	{
		u[i] = 6*(b[i] - b[i-1]);
	}

	z[0] = z[n] = 0;

	float mat[n-1][n-1];
	for(i = 0; i < n-1; i++)
	{
		mat[i][i] = v[i+1];
	}

	for(i = 0; i < n-2; i++)
	{
		mat[i][i+1] = h[i+1];
		mat[i+1][i] = h[i+1];
	}

	//gaussian elimination for tridiagonal systems
	float m;
	for(i = 2; i < (n-1);i++)
	{
		m = h[i-1]/v[i-1];
		v[i] = v[i] - m*h[i-1];
		u[i] = u[i] - m*u[i-1];	
	}
	
	z[n-1] = u[n-1]/v[n-1];
	for(i = (n-2); i > 0; i--)
	{
		z[i] = (u[i]-h[i]*z[i+1])/v[i];
	}
	float result;
	
	
	for(i = 1; i < n+1;i++)
	{
		if((xi > x[i-1])&&(xi<x[i]))
		{
			result = z[i]*pow((xi - x[i-1]),3)/(6*h[i-1])+z[i-1]*pow((x[i] - xi),3)/(6*h[i-1])+((y[i]/h[i-1])-((z[i]*h[i-1])/6))*(xi-x[i-1])+((y[i-1]/h[i-1])-((z[i-1]*h[i-1])/6))*(x[i]-xi);
			// result is the final y co-ordinate
		}
	}
	return result; // returning result
	
}

// main function begin
int main()
{
	// Initilization of variables
	char c,ch[100];
	int count=1,loopx=0,finalx;
	float xc[1000],yc[1000],f,fi[1000];
	
	//Declaring pointers to files in the directory of the programme
	FILE *fp,*fpt,*ftpr;
	ftpr=fopen("interpolated.txt","w"); // Final wanted resulting file
	fp=fopen("Subsampling.txt","r");	// File containing all the initial values
	fpt=fopen("downsampled.txt","w");	// File contaiining downsampled values (i.e. every 10th value)
	
	// Reading every 10th value from Subsampling.txt and storing into downsampling.txt
	while((c= fgetc(fp)) != EOF )
	{
	   if(c=='\n')
		{
			count++;
		}	   		
		if(count%10==1)
		{
			fscanf(fp,"%[^\n]",ch);
			f=atof(ch);
			fprintf(fpt,"%d %f\n",count,f);
			xc[loopx]=count;
			yc[loopx]=f;
			loopx++;
		}
	}
	
	// Reading all the initial values and storing in an array
	for(finalx=1;finalx<=count;finalx++)
	{
		fscanf(fp,"%[^\n]",ch);
		f=atof(ch);
		fi[finalx]=f;
	}
	
	// Variables required for interpolation and RMS error caluclation
	float rmsq=0;
	int ran=0;
	float *x=xc;
	float *y=yc;
	
	// Calculation interpolated function y co-ordinates for all x co-ordinates
	for(finalx=1;finalx<=count;finalx++)
	{
		if(finalx%10!=1) // x co-ordinates ommited in downsampling
		{
			fprintf(ftpr,"%d %f\n",finalx,cubicspline(x,y,loopx,finalx)); // Storing values in file named "interpolated.txt"
			rmsq=rmsq+pow((fi[finalx]-cubicspline(x,y,loopx,finalx)),2);	// calculating sum of squares of error
		}
		else // x co-ordinates read during downsampling
		{
			fprintf(ftpr,"%d %f\n",finalx,yc[ran]);	// Storing values in file named "interpolated.txt" 
			ran++;	// As this values itself are used for interpolation, they are useless for error calculation
		}
	}
	rmsq=sqrt(rmsq/count);	// calculating RMS error value
	printf("%f",rmsq);	// Printing RMS error value on output console
	return 0;
}// end of main


/***************************************************************************************************/
