/*****
***Purpose:Learn how to solve 3 linear equations using LU decomposition and use this method for cubic spline interpolation.
***Authors:Pranav Phatak(EE19B105),Nisharg Manvar(EE19B094)
***Input: The number of points.
	  The value of x coordinate and y coordinate separated by a space.
	  The value of x at which the function has to be interpolated.
***Output: The value of the function at the required point.
***Date: 18-9-19
*****/

//Including header files
#include<stdio.h>
#include<math.h>
#include<stdlib.h>

//function for generating cubic splines
//function arguments include x-coordinate list, y-coordinate list, number of points, x-coordinate whose function value is needed 
void cubicspline(float x[100],float y[100], int k,float xi)
{
	int n;	
	n = k-1;
	float h[n],b[n],v[n-1],u[n-1],z[n+1];
	int i,j;
	for(i = 0; i < n; i++)
	{
		h[i] = x[i+1] - x[i];
	
	}
	
	for(i = 0; i < n; i++)
	{
		b[i] = (y[i+1] - y[i])/h[i];
		
	}

	for(i = 0; i < n-1; i++)
	{
		v[i] = 2*(h[i+1]+h[i]);
	}

	for(i = 0; i < n-1; i++)
	{
		u[i] = 6*(b[i+1] - b[i]);
	}

	z[0] = z[n] = 0;

	float mat[n-1][n-1];
	for(i = 0; i < n-1; i++)
	{
		mat[i][i] = v[i];
	}

	for(i = 0; i < n-2; i++)
	{
		mat[i][i+1] = h[i+1];
		mat[i+1][i] = h[i+1];
	}

	int row,column,ctr1,ctr2;
	float lowertriangle[n-1][n-1];//matrices for lower and uppper triangle
	float uppertriangle[n-1][n-1];
	for(row=0;row<n-1;row++)
	{	for(column=0;column<n-1;column++)
		{
			if(row>column)//initialise all elements of lower triangle in upper triangular matrix as 0
				uppertriangle[row][column]=0.0;
			if(row<column)//initialise all elements of upper triangle in lower triangular matix as 0
				lowertriangle[row][column]=0.0;
			if(row==column)//initialise all diagonal elements of lower triangular matrix as 1
				lowertriangle[row][column]=1.0;
		}
	}
	ctr2 = 0;
	int m = 1;
	while(ctr2 < n-1)//loop for LU decomposition of the matrix
	{	
		for(ctr1 = m; ctr1<n-1;ctr1++)
		{
			float mul[n-1];
			mul[ctr1] = mat[ctr1][ctr2]/mat[ctr2][ctr2];
			lowertriangle[ctr1][ctr2] = mul[ctr1];
			row = ctr1;
			for(column = ctr2;column<n-1;column++)
			{
				mat[row][column] = mat[row][column] - mul[ctr1]*mat[ctr2][column];
			}
		}
		m++;
		ctr2++;
	}

	printf("UPPER TRIANGULAR MATRIX\n");
	for(row=0;row<n-1;row++)
	{//displays upper triangular matrix
        for(column=0;column<n-1;column++)
        {
			uppertriangle[row][column] = mat[row][column];
			printf("%.2f ",uppertriangle[row][column] );
		}
		printf("\n");
    }
    printf("LOWER TRIANGULAR MATRIX\n");
    for(row=0;row<n-1;row++)
    {//displays lower triangular matrix
        for(column=0;column<n-1;column++)
			printf("%.2f ",lowertriangle[row][column]);
		printf("\n");
    }

	float Y[n-1];
	for(i=0; i<n-1; i++)//loops to find the constants of the cubicspline
    {
		Y[i]=u[i];
        for(j=0; j<i; j++)
        {
			Y[i] = Y[i] - lowertriangle[i][j]*Y[j];
	}
    }

	for(i=n-1; i>=1; i--)
    {
        z[i]= Y[i-1];
        for(j=i+1; j<n; j++)
        {
			z[i]=z[i]-uppertriangle[i-1][j-1]*z[j];
        }
		z[i] = z[i]/uppertriangle[i-1][i-1];
    }

	float result;
	for(i = 1; i < n+1;i++)
	{
		if((xi > x[i-1])&&(xi<x[i]))
		{
			result = z[i]*pow((xi - x[i-1]),3)/(6*h[i-1])+z[i-1]*pow((x[i] - xi),3)/(6*h[i-1])+((y[i]/h[i-1])-((z[i]*h[i-1])/6))*(xi-x[i-1])+((y[i-1]/h[i-1])-((z[i-1]*h[i-1])/6))*(x[i]-xi);					
			printf("value of the function at x = %.2f is y =  %.4f \n",xi,result);
		}
	}
}

//Beginning of main function
int main()
{
	//Variable declartions
	int no;	//variable to store number of 
	float x[100],y[100];	//arrays to store userdefined co-ordinates
	printf("Enter the number of points less than 100 : ");
	scanf("%d",&no);

	int i;	//loop control variable
	printf("\nEnter the x value and the y value of the function for the number of points mentioned above: \n");
	for(i = 0; i < no;i++)
	{
		scanf("%f %f",&x[i],&y[i]);
	}
		
	int test=1;	
	float xi; //variable to store value of x-coordinate whose value is to be interpolated
	printf("Enter the value of x at which the value of y is needed : ");
	scanf("%f",&xi);
	for(i=0;i<no;i++)	//checking if xi is equal to any of the userdefined x-coordinate and if true printing y-coordinate directly
	{
		if(xi==x[i])
		{
			printf("value of the function at x = %.2f is y =  %.4f \n",xi,y[i]);
			test=0;
		}
	}
	if(test==1)
	    cubicspline(x,y,no,xi);	//call to cubicspline function 
return 0;
}//End of main function
//End of program
