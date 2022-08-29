#include <stdio.h>
#include <math.h>
#include <time.h>

int main(int argc,char *argv[])
{
	FILE *file1=fopen(argv[1],"r");
	int arr[410000];
	int i=0,j,sum=0;
	int status;
	double average=0;
	double variance=0;
	double std_dev=0;
	clock_t start,end;
	double time;
	
	printf("Sequential program launched\n");
	printf("Reading file1.txt\n");
	
	if(file1==NULL)
		printf("Cannot open the file!");
	else
	{
		status=fscanf(file1,"%d",&arr[i]);
		
		while(status!=EOF)
		{
			i++;
			status=fscanf(file1,"%d",&arr[i]);
		}
		
		fclose(file1);
	}
	
	printf("Timer started.\n");
	start=clock();
	
	for(j=0;j<410000;j++)
		sum+=arr[j];

	average=(double)sum/410000;
	
	for(i=0;i<410000;i++)
		variance+=pow((arr[i]-average),2);
		
	std_dev=sqrt(variance/410000);
		
	printf("The average is: %f\n",average);
	printf("The standard deviation: %f\n",std_dev);
	
	end=clock();
	
	time=(double)(end-start)/CLOCKS_PER_SEC;
	
	printf("Calculation completed in %f milliseconds.\n",(time*1000.0));
	
	return 0;	
}
