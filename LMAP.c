/*
***********************************************************************************************************************************************
EE1103-Numerical Methods
Assignment 5) Generate a plot of the logistic map, in an "interesting range" of r
Done by: Pranav Phatak(EE19B105),Nisharg Manvar(EE19B094)	
General formula used:x[n+1]=r*x[n]*(1-x[n]) where r is a constant.
Input: -
Output: .pgm file of x[n] vs r in the range 2.5 to 4 for r. 
Date: 26th September 2019
Run command: gcc LMAP.c
	     ./a.out
	     
***********************************************************************************************************************************************
*/



#include<stdio.h>
#define lower 2.5  //lower limit of r
#define upper 4    //upper limit of r


int h=1000, w =1000;  //pixels for output .pgm file

int main()
{                                                                    
        FILE *fptr=fopen("lmap.dat","w");                 
	float x=0.5;
	int lmap[h][w], i, j;                                            
        
	for(i=0;i<h;i++)	//Initialize all elements of array to 0
		for(j=0;j<w;j++)                                           
			lmap[i][j] = 0;
	
	for(float r=lower;r<upper;r+=1.0*(upper-lower)/w)	//vary r from 2.5 to 4 in step size of 1.5/1000
	{
		for(int i=0;i<10000;i++)
		{
			x =r*x*(1-x); 								//Governing equation for finding next value of x
			fprintf(fptr,"%f  %f\n",r,x);						//printing r and corresponding x's in a .dat file for gnuplotting	
			if(lmap[(int)(x*h)][(int)(w*(r-lower)/(upper-lower))]<255)             //Pixels saturate at 255
				lmap[(int)(x*h)][(int)(w*(r-lower)/(upper-lower))]++;		//Increase intensity by 1
	 	} 
 
	}
	

	FILE *fp=fopen("lmap.pgm","w");
	fprintf(fp,"P2\n%d %d\n255\n",w,h);	//Parameters for .pgm file
	{
		for(i=999;i>=0;i--)	        //starting loop at 999 because printing starts from the top which will give an inverted y axis if we start from 0, 							starting from 999 at the top we go to 0 towards the bottom to revert the y axis to its original alignment.
		{
			for(j=0;j<w;j++)
			{
                           fprintf(fp,"%d ",lmap[i][j]);  //printing values of array into a .pgm file
                        }
                }
        }
	fclose(fp);
	printf("SUCCESS, refer lmap.pgm for the output and a gnuplot window will pop up ( give it time to load since it has to plot many values )\n");		
        
        char * commandsForGnuplot[] = //commands for gnuplot to plot population vs time
        {
                "set title \"logistic-map\"",
                "set xlabel 'value of r'",
                "set ylabel 'x[n]'",
                "set xrange [2.5:4]",
                "plot 'lmap.dat' with dots"
        };
        FILE * gnuplotPipe = popen("gnuplot -persistent", "w");
        for (int i = 0; i < 5; i++) 
        {
                fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]); //Send commands to gnuplot one by one.
        }
        return 0;
}
