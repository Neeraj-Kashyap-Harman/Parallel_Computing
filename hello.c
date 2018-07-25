#include<stdio.h>
#include<mpi.h>
#include<unistd.h>

int main(int argc,char **argv)
{
	int size,myrank;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&myrank);	
	sleep(myrank); 
	printf ("Rank:%d \t Size:%d\n",myrank,size);
	MPI_Finalize();
}

