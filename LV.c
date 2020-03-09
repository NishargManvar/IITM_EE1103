/*
***********************************************************************************************************************************************
EE1103-Numerical Methods
Assignment 5) Generate a plot of the Lotka Volterra dynamics between predator and prey. Show both the time series and the phase plots (predator vs prey)
This program will:
	-use time count to be considered and initial values of prey and predator to plot a graph of population vs time and a phase plot of prey vs predator
Done by: Pranav Phatak(EE19B105),Nisharg Manvar(EE19B094)	
General formula used: dx=x(a-by) , dy=-y(c-dx)
Input: Time , Initial values of prey and predator in the system
Output: Plots of prey & predator vs time and plot of prey vs predator i.e phase plot
Date: 26th September 2019
Run command: gcc LV.c  
	     ./a.out
	     'T', 'x0' & 'y0' values.
***********************************************************************************************************************************************
*/


#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int main() 
{
        int T, x0, y0;
        printf("Enter time count,initial values of prey and predator(all integers,initial values should be of same order and time greater than 400 to see oscillations)\n");
        scanf("%d %d %d", & T, & x0, & y0);

        FILE * prey = fopen("prey.dat", "w");
        FILE * predator = fopen("predator.dat", "w");
        FILE * pvsp = fopen("phase.dat", "w");
        float x[T]; //Array for Prey
        float y[T]; //Array for Predator
        float t[T]; //Time array
        float dt = 1; //time interval

        float a = 0.1, b = 0.01, c = 0.001, d = 0.05;  //giving suitable values to constants in the differential equation
        float xmid, ymid; //defining midpoints to take their differential for a better approximation of values

        x[0] = x0;
        y[0] = y0;
        t[0] = 0;

        for (int i = 1; i < T; i++) 
        {
                xmid = x[i - 1] + 0.5 * dt * (a * x[i - 1] - b * x[i - 1] * y[i - 1]);  //finding the midpoint using derivative approximation
                ymid = y[i - 1] + 0.5 * dt * (c * x[i - 1] * y[i - 1] - d * y[i - 1]);
                x[i] = x[i - 1] + dt * (a * xmid - b * xmid * ymid); //using derivative at midpoint to find the next point using differential equation
                y[i] = y[i - 1] + dt * (c * xmid * ymid - d * ymid);
                t[i] = t[i - 1] + dt;

        }

        for (int j = 0; j < T; j++) //printing values of prey,predator,time in files as needed for plotting required graphs
        {
                fprintf(prey, "%f %f \n", t[j], x[j]);
                fprintf(predator, "%f  %f\n", t[j], y[j]);
                fprintf(pvsp, "%f %f\n", x[j], y[j]);
        }

        char * commandsForGnuplot1[] = //commands for gnuplot to plot population vs time
        {
                "set title \"prey-predator\"",
                "set xlabel 'time'",
                "set ylabel 'population'",
                "plot 'prey.dat','predator.dat'"
        };
        char * commandsForGnuplot2[] = //commands for gnuplot to plot phase plot
        {
                "set title \"phase-plot\"",
                "set xlabel 'prey'",
                "set ylabel 'predator'",
                "plot 'phase.dat'"
        };

        FILE * gnuplotPipe1 = popen("gnuplot -persistent", "w");
        FILE * gnuplotPipe2 = popen("gnuplot -persistent", "w");

        for (int i = 0; i < 4; i++) 
        {
                fprintf(gnuplotPipe1, "%s \n", commandsForGnuplot1[i]); //Send commands to gnuplot one by one.
        }
        for (int i = 0; i < 4; i++) 
        {
                fprintf(gnuplotPipe2, "%s \n", commandsForGnuplot2[i]); //Send commands to gnuplot one by one.
        }

        return 0;
}
