#include<stdio.h>
#include<math.h>
#include<mpi.h>

int main (int argc,char **argv)
{
float matrix[9]={1.00,2.00,3.00,5.00,4.00,3.00,6.00,5.00,4.00},vector[3]={4.00,2.00,5.00},matrix_scatter[3]={},vector_scatter;
float pivot_element[3]={},matrix_local[3]={},vector_local;
int size,myrank,i_iteration,j_iteration,k_iteration;

MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD,&size);
MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
//MPI_Status MPI_STATUS_IGNORE;
MPI_Scatter(&matrix,3,MPI_FLOAT,&matrix_scatter,3,MPI_FLOAT,0,MPI_COMM_WORLD);
MPI_Scatter(&vector,1,MPI_FLOAT,&vector_scatter,1,MPI_FLOAT,1,MPI_COMM_WORLD);


			for (i_iteration=0;i_iteration<myrank;i_iteration++)
			{

				MPI_Recv(&matrix_local,3,MPI_FLOAT,i_iteration,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);// for matrix
				MPI_Recv(&vector_local,1,MPI_FLOAT,i_iteration,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);// for vector

				//loop logic
				//logic					
	
				for (k_iteration=0;k_iteration<3;k_iteration++)
				{
					matrix_local[k_iteration]=(matrix_local[k_iteration]/matrix_local[myrank]);
				}				
	
				for (j_iteration=myrank;j_iteration<3;j_iteration++)
					{	
					matrix[j_iteration]-=matrix[j_iteration]*matrix_local[j_iteration];
					printf ("%f",matrix[j_iteration]);
					}

					
				for (k_iteration=myrank+1;k_iteration<size;k_iteration++)
				{
					// send a to k^a th processor
				MPI_Send(matrix,3,MPI_FLOAT,i_iteration,0,MPI_COMM_WORLD);	
				MPI_Send(vector,1,MPI_FLOAT,i_iteration,1,MPI_COMM_WORLD);			
				}
			}		



			MPI_Finalize();
}
