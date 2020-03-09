/**************************
Purpose : Mean and Variance and learning basic terminal commands
Authors : Neham_Jain(EE19B084) , Nisharg_Manvar(EE19B094) , Viswa_Koduru(EE19B060)
Date    : 08/08/2019
Input   : No input
Output  : Mean and Variance of the data
***************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<unistd.h>
void main()

{	
    //Initialisation
	char c,d;	
	char ch[100];
	float total=0.0 ;
	float f[1000];
	float mean,dev;
	int n,i=0;
	
	FILE *fp;
	
	//Change the value "10" in the next line to change the number of time you want to ping 	
	system("echo Pinging www.iitm.ac.in  ");
	system("ping www.iitm.ac.in -c 10 >ping.dat");
	fp=fopen("ping.dat","r");
	
	//File Reading and Value Storing
	int count=0;
	c=fgetc(fp);
	while(c!= EOF)
	{	
	    d=fgetc(fp);
	    //taking the value after time= in the ping.dat file until the blank space
  		if(c=='e' && d=='=')
		{
			fscanf(fp,"%[^ ]",ch);
			f[i]=atof(ch);
			i++;
			count++;
		}
		c=d;
		
	}
    printf("The website was pinged %d times \n" , count);
	//Mean Calculation
	for(n = 0 ; n < i ; n++)
	{
		total = total + f[n] ;
	}
	mean = total/i;
	printf("The mean of the values taken from ping.txt is %.3f " , mean);

	//Standard Deviation
	total=0;	
	for(n=0;n<i;n++)
	{
			total=total+pow((f[n]-mean),2);
	}	
	dev=sqrt(total/i);
	printf("\nThe standard deviation of the values is %f  \n", dev);
	fclose(fp);
}

