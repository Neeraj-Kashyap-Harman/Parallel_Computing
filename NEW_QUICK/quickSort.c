#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int firstPass(int right_array_new[],int left_array_new[],int j_iteration,int k_iteration,int myrank,int size,int chunkSize);

int main(int argc,char **argv)
{
	int size,myrank,i_iteration,j_iteration,k_iteration,arrayElements[12]={6,19,3,7,1,8,4,6,3,5,11,10},pivot,left[12]={0},right[12]={0},a[12]={},recvArray[12]={};
int ll1,recv_countll1,ll,right_count;

	int chunkSize,sizeDetermine,temp,recv_count,mergeArray[12]={0},left_list1[]={0,0,0,0,0,0,0,0,0,0},right_list1[]={0,0,0,0,0,0,0,0,0,0},right_list_count,left_list_count,left_list_count1,right_list_count1;
		
	int left_array_new[12]={0},right_array_new[12]={0},left_iteration,right_iteration;	
	int new_k;
			
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
	


				

	if(myrank<(size/2))
		{	
		//    printf ("\nLEFT\n");		
			
			for (i_iteration=0;i_iteration<left_list_count;i_iteration++)
				left[j_iteration++]=left_list1[i_iteration];

				for (i_iteration=0;i_iteration<j_iteration;i_iteration++)
					//printf ("RANK=%d %d \n",myrank,left[i_iteration]);					
	
				/*Copy the left elements in new right_new_array*/
				for (i_iteration=0;i_iteration<j_iteration;i_iteration++)
			             {
			                left_array_new[i_iteration]=left[i_iteration];
			//		printf ("%d<==\n",left_array_new[i_iteration]);			
				     }
                         //printf ("==>%d",left_array_new[i_iteration]);
			//MPI_Gather(left,1,MPI_INT,left_array_new,1,MPI_INT,0,MPI_COMM_WORLD);	
			//	printf ("J=%d",j_iteration); No. of J elements, depends on rank
		}	
				
		else
			{	
			//printf ("\nRIGHT\n");		
			for (i_iteration=0;i_iteration<right_list_count1;i_iteration++)
					right[k_iteration++]=right_list1[i_iteration];

	
				for (i_iteration=0;i_iteration<k_iteration;i_iteration++)
					//printf ("RANK=%d %d \n",myrank,right[i_iteration]);					
				
				
				/*Copy the right elements in new right_new_array*/
				for (i_iteration=0;i_iteration<k_iteration;i_iteration++)
			             {
			                right_array_new[i_iteration]=right[i_iteration];
			//		printf ("==>%d\n",right_array_new[i_iteration]);			
				     }	
				//printf ("K=%d",k_iteration);	 No of K elements,depends on rank
			}
					
			 firstPass(right_array_new,left_array_new,j_iteration,k_iteration,myrank,size,chunkSize);	
			
	MPI_Finalize();	
}


int firstPass(int right_array_new[],int left_array_new[],int j_iteration,int k_iteration,int myrank,int size,int chunkSize)
{
	int i,pivot_left,pivot_right,ileft_iteration,jright_iteration,aleft[12]={0},bright[12]={0};
	int left_less_pivot[12]={0},left_greater_pivot[12]={0},right_less_pivot[12]={0},right_greater_pivot[12]={0};
	
	int counter_left=0,counter_right=0,counter;
	int j_left_iteration,k_left_iteration,j_right_iteration,k_right_iteration;
	int new_k,new_j,sss[12]={0},sks[12]={0},i_iteration,kk_iteration,kr_iteration,temp1,temp2;
	int recv_counter,recv_counter1;
	
		if(myrank<(size/2))
		{
				for (i=0;i<j_iteration;i++)
				{
				counter_left++;
				//printf ("%d<==\n",left_array_new[i]);					
				}
		}
		else
		{
				for (i=0;i<k_iteration;i++)
				{
				counter_right++;
				//printf ("==>%d\n",right_array_new[i]);					
				}
		}


	//MPI_Scatter(&left_array_new,counter_left,MPI_INT,&aleft,counter_left,MPI_INT,0,MPI_COMM_WORLD);
			
				if (myrank==0)
				{		
					pivot_left=left_array_new[0];
					printf ("LEFT=>%d",pivot_left);
				}
				MPI_Bcast(&pivot_left,1,MPI_INT,0,MPI_COMM_WORLD);	
			
				j_left_iteration=k_left_iteration=0;

				for (ileft_iteration=0;ileft_iteration<counter_left;ileft_iteration++)
				{
				//printf ("<>%d\n",left_array_new[ileft_iteration]); 
					if (left_array_new[ileft_iteration] <= pivot_left)
					{
//					left_less_pivot[j_left_iteration++]=aleft[ileft_iteration];
					left_less_pivot[j_left_iteration++]=left_array_new[ileft_iteration];
					printf ("\n RANK %d LEFT 1=%d",myrank,left_less_pivot[ileft_iteration]);
					}
					else
					{
					left_greater_pivot[k_left_iteration++]=left_array_new[ileft_iteration];
					printf ("\n RANK %d LEFT 2=%d",myrank,left_greater_pivot[ileft_iteration]);
					}	
				}
	
	
				 
				printf ("\n");	
				

				if (myrank==2)
					{		pivot_right=right_array_new[0];
							printf ("\n RIGHT=>%d",pivot_right);
					}
				MPI_Bcast(&pivot_right,1,MPI_INT,2,MPI_COMM_WORLD);
				j_right_iteration=k_right_iteration=0;

			for (jright_iteration=0;jright_iteration<counter_right;jright_iteration++)
				{
				if (right_array_new[jright_iteration] <= pivot_right)
					{
					right_less_pivot[j_right_iteration++]=right_array_new[jright_iteration];
					printf ("\n RANK %d RIGHT 1=%d",myrank,right_less_pivot[jright_iteration]);
					}
					else
					{
					right_greater_pivot[k_right_iteration++]=right_array_new[jright_iteration];
					printf ("\n RANK %d RIGHT 2=%d",myrank,right_greater_pivot[jright_iteration]);
					}	
				}
				printf ("\n");	
			
			
		
}


