#include<unistd.h>
#include<stdio.h>
#include<mpi.h>

int main (int argc,char **argv)
{
	
	MPI_Init(&argc,&argv);
	FILE *fpmatrix,*fpvector;	
	
	int size,myrank,i,matrix_input,vector_input;
	float temperory[4]={},mult=0.0,matrixa[16]={},vectorb[4]={};
	float recvbuf[4]={};
	
	MPI_Comm_size(MPI_COMM_WORLD,&size);   		// size is declared 
	MPI_Comm_rank(MPI_COMM_WORLD,&myrank); 		// rank is declared	
	
	if (myrank==0)
		{
		
				fpmatrix=fopen("matrix.txt","r");
				fpvector=fopen("vector.txt","r");

				fscanf (fpmatrix,"%d",&matrix_input);	
				fscanf (fpvector,"%d",&vector_input);
			
					int a=0,b=0;	

						printf ("\n Matrix A \n");
				while(!feof(fpmatrix) && a<matrix_input)
				{
					fscanf (fpmatrix,"%f",&matrixa[a]);
					a++;				
				}
	
				printf ("\n Vector \n");
				while(!feof(fpvector) && b<matrix_input)
				{
					fscanf (fpvector,"%f",&vectorb[b]);
					b++;				
				}

			printf ("\n%d\t",matrix_input);
			printf ("%d\n",vector_input);
	
			float sum=0.0;




		}
	

	fcloseall();
	MPI_Finalize();	
}
/*

int size,myrank,i;
	float matrixa[16]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16},vector_matrix[4]={1,2,3,4};
	float temperory[4]={},mult=0.0;
	float recvbuf[4]={};
	MPI_Comm_size(MPI_COMM_WORLD,&size);   		// size is declared 
	MPI_Comm_rank(MPI_COMM_WORLD,&myrank); 		// rank is declared	
	
	MPI_Bcast(&vector_matrix,4,MPI_FLOAT,0,MPI_COMM_WORLD);
	MPI_Scatter(&matrixa,4,MPI_FLOAT,&temperory,4,MPI_FLOAT,0,MPI_COMM_WORLD);

	float sum=0.0;

	/*This loop is used to take the matrix elements in the temporary array*/
/*	for (i=0;i<size;i++)
		{
		printf ("\nrank=%d no=%f\n",myrank,temperory[i]);		
		}

	/*multiply the temporary by the vector*/	
/*		for (i=0;i<4;i++)
		{
			sum+=temperory[i]*vector_matrix[i];
		//		printf ("\n%f\n",sum);
		}
		//printf ("\nT_SUM=%f\n",sum);
	
		MPI_Gather(&sum,1,MPI_FLOAT,&recvbuf,1,MPI_FLOAT,0,MPI_COMM_WORLD);

		/*The Result we got by using MPI_Gather*/
/*
		if (myrank==0)
		{		
			for (i=0;i<4;i++)
				{
				printf ("\nThe Result of the Matrix vector Multiplication is:\n");
				printf ("%f\n",recvbuf[i]);
				}
		}
	fcloseall();
	MPI_Finalize();	*/
