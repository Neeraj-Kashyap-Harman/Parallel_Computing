#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

int main(int argc, char ** argv)
{
        int A[] = {5, 9, 2, 7, 1, 8, 4, 6, 3, 5, 11, 10};
        int final[4][16], num[4];
        int chunk = sizeof(A)/sizeof(int);
        int i, j, k, pivot, size, rank, new[chunk], temp, n;
        MPI_Init(&argc, &argv);
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        chunk /= size;
        int l[chunk], r[chunk], a[chunk], nw[chunk];
        MPI_Scatter(&A, chunk, MPI_INT, &a, chunk, MPI_INT, 0, MPI_COMM_WORLD);
        pivot = A[0];
        MPI_Bcast(&pivot, 1, MPI_INT, 0, MPI_COMM_WORLD);
        for (i = 0, j = 0, k = 0; i < chunk; i++)
        {
                if (a[i] <= pivot)
                {
                    l[j] = a[i];
                    j++;
                }
                else
                {
                    r[k] = a[i];
                    k++;
                }
        }
        if(rank >= (size/2))
        {
                temp = (rank-(size/2));
                MPI_Send(&j, 1, MPI_INT, temp, 0, MPI_COMM_WORLD);
                MPI_Send(&l, j, MPI_INT, temp, 0, MPI_COMM_WORLD);
                MPI_Recv(&n, 1, MPI_INT, temp, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Recv(&nw, n, MPI_INT, temp, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                for(i = 0; i < k; i++)
                        new[i] = r[i];
                for(j = 0; j < n; i++, j++)
                        new[i] = nw[j];
                n=n+k;
        }
        else
        {
                temp = (rank+(size/2));
                MPI_Recv(&n, 1, MPI_INT, temp, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Recv(&nw, n, MPI_INT, temp, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Send(&k, 1, MPI_INT, temp, 0, MPI_COMM_WORLD);
                MPI_Send(&r, k, MPI_INT, temp, 0, MPI_COMM_WORLD);
                for(i = 0; i < j; i++)
                        new[i] = l[i];
                for(k = 0; k < n; i++, k++)
                        new[i] = nw[k];
                n=n+j;
        }
        if(rank == 0 || rank == 2)
        {
                pivot = new[0];
                temp = rank + 1;
                MPI_Send(&pivot, 1, MPI_INT, temp, 0, MPI_COMM_WORLD);
        }
        else
        {
                temp = rank - 1;
                MPI_Recv(&pivot, 1, MPI_INT, temp, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        for (i = 0, j = 0, k = 0; i < n; i++)
        {
                if (new[i] <= pivot)
                {
                    l[j] = new[i];
                    j++;
                }
                else
                {
                    r[k] = new[i];
                    k++;
                }
        }
        if(rank%2)
            {
                temp = rank - 1;
                MPI_Send(&j, 1, MPI_INT, temp, 0, MPI_COMM_WORLD);
                MPI_Send(&l, j, MPI_INT, temp, 0, MPI_COMM_WORLD);
                MPI_Recv(&n, 1, MPI_INT, temp, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Recv(&nw, n, MPI_INT, temp, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                for(i = 0; i < k; i++)
                        new[i] = r[i];
                for(j = 0; j < n; i++, j++)
                        new[i] = nw[j];
                n=n+k;
        }
        else
        {
                temp = rank + 1;
                MPI_Recv(&n, 1, MPI_INT, temp, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Recv(&nw, n, MPI_INT, temp, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Send(&k, 1, MPI_INT, temp, 0, MPI_COMM_WORLD);
                MPI_Send(&r, k, MPI_INT, temp, 0, MPI_COMM_WORLD);
                for(i = 0; i < j; i++)
                        new[i] = l[i];
                for(k = 0; k < n; i++, k++)
                        new[i] = nw[k];
                n=n+j;
        }
        for (int i = 0; i < n-1; ++i)
        {
                for (int j = 0; j < n-1; ++j)
                {
                        if (new[j] > new[j+1])
                        {
                                temp = new[j];
                                new[j] = new[j+1];
                                new[j+1] = temp;
                        }
                }
        }
        MPI_Gather(&n, 1, MPI_INT,&num, 1, MPI_INT, 0, MPI_COMM_WORLD);
        //MPI_Gather(&new, n, MPI_INT,&final[rank], num[rank], MPI_INT, 0, MPI_COMM_WORLD);
        if (rank)
        {
                MPI_Send(&new, n, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
        if (!rank)
        {
                for (int i = 0; i < num[0]; ++i)
                        final[0][i] = new[i];
                for(i = 1; i < 4; i++)
                        MPI_Recv(&final[i], num[i], MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                for (int i = 0; i < 4; ++i)
                        for (int j = 0; j < num[i]; ++j)
                                printf("%d\n", final[i][j]);
        }
        //for(i = 0; i < n; i++)
                //printf("rank: %d\tn: %d\n", rank, new[i]);
        printf("\n");
        MPI_Finalize();
}
                                                                                                                                                84,1-8        42%


