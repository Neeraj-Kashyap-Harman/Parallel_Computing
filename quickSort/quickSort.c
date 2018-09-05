#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>



int main(int argc,char **argv)
{
	int size,myrank,i_iteration,j_iteration,k_iteration,arrayElements[12]={6,19,3,7,1,8,4,6,3,5,11,10},pivot,left[12]={0},right[12]={0},a[12]={},recvArray[12]={};

	int chunkSize,sizeDetermine,temp,recv_count;
	
		
		
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&myrank);



		chunkSize=((int) (sizeof(arrayElements))/sizeof(arrayElements[0]))/size;
		
		MPI_Scatter(&arrayElements,chunkSize,MPI_INT,&a,chunkSize,MPI_INT,0,MPI_COMM_WORLD);
		
		if (myrank==0)
			{
			pivot=a[0];
			}
			
			MPI_Bcast(&pivot,1,MPI_INT,0,MPI_COMM_WORLD);	
					
		for (i_iteration=0,j_iteration=0,k_iteration=0;i_iteration<chunkSize;i_iteration++,j_iteration++,k_iteration++)
			{
				if (a[i_iteration] <= pivot)
					{
					left[j_iteration]=a[i_iteration];
//					printf ("RANK %d LEFT=%d",myrank,left[j_iteration]);
					}
					else{
					right[k_iteration]=a[i_iteration];
//					printf ("RANK %d RIGHT=%d",myrank,right[j_iteration]);
					}	
				printf ("\n");
					
			}

				sizeDetermine=size/2;
					if(myrank<sizeDetermine)
						{
						temp=myrank+sizeDetermine;
						recv_count=k_iteration;						
						MPI_Send(&recv_count,1,MPI_INT,temp,2,MPI_COMM_WORLD);
						MPI_Send(right,recv_count,MPI_INT,temp,0,MPI_COMM_WORLD);
						MPI_Recv(left,j_iteration,MPI_INT,temp,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);	
						
						}
					else 
						{
						temp=myrank-sizeDetermine;
						recv_count=j_iteration;
						MPI_Send(left,recv_count,MPI_INT,temp,1,MPI_COMM_WORLD);
						MPI_Recv(&k_iteration,1,MPI_INT,temp,2,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
						MPI_Recv(right,k_iteration,MPI_INT,temp,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
				
						}	
				
				printf ("RIGHT");		
	for (k_iteration=0;k_iteration<6;k_iteration++)
		{
			printf ("RANK=%d %d \n",myrank,right[k_iteration]);					
		}		
	MPI_Finalize();	
}

