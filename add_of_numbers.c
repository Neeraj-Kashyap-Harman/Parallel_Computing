#include<stdio.h>
#include<mpi.h>
#include<unistd.h>

int main(int argc,char **argv)
{
	int size,myrank,a=0,sumOfAll=0,sum=0;
	int chunkSize,noOfElements=100,startSize,i,endSize;
	//MPI_Status status_of_first,status_of_second,status_of_third,status_of_fourth,MPI_Status_IGNORE;
		
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&myrank);	
	chunkSize=noOfElements/size;
	//	sleep(myrank); 	
	startSize=chunkSize*myrank;
	endSize=startSize+chunkSize;

		
				if (myrank==size-1)
			{
				endSize=noOfElements;				
			}	
					
	for (i=startSize+1;i<=endSize;i++)
		{
		
			sum=sum+i;
		}

	printf ("ChunkSize=%d startSize=%d endSize=%d local_sum=%d \n",chunkSize,startSize,endSize,sum);

		
	if (myrank==0)
		{
					sumOfAll=sumOfAll+sum;
					for (i=1;i<size;i++)
					{		
						
						MPI_Recv(&sum,1,MPI_INT,i,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);		
						sumOfAll=sumOfAll+sum;
							
					}
						printf ("\n SUM_ALL:%d",sumOfAll);							
		}				

	if(myrank>=1)
		{	
					MPI_Send(&sum,1,MPI_INT,0,1,MPI_COMM_WORLD);
								
		}	
				
					

	MPI_Finalize();					
}

