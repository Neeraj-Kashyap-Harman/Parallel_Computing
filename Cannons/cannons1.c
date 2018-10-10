/*	Name: Neeraj Kashyap
	Program : Cannon's 
*/

#include "mpi.h"
#include <stdio.h>
#define SIZE 16
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
int main(int argc, char *argv[])
{
	int numtasks, rank, size = 0, A, B, source, dest, outbuf, i, tag=1,x_displacement = 0,y_displacement = 0,
	//inbuf[4]={MPI_PROC_NULL,MPI_PROC_NULL,MPI_PROC_NULL,MPI_PROC_NULL,},
	nbrs[4], dims[2]={4,4},periods[2]={1,1}, reorder=0, coords[2],rows = 4 ,cols = 4,cnt=0;
	int a[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15} , b[] = {0,4,8,12,1,5,9,13,2,6,10,14,3,7,11,15} , c[16];
	int ln, rn, un, dn, tmp, multi = 0;
	MPI_Request reqs[2];
	MPI_Status status[2];
	MPI_Comm cartcomm;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Scatter(&a,1,MPI_INT,&A,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(&b,1,MPI_INT,&B,1,MPI_INT,0,MPI_COMM_WORLD);
	
	if (size == SIZE) 
	{
		MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, reorder, &cartcomm);
		MPI_Comm_rank(cartcomm, &rank);
		MPI_Cart_coords(cartcomm, rank, 2, coords);
		
		for(i = 0; i < 4; i++)
		{
			if(i == 0)
			{
			x_displacement = rank/rows;
			y_displacement = rank%cols;
			}
			else
			{
			x_displacement = 1;
			y_displacement = 1;
			}
		
		MPI_Cart_shift(cartcomm, 1, x_displacement, &ln, &rn);
		MPI_Isend(&A, 1, MPI_INT, ln, 0, cartcomm, &reqs[0]);
		MPI_Irecv(&tmp, 1, MPI_INT, rn, 0, cartcomm,&reqs[1]);
		MPI_Waitall(2,reqs,status);
		A = tmp;
		
		int tmp1;
		MPI_Cart_shift(cartcomm, 0, y_displacement, &un, &dn);
		MPI_Isend(&B, 1, MPI_INT, un, 1, cartcomm, &reqs[0]);
		MPI_Irecv(&tmp1, 1, MPI_INT, dn, 1, cartcomm,&reqs[1]);
		MPI_Waitall(2,reqs,status);
		B = tmp1;
		
		multi = multi + (A*B);
		
		}
		//printf("Multiplication = %d\n",multi);
	
		MPI_Gather(&multi, 1, MPI_INT,&c[rank],1,MPI_INT,0,cartcomm);

		if(rank==0)
		for(i=0;i<16;i++)
		{
		printf("%d \t",c[i]);cnt++;
		if(cnt%4==0)printf("\n");
		}
		
		/*MPI_Cart_shift(cartcomm, 0, 1, &nbrs[UP], &nbrs[DOWN]);
		MPI_Cart_shift(cartcomm, 1, 1, &nbrs[LEFT], &nbrs[RIGHT]);
		printf("rank= %d coords= %d %d neighbors(u,d,l,r)= %d %d %d %d\n",
		rank,coords[0],coords[1],nbrs[UP],nbrs[DOWN],nbrs[LEFT],nbrs[RIGHT]);
		outbuf = rank;
		for (i=0; i<4; i++) 
		{
			dest = nbrs[i];
			source = nbrs[i];
			MPI_Isend(&outbuf, 1, MPI_INT, dest, tag, MPI_COMM_WORLD, &reqs[i]);
			MPI_Irecv(&inbuf[i], 1, MPI_INT, source, tag,MPI_COMM_WORLD, &reqs[i+4]);
		}
		MPI_Waitall(8, reqs, stats);
		//printf("rank= %d inbuf(u,d,l,r)= %d %d %d %d\n",rank,inbuf[UP],inbuf[DOWN],
		//inbuf[LEFT],inbuf[RIGHT]); */
	}
	else
	    printf("Must specify %d processors. Terminating.\n",SIZE);
	MPI_Finalize();
}
