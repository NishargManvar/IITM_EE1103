/********************************************************
Autors  : Nisharg_Manvar (EE19B094) , Neham_Jain (EE19B084)
Purpose : Integration Assignment i.e. implementing midpoint, trapezoid and Simpson's methods of integration
Date    : 11th September 2019
Input   : 1)Text file named "output.txt with the 502 given datapoints in the same directory as this program
          2) Assign the value of deltax to "deltax" variable
Output  : Three text files with respective integration methods containing the value of deltax and error in integration
********************************************************/

//Header files declaration
#include<stdio.h>
#include<math.h>
#include<stdlib.h>

//Lists of functions defined in this program
float trapezoid(int loopx,float deltax,float *fpointer);	//function to calculate integration using trapezoid method
float box(int loopx,float delta, float *fpointer);	//function to calculate integration using box method
float simpson(int loopx,float deltax,float *fpointer);	//function to calculate integration using simpson's method
float cubicspline(float *x,float *y, int k,float xi);	//function to interpolate values using cubicspline method
void dump_row(size_t i, double *R);	//function to dump a row
//function to calculate integration value using romberg's method
double romberg(float *xc,float *yc,int loopx, double /*lower limit*/ a, double /*upper limit*/ b, size_t max_steps, double /*desired accuracy*/ acc);

//Beginning of main function
int main()
{
	//Declaring file pointers and variables
	FILE *fpt,*trap,*boxf,*simp;	
	fpt=fopen("output.txt","r");
	trap=fopen("trapezoid.txt","a");
	boxf=fopen("box.txt","a");
	simp=fopen("simpsons.txt","a");
	float a,sum=0,yc[10000],xc[10000],deltax=5.001,finalx=0,fcubic[10000];
	int count=1,i=0,loopx=0;
	char c,ch[100];
	
	//Reading values from output.txt
	while((c= fgetc(fpt)) != EOF )
	{
	   if(c=='\n')
	   {
	     count++;
       }	   		
	   
	    fscanf(fpt,"%[^\n]",ch);
	    yc[loopx]=atof(ch);	//storing y-coordinate in array 'yc'
		xc[loopx]=count;	//storing x-coordinate in array 'xc'
		loopx++;
	}
	
	//interpolating values with cubicslpine method
	for(finalx=1+deltax;finalx<=(float)loopx;finalx+=deltax)
	{
			fcubic[i]=cubicspline(xc,yc,loopx,finalx); //saving interpolated values in array 'fcubic'
			i++;
	}
	
	double reference=romberg(xc,yc,loopx,1,501,18,0.00001); //calculating integration value using romberg's method
		
	fprintf(trap,"%f %f\n",deltax,trapezoid(i,deltax,fcubic)-reference); //Printinf error in trapezoid method in file
	fprintf(boxf,"%f %f\n",deltax,box(i,deltax,fcubic)-reference);	//Printinf error in box method in file
	fprintf(simp,"%f %f\n",deltax,simpson(i,deltax,fcubic)-reference);	//Printinf error in simpson's method in file

	return 0; //Return 0 if no runtime errors
}
//End of main function

//Beginning of trapezoid method
//Arguments for function include number of points , deltax, pointer to points respectively
float trapezoid(int loopx,float deltax,float *fpointer)
{
	int i;
	float a,sum=0;
	for(i=0;i<(loopx);i++)	//Adding the area of each trapezoid to get intigration value
	{
	    a=(fpointer[i]+fpointer[i+1])*deltax/2;
	    sum=sum+a;
	}
	
	return sum; // Return the value of integration

}// End of trapezoid function

//Beginning of box function
//Arguments for function include number of points , deltax, pointer to points respectively
float box(int loopx,float deltax, float *fpointer)
{
	int i;
	float a,sum=0;
	for(i=0;i<loopx;i++)	//Adding the area of boxes to get integration value
	{
		a=fpointer[i]*deltax;
		sum = sum + a;
	}
	
	return sum; //Returning the value of integration

}// End of box function

//Beginning of simpson function
//Arguments for function include number of points , deltax, pointer to points respectively
float simpson(int loopx,float deltax,float *fpointer)
{
	//Implementing algorithm of simpson's method
	int i,n;
	float x0=1,xn=502,h=deltax,y[10000],so,se,ans,x[10000];
    n=(xn-x0)/h;
    if(n%2==1)
    {
        n=n+1;
    }
    h=(xn-x0)/n;
    
    for(i=0; i<loopx; i++)
    {
        x[i]=x0+i*h;
    }
    so=0;
    se=0;
    for(i=1; i<loopx; i++)
    {
        if(i%2==1)
        {
            so=so+fpointer[i];
        }
        else
        {
            se=se+fpointer[i];
        }
 
    }
    ans=h/3*(fpointer[0]+fpointer[loopx-1]+4*so+2*se);
    
	return ans;//Returning the value of integration

}//End of simpson function

//Beginning of cubicspline function
//Arguments for function include pointer to x-coordinate, y-coordinate, number of points, value of x-coordinate whose value is intended
float cubicspline(float *x,float *y, int k,float xi)
{
	//Applying cubicspline method's algorithm
	int n,i;	
	n = k-1;
	float h[n],b[n],v[n],u[n],z[n+1];	
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
		}
	}
	return result;
		

}//End of cubicspline function

//Beginning of dump_row function
void dump_row(size_t i, double *R)
{
   //Used to dump a row

}//End of dump_row function

//Beginning of romberg function
double romberg(float *xc,float *yc,int loopx, double /*lower limit*/ a, double /*upper limit*/ b, size_t max_steps, double /*desired accuracy*/ acc)
{
   double R1[max_steps], R2[max_steps]; //buffers
   double *Rp = &R1[0], *Rc = &R2[0]; //Rp is previous row, Rc is current row
   double h = (b-a); //step size
   Rp[0] = (yc[0] + yc[501])*h*.5; //first trapezoidal step

   dump_row(0, Rp);
   size_t i,j;
   for(i = 1; i < max_steps; ++i){
      h /= 2.;
      double c = 0;
      size_t ep = 1 << (i-1); //2^(n-1)
      for( j = 1; j <= ep; ++j)
	  {
         c += cubicspline(xc,yc,loopx,(a+(2*j-1)*h));
      }
      Rc[0] = h*c + .5*Rp[0]; //R(i,0)

      for(j = 1; j <= i; ++j){
         double n_k = pow(4, j);
         Rc[j] = (n_k*Rc[j-1] - Rp[j-1])/(n_k-1); //compute R(i,j)
      }

      //Dump ith column of R, R[i,i] is the best estimate so far
      dump_row(i, Rc);

      if(i > 1 && fabs(Rp[i-1]-Rc[i]) < acc){
         return Rc[i-1];
      }

      //swap Rn and Rc as we only need the last row
      double *rt = Rp;
      Rp = Rc;
      Rc = rt;
   }
   return Rp[max_steps-1]; //return our best guess
}//End of romberg function
