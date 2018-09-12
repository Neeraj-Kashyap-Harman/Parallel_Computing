#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>



int main(int argc,char **argv)
{
	int size,myrank,i_iteration,j_iteration,k_iteration,arrayElements[12]={6,19,3,7,1,8,4,6,3,5,11,10},pivot,left[12]={0},right[12]={0},a[12]={},recvArray[12]={};
int ll1,recv_countll1,ll,right_count;

	int chunkSize,sizeDetermine,temp,recv_count,mergeArray[12]={0},left_list1[]={0,0,0,0,0,0,0,0,0,0},right_list1[]={0,0,0,0,0,0,0,0,0,0},right_list_count,left_list_count,left_list_count1,right_list_count1;
		
		
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&myrank);



		chunkSize=(12/size);
		
		MPI_Scatter(&arrayElements,chunkSize,MPI_INT,&a,chunkSize,MPI_INT,0,MPI_COMM_WORLD);
		
		if (myrank==0)
			{
			pivot=a[0];
			}
			
			MPI_Bcast(&pivot,1,MPI_INT,0,MPI_COMM_WORLD);	
					j_iteration=k_iteration=0;

		for (i_iteration=0;i_iteration<chunkSize;i_iteration++)
			{
				if (a[i_iteration] <= pivot)
					{
					left[j_iteration++]=a[i_iteration];
//					printf ("RANK %d LEFT=%d",myrank,left[j_iteration]);
					}
					else{
					right[k_iteration++]=a[i_iteration];
//					printf ("RANK %d RIGHT=%d",myrank,right[j_iteration]);
					}	
				
				printf ("\n");	
			}
//printf ("LEFT_ITERATION_COUNT=%d,RIGHT_ITERATION_COUNT=%d \n",j_iteration,k_iteration);	

/*

if(rank<size/2)
{

tmp=rank+(size/2);
rcount_rl=r;

MPI_Send(&rcount_rl, 1,MPI_INT,tmp,1, MPI_COMM_WORLD);
MPI_Send(&rl, r, MPI_INT, tmp, 2, MPI_COMM_WORLD);

MPI_Recv(&rcount_ll, 1, MPI_INT, tmp, 4, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
MPI_Recv(&ll1, rcount_ll, MPI_INT, tmp, 3, MPI_COMM_WORLD,MPI_STATUS_IGNORE);

}

else
{
tmp=rank-(size/2);
  rcount_ll1=l;

MPI_Send(&rcount_ll1, 1, MPI_INT, tmp, 4, MPI_COMM_WORLD);
MPI_Recv(&rcount_rl1, 1, MPI_INT, tmp, 1, MPI_COMM_WORLD,MPI_STATUS_IGNORE);

MPI_Send(&ll, l, MPI_INT, tmp, 3, MPI_COMM_WORLD);
MPI_Recv(&rl1, rcount_rl1, MPI_INT, tmp, 2, MPI_COMM_WORLD,MPI_STATUS_IGNORE);

}
		
*/
				if (myrank<(size/2))
				{
				temp=myrank+(size/2);
				right_list_count=k_iteration;
			MPI_Send(&right_list_count,1,MPI_INT,temp,1,MPI_COMM_WORLD);
			MPI_Send(&right,k_iteration,MPI_INT,temp,2,MPI_COMM_WORLD);
			MPI_Recv(&left_list_count,1,MPI_INT,temp,4,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			MPI_Recv(&left_list1,left_list_count,MPI_INT,temp,3,MPI_COMM_WORLD,MPI_STATUS_IGNORE);				
				}
					else
						{
				temp=myrank-(size/2);
				left_list_count1=j_iteration;
				MPI_Send(&left_list_count1,1,MPI_INT,temp,4,MPI_COMM_WORLD);
				MPI_Recv(&right_list_count1,1,MPI_INT,temp,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
				MPI_Send(&left,j_iteration,MPI_INT,temp,3,MPI_COMM_WORLD);
				MPI_Recv(&right_list1,right_list_count1,MPI_INT,temp,2,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
						}		
	


					/*sizeDetermine=size/2;
					if(myrank<sizeDetermine)
						{
						temp=myrank+sizeDetermine;
						recv_count=k_iteration;						
				
						//MPI_Send(&recv_count,1,MPI_INT,temp,1,MPI_COMM_WORLD);
						//MPI_Send(&right,k_iteration,)						
						
						MPI_Send(&k_iteration,1,MPI_INT,temp,2,MPI_COMM_WORLD);
						MPI_Send(right,k_iteration,MPI_INT,temp,0,MPI_COMM_WORLD);
						MPI_Recv(left,j_iteration,MPI_INT,temp,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);	
						MPI_Recv();
						}
					else 
						{
						temp=myrank-sizeDetermine;
						recv_count=j_iteration;
						MPI_Send(left,j_iteration,MPI_INT,temp,1,MPI_COMM_WORLD);
						MPI_Recv(&k_iteration,1,MPI_INT,temp,2,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
						MPI_Recv(right,k_iteration,MPI_INT,temp,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
						MPI_Send()				
						}
					*/	
				

	if(myrank<(size/2))
		{	
		    printf ("\nLEFT\n");		
			
			for (i_iteration=0;i_iteration<left_list_count;i_iteration++)
				left[j_iteration++]=left_list1[i_iteration];
			
				for (i_iteration=0;i_iteration<j_iteration;i_iteration++)
						printf ("RANK=%d %d \n",myrank,left[i_iteration]);					
		}	
				
		else
			{	
				printf ("\nRIGHT\n");		
				
			for (i_iteration=0;i_iteration<right_list_count1;i_iteration++)
					right[k_iteration++]=right_list1[i_iteration];
	
				for (i_iteration=0;i_iteration<k_iteration;i_iteration++)
					printf ("RANK=%d %d \n",myrank,right[i_iteration]);					
			}
	MPI_Finalize();	
}

