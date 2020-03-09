/***********************************************
Purpose : Real Time data analysis using first in first out method.
			This code uses real life experiment data graphs (therefore too big to analyse while storing it) and use real time data analysis.
			The aim is to find the cell count from the two graphs (i.e. peak in both graph = cell present)
Authors : Pranav Phatak(EE19B105),Nisharg Manvar(EE19B094)
Input   : Data file to be in same directory as code
Output  : 1)File containg location and width of the cells
		  2)Average width and average time on output console
Date	: 27th October 2019
************************************************/
//Including header files
#include<stdio.h>
#include<math.h>
#include<stdlib.h>

//Defining constants in the program
#define RING 100
#define horizontal_threshold 25
#define vertical_threshold 35

//User defined variable type having a float value and a pointer
struct node
{float value; struct node *next;};

//Beginning of main function
int main()
{
	FILE *file=fopen("CompleteData_fsc_ssc_10um.txt","r");	//File containg data points
	FILE *output=fopen("Cell_Output.txt","w");	//Output file containg average width and average time
	int on,start,end,count=0;	//variables for status of cell,start of cell,end of cell and number of cell
	float widthavg=0,timeavg=0;	//variables for average width and average time
	
	float read1=0,read2=0;	//Variables for storing values read from file
	struct node *head , *tail , *t;	//Starting , ending and extra node for the linked list
	head = (struct node *)malloc(sizeof *head);
	tail = (struct node *)malloc(sizeof *tail);
	t=head;
	for (int i = 0; i < RING; i++)	//Initalizing linked list of RING nodes with value 0
	{
		t->next=(struct node *)malloc(sizeof *t);
		t=t->next;
		t->value=0;
	}
	t->next=tail;
	t=head;
	for(int i=0;i<1115900;i++)	//Going through all the values of the file
	{
		struct node *new1,*temp;	//Variables for implementing first in first out method
		new1 = (struct node *)malloc(sizeof *new1);
		//printf("here\n");
		fscanf(file,"%f",&read1);	//Scanning first value of file
		fscanf(file,"%f",&read2);	//Scanning second value of file
		//printf("here\n");
		new1->value=read2;
		if((read2>horizontal_threshold && abs((int)read1-2650)>vertical_threshold) && on==0) //Starting of the cell
		{
			start = i;	//Starting position of cell
			on = 1 ;	//Cell status is on
			count++;	//Number of cells increased by 1
			timeavg=((timeavg*(count-1))+(start-end))/count;	//Calculating time avergage by taking time as start of this cell - end of last cell
			//printf("%d ",i);
		}
		if (((read2<horizontal_threshold && abs((int)read1-2650)<vertical_threshold)) && on == 1)	//End of cell
		{
			end = i;	//Ending position of cell
			fprintf(output,"%d %d\n",(start+end)/2,(end-start));	//Printing values of location , width
			widthavg=((widthavg*(count-1))+(end-start))/count;	//Calculating average width
			on = 0;
			//printf("end here %d\n",i);
		}
		tail->next=new1;	//Next few commands for implementing first in first out
		tail=tail->next;
		temp=head;
		head->next=head;
		free(new1);	//Deleting the memory allocated to a temporary node
		
	}
	printf("Average Width : %f \nAverage Time : %f \nNumber of cells : %d\n",widthavg,timeavg,count);	//Printing the values of average width,average time and number of cell

	return 0;
}//End of main
