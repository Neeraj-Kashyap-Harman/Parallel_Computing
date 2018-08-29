#include<stdio.h>
#include<mpi.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>

int main (int argc,char **argv)
{
	MPI_Init(&argc,&argv);
	int size,myrank,i,n= 10000000000,number,counter=0;
        float x,y,r=1.00,error;
        float radius_square,power_x_y,local_pi,piwe,sumOfAll;
	
	MPI_Comm_size(MPI_COMM_WORLD,&size);   		// size is declared 
	MPI_Comm_rank(MPI_COMM_WORLD,&myrank); 		// rank is declared	

	number=n/size;
	//printf ("%d",number);
	printf ("\n");		

	srand(time(NULL)); //setting a seed using current time
        
                radius_square=pow(r,2);
                
	for (i=0;i<number;i++)
       		{
                 x= (float) rand()/RAND_MAX;              

         			
		 y= (float) rand()/RAND_MAX;              
		        power_x_y=(pow(x,2)+pow(y,2));
		                
		                if (power_x_y<=radius_square)
		                        {
		                        counter++;
		                        }
		}
		
		local_pi=(4.0*(float)(counter)/number);
                printf ("\n  PI=%f\t%d\n",local_pi,counter);
                MPI_Reduce(&local_pi,&sumOfAll,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);
                
	
	if(myrank==0)
	{
                sumOfAll=sumOfAll/size;
		printf ("\n  PI=%f",sumOfAll);
		printf ("\n");
            
                     error=M_PI-sumOfAll;
       	             printf ("Error=%f \n",error);  
       	}
       	        
       	            
	MPI_Finalize();	

}






















/*
float matrixa[16]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16},vector_matrix[4]={1,2,3,4};
	float temperory[4]={},mult=0.0;
	float recvbuf[4]={};

MPI_Bcast(&vector_matrix,4,MPI_FLOAT,0,MPI_COMM_WORLD);
	MPI_Scatter(&matrixa,4,MPI_FLOAT,&temperory,4,MPI_FLOAT,0,MPI_COMM_WORLD);

	float sum=0.0;

	/*This loop is used to take the matrix elements in the temporary array*/
	/*for (i=0;i<size;i++)
		{
		printf ("\nrank=%d no=%f\n",myrank,temperory[i]);		
		}

	/*multiply the temporary by the vector*/	
	/*	for (i=0;i<4;i++)
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

*/

