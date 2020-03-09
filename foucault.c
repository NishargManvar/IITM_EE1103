/************************************************
Purpose : Foucault Pendulum Assignment i.e. simulating Foucault Pendulum with given initial parameters using different methods
Date    : 24th October 2019
Authors : Pranav Phatak(EE19B105),Nisharg Manvar(EE19B094)
Input   : To change step size, n changes can be made in main funcion, we have used optimal values for each
Output  : 4 gnuplot graphs, one each of Euler , Heun , Runge_Kutta , RK45.
References : http://maths.cnam.fr/IMG/pdf/RungeKuttaFehlbergProof.pdf for the coefficients of RK45.
	     Numerical Methods by Chapra for coefficients of Runge-Kutta.	
*************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define a 0.00007
#define b 1
#define phi 0.6

//Function for Euler's method
//Argumennts include step size h and number of points to be calculated
void Euler(float h,int N)
{
	float U[N],V[N],X[N],Y[N],T[N];	//U stands for x(dot), V stands for y(dot), X for x and Y for y, T for time
		
	//creating pointer of file for saving the values of X and Y
	FILE *fptr=fopen("foucault_euler.dat","w");
	
	//Variable initalization
	X[0]=1;Y[0]=0;
	U[0]=1;V[0]=3/2;
	T[0]=0;
	
	//Steps to solve differential equatons using euler's method 
	for(int i = 0; i < N-1; i++)
	{       
		
		U[i+1] = U[i]+h*(-b*X[i]+2*a*V[i]*sin(phi));	//Finding next value of U using DE of focault pendulum
		V[i+1] = V[i]+h*(-b*Y[i]-2*a*U[i]*sin(phi));	//Finding next value of V using DE of focault pendulum

		X[i+1] = X[i]+h*U[i];	//Finding next value of x by using U=x(dot)
		Y[i+1] = Y[i]+h*V[i];	//Finding next value of y by using V=y(dot)

		T[i+1] = T[i]+h;	//Next value of Time
	}
		//saving the X, Y, Time values in a file and plotting the curve in gnuplot
	for(int i = 0; i < N-1; i++)
		fprintf(fptr,"%lf %lf %lf\n", X[i+1], Y[i+1],T[i+1]); 

	//List of commands to be given to gnuplot
    char * commands[] = {"set title \"euler's method\"","set ylabel 'Y'","set xlabel 'X'", "plot 'foucault_euler.dat' w l "};
	FILE * gnuplot = popen("gnuplot -persistent","w");	//Open gnuplot

	for(int i=0; i < 4; i++)
		fprintf(gnuplot, "%s \n", commands[i]); //Send commands to gnuplot one by one.
		
	fclose(fptr);
	

}//End of euler's function

//Start of heun function
//Arguments include step size h and number of points N
void Heun(float h,int N)
{
	
        
	//creating pointer of file for saving the values of X and Y
	FILE *fptr=fopen("foucault_heun.dat","w");

	float U[N],V[N],X[N],Y[N],T[N];	//U stands for x(dot), V stands for y(dot), X for x and Y for y, T fot time
	float Umid,Vmid,Xmid,Ymid;	//Variables to store values of U,V,X,Y at the mid-point of two consecutive points
	
	//initialising the variables
	X[0]=1;Y[0]=0;
	U[0]=1;V[0]=3/2;
	T[0]=0;

	//Steps to solve the DEs by heun's method
	for(int i = 0; i < N-1; i++)
	{

		//finding the midpoint values of corresponding values
		Umid = U[i]+0.5*h*(-b*X[i]+2*a*V[i]*sin(phi));
		Vmid = V[i]+0.5*h*(-b*Y[i]-2*a*U[i]*sin(phi));
		
		Xmid = X[i]+0.5*h*U[i];
		Ymid = Y[i]+0.5*h*V[i];
		
		//solving DEs by taking slope at midpoint
		U[i+1] = U[i]+h*(-b*Xmid+2*a*Vmid*sin(phi));
		V[i+1] = V[i]+h*(-b*Ymid-2*a*Umid*sin(phi));

		X[i+1] = X[i]+0.5*h*Umid;
		Y[i+1] = Y[i]+0.5*h*Vmid;
			
		T[i+1] = T[i]+h;
	}

	//saving the X,Y,Time values in a file and plotting the curve in gnuplot
	for(int i = 0; i < N-1; i++)
		fprintf(fptr, "%lf %lf %lf\n", X[i+1], Y[i+1], T[i+1]); 

	//List of commands to be given to gnuplot
    char * commands[] = {"set title \"heun's method\"","set ylabel 'Y'","set xlabel 'X'", "plot 'foucault_heun.dat' w l "};
	FILE * gnuplot = popen ("gnuplot -persistent", "w");	//Open gnuplot

	for (int i=0; i < 4; i++)
		fprintf(gnuplot, "%s \n", commands[i]); //Send commands to gnuplot one by one.
	
	fclose(fptr);

}//End of heun's method function

//Start of Runge_Kutta method function
//Arguments include step size h and number of points N
void Runge_Kutta(float h,int N)
{
	
	//creating a file for saving the values of X and Y
	FILE *fptr=fopen("foucault_RK4.dat","w");
		
	float U[N],V[N],X[N],Y[N],T[N];	//U stands for x(dot), V stands for y(dot), X for x and Y for y, T for time
	
	//initialising the variables
	X[0]=1;Y[0]=0;
	U[0]=0;V[0]=0;
	T[0]=0;
	
	//Variables to store values of corresponding variables at different points between two points
	float U1,U2,U3,U4;
	float V1,V2,V3,V4;
	float Y1,Y2,Y3,Y4;
	float X1,X2,X3,X4;
	
	for(int i = 0; i < N-1; i++)
	{       
		//solving dU/dt		
		U1 = -b*X[i]+2*a*V[i]*sin(phi) ;	//Increment based on slope at initial point
		U2 = -b*(X[i]+0.5*h)+2*a*(V[i]+0.5*U1*h)*sin(phi);	//Increment based on the slope at the midpoint using U1
		U3 = -b*(X[i]+0.5*h)+2*a*(V[i]+0.5*U2*h)*sin(phi);	//Increment based on the slope at the midpoint but using U2
		U4 = -b*(X[i]+h)+2*a*(V[i]+U3*h)*sin(phi);	//Increment based on the slope at the end of the interval using U3
		U[i+1] = U[i]+h*(U1+2*U2+2*U3+U4)/6;	//Next value of U based on values calculated above
		
		//Applying above method for all the variables
		
		X1 = U[i+1];
		X2 = U[i+1]+0.5*h;
		X3 = U[i+1]+0.5*h;
		X4 = U[i+1]+h;
		X[i+1] = X[i]+h*(X1+2*X2+2*X3+X4)/6;
		
		V1 = -b*Y[i]-2*a*U[i]*sin(phi) ;
		V2 = -b*(Y[i]+0.5*h)-2*a*(U[i]+0.5*U1*h)*sin(phi);
		V3 = -b*(Y[i]+0.5*h)-2*a*(U[i]+0.5*U2*h)*sin(phi);
		V4 = -b*(Y[i]+h)-2*a*(U[i]+U3*h)*sin(phi);
		V[i+1] = V[i]+h*(V1+2*V2+2*V3+V4)/6;

		Y1 = V[i+1];
		Y2 = V[i+1]+0.5*Y1*h;
		Y3 = V[i+1]+0.5*Y2*h;
		Y4 = V[i+1]+Y3*h;
		Y[i+1] = Y[i]+h*(Y1+2*Y2+2*Y3+Y4)/6;
	
		T[i+1] = T[i]+h;
	}
	
	//saving the X,Y,Time values in a file and plotting the curve in gnuplot
	for(int i = 0; i < N-1; i++)
		fprintf(fptr, "%lf %lf %lf\n", X[i+1], Y[i+1],T[i+1]); 

	//List of commands to be given to gnuplot
    char * commands[] = {"set title \"RungeKutta's method\"","set ylabel 'Y'","set xlabel 'X'", "plot 'foucault_RK4.dat' u 1:2:3 w l "};
	FILE * gnuplot = popen ("gnuplot -persistent", "w");	//Open gnuplot
	
	for (int i=0; i < 4; i++)
		fprintf(gnuplot, "%s \n", commands[i]); //Send commands to gnuplot one bY one.

	fclose(fptr);

}//End of Runge_Kutta method function

//Beginning of RK45 method function
//Arguments include step size h and number of points N
void RK45(float h,int N)
{
		
	//creating pointer of file for saving the values of X and Y
	FILE *fptr=fopen("foucault_RK45.dat","w");
	
	float U[N],V[N],X[N],Y[N],T[N];	//U stands for x(dot), V stands for y(dot), X for x and Y for y, T for time
	
	//initialising the variables
	X[0]=1;Y[0]=0;
	U[0]=1;V[0]=3/2;
	T[0]=0;
	
	
	//Variables to store values of corresponding variables at different points between two points
	float U1,U2,U3,U4,U5,U6;
	float V1,V2,V3,V4,V5,V6;
	float X1,X2,X3,X4,X5,X6;
	float Y1,Y2,Y3,Y4,Y5,Y6;
	
	for(int i = 1; i < N-1; i++)
	{       
		//solving for next value of U using various points in middle		
		U1 = -b*X[i]+2*a*V[i]*sin(phi) ;
		U2 = -b*(X[i]+0.25*h)+2*a*(V[i]+0.25*U1*h)*sin(phi);
		U3 = -b*(X[i]+3*h/8)+2*a*(V[i]+3*h*U1/32+9*h*U2/32)*sin(phi);
		U4 = -b*(X[i]+12*h/13)+2*a*(V[i]+1932*U1/2197-7200*h*U2/2197+7296*h*U3/2197)*sin(phi);
		U5 = -b*(X[i]+h)+2*a*(V[i]+439*h*U1/216-8*U2+3680*U3/513-845*h*U4/4104)*sin(phi);
		U6 = -b*(X[i]+0.5*h)+2*a*(V[i]-8*h*U1/27+2*h*U2-3544*h*U3/2565+1859*U4*h/4104-11*h*U5/40)*sin(phi);
		U[i+1] = U[i]+h*(16*U1/135+6656*U3/12825+28561*U4/56430-9*U5/50+2*U6/55);
		
		//Applying same method for all other variables
		
		X1 = U[i+1];
		X2 = U[i+1]+0.25*X1*h;
		X3 = U[i+1]+0.5*h*X2;
		X4 = U[i+1]+0.5*h*X3;
		X5 = U[i+1]+0.75*h*X4;
		X6 = U[i+1]+h*X5;
		X[i+1] = X[i]+h*(16*X1/135+6656*X3/12825+28561*X4/56430-9*X5/50+2*X6/55);	
		
		V1 = -b*Y[i]+2*a*U[i]*sin(phi) ;
		V2 = -b*(Y[i]+0.25*h)+2*a*(U[i]+0.25*V1*h)*sin(phi);
		V3 = -b*(Y[i]+3*h/8)+2*a*(U[i]+3*h*V1/32+9*h*V2/32)*sin(phi);
		V4 = -b*(Y[i]+12*h/13)+2*a*(U[i]+1932*V1/2197-7200*h*V2/2198+7296*h*V3/2197)*sin(phi);
		V5 = -b*(Y[i]+h)+2*a*(U[i]+439*h*V1/216-8*V2+3680*V3/513+845*h*V4/4104)*sin(phi);
		V6 = -b*(Y[i]+0.5*h)+2*a*(U[i]-8*h*V1/27+2*h*V2-3544*h*V3/2565+1859*V4*h/4104-11*h*V5/40)*sin(phi);
		V[i+1] = V[i]+h*(16*V1/135+6656*V3/12825+28561*V4/56430-9*V5/50+2*V6/55);
		
		Y1 = V[i+1];
		Y2 = V[i+1]+0.25*Y1*h;
		Y3 = V[i+1]+h*Y1/8+h*Y2/8;
		Y4 = V[i+1]-h*Y2/2+h*Y3;
		Y5 = V[i+1]+3*h*Y1/16+9*h*Y4/16;
		Y6 = V[i+1]-3*h*Y1/7+2*h*Y2/7+12*h*Y3/7-12*Y4*h/7+8*h*Y5/7;
		Y[i+1] = Y[i]+h*(16*Y1/135+6656*Y3/12825+28561*Y4/56430-9*Y5/50+2*Y6/55);
		
		T[i+1]=T[i]+h;
	}
	
	//saving the X,Y,Time values in a file and plotting the curve in gnuplot
	for(int i = 0; i < N-1; i++)
		fprintf(fptr, "%lf %lf %lf\n", X[i+1], Y[i+1],T[i+1]);

	//List of commands to be given to gnuplot
    char * commands[] = {"set title \"RK45 method\"","set ylabel 'Y'","set xlabel 'X'", "plot 'foucault_RK45.dat' w l "};
	FILE * gnuplot = popen ("gnuplot -persistent", "w");	//Open gnuplot

	for (int i=0; i < 4; i++)
		fprintf(gnuplot, "%s \n", commands[i]); //Send commands to gnuplot one by one.

	fclose(fptr);
}//End of RK45 method function

//Start of main function
int main()
{
	//Call to functions with appropriate arguments values	
	Euler(0.01,20000);
	Heun(0.05,10000);
	Runge_Kutta(0.05,10000);
	RK45(0.1,4000);

	return 0;
}//End of main
