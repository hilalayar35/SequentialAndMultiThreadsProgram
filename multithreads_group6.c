#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

int threads;
int sum[]={0};
double average=0;
double variance[]={0};
double std_dev;
int arr[410000]={0};
void* runner1(void* param1);
void* runner2(void* param2);

int main(int argc,char *argv[])
{
	FILE *file1=fopen(argv[1],"r");
	int status;
	int i=0;
	double time=0;
	clock_t start,end;

	printf("Multi-threaded program launched\n");
	printf("Reading file1.txt\n");

	if(file1==NULL){
		printf("Cannot open the file!");
		exit(0);
	}
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

	threads=atoi(argv[2]);
	printf("%d threads are created.\n",threads);

	pthread_t *threads1 = (pthread_t*) malloc(threads * sizeof(pthread_t));
	pthread_t *threads2 = (pthread_t*) malloc(threads * sizeof(pthread_t));

	if(argc!=3) {
		fprintf(stderr,"usage: a.out <integer value>\n");
		return -1;
	}

	int ids1[threads];
	for(int a=0;a<threads;a++){
		ids1[a] = a;
		pthread_create(&threads1[a],NULL,runner1,&ids1[a]);
	}

	start=clock();

	for(int b=0;b<threads;b++)
		pthread_join(threads1[b],NULL);

	printf("The timer started.\n");

	int total_sum=0;
	for(int g=0;g<threads;g++)
		total_sum+=sum[g];

	average=(double)total_sum/410000;
	
	int ids2[threads];
	for(int i=0;i<threads;i++){
		ids2[i] = i;
		pthread_create(&threads2[i],NULL,runner2,&ids2[i]);
	}

	for(int i=0;i<threads;i++)
		pthread_join(threads2[i],NULL);

	double total_variance=0;
	for(int v=0;v<threads;v++)
		total_variance+=variance[v];
	
	printf("The global average is: %f\n",average);
	
	std_dev=sqrt(total_variance/410000);
	printf("The standard deviation: %f\n",std_dev);

	end=clock();
	time=(double)(end-start)/CLOCKS_PER_SEC;
	
	printf("Calculation completed in %f milliseconds.\n",(time*1000));
	
	return 0;	
}

void* runner1(void* param1)
{
	int thread_part1 = * (int *) param1;
	int j=0;

	double x=(double)410000/threads;
	double result=floor(x);
	int start = thread_part1*result;
	int end = (thread_part1+1)*result;

	if(thread_part1==(threads-1))
		end=410000;
	for(j=start; j<end; j++)
		sum[thread_part1]+=arr[j];

	pthread_exit(0);
}

void* runner2(void* param2)
{
	int thread_part2 = * (int *) param2;
	int c=0;

	double x1=(double)410000/threads;
	double result1=floor(x1);
	int start1 = thread_part2*result1;
	int end1 = (thread_part2+1)*result1;

	if(thread_part2==(threads-1))
		end1=410000;
	for(c=start1; c<end1; c++)
		variance[thread_part2]+=pow((arr[c]-average),2);

	pthread_exit(0);
}

