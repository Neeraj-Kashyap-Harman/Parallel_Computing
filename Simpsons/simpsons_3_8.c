#include<unistd.h>
#include<stdio.h>
#include<mpi.h>
#include<math.h>

float calculate_the_value(float locala)
	{
	return 	2+sin(2*sqrt(locala)); 
	}

int main (int argc,char **argv)
{
	/*It is for the function 2+sin*2*sqrt(x)*/
	int size,myrank;
	float height,local_a,local_b,starting_point=0,ending_point=1,summation,summation_of_all,final_ans;
		

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&myrank);	
	
        //printf ("Rank:%d\tsize:%d\n",myrank,size);

	/*The height of the function*/
	height=((ending_point-starting_point)/size);

	//printf ("%f",height);
	
	local_a=myrank*height;
	local_b=local_a+height;
	
	
	
	summation=calculate_the_value(local_a)+3*calculate_the_value(((2*local_a)+local_b)/3)+3*calculate_the_value((local_a+(2*local_b))/3)+calculate_the_value(local_b);
	
	summation=((local_b-local_a)/8)*summation ;	

	MPI_Reduce(&summation,&final_ans,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);

	if(myrank==0)
	{

		printf ("\n Final Answer=%f",final_ans);
	}

	//printf ("Rank:%d\tLocal A:%f\tLocal B:%f\n",myrank,local_a,local_b);
		
	MPI_Finalize();	
}
