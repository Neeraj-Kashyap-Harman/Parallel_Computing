#include<unistd.h>
#include<stdio.h>
#include<mpi.h>
#include<math.h>

/*
float sumOfAll(float x[],int n)				
{
		float sum;
		int j_iteration;
		/*fa=2+sin(2*sqrt(xa)); 
		fb=2+sin(2*sqrt(xb)); 
		sum=fa+fb;
		*/
/*			for (j_iteration=2;j_iteration<n-1;j_iteration++)
				{
					if (j_iteration%3==0)
					{
						sum+=2*(2+sin(2*sqrt(x[j_iteration])));	
						printf ("\n Sum=%f",sum);								
					}
						else
						sum+=3*(2+sin(2*sqrt(x[j_iteration])));			
				}
					
		return sum;
}
*/		

 
// Given function to be integrated
float func( float x)
{
    return (2+sin(2*sqrt(x)));
}
 
// Function to perform calculations
float calculate(float starting_point, float ending_point,
                int n )
{
	float total;

   float height=((ending_point-starting_point)/n);
    float sum = func(starting_point) + func(ending_point);
 
    // Calculates value till integral limit
    for (int i = 1 ; i < n ; i++)
    {
        if (i % 3 == 0)
            sum = sum + 2 * func( starting_point+ i * height);
        else
            sum = sum + 3 * func(starting_point + i * height);
    }
		
    return sum;

	
}




int main (int argc,char **argv)
{
	/*It is for the function 2+sin*2*sqrt(x)*/
		int size,myrank,no_of_intervals=21,i_iteration;
	float height,xa,xb,fa,fb,x[50],sum1,local_a,local_b,starting_point=0,ending_point=1,summation,summation_of_all,final_ans,sum;
	float total;	

		MPI_Init(&argc,&argv);
		MPI_Comm_size(MPI_COMM_WORLD,&size);
		MPI_Comm_rank(MPI_COMM_WORLD,&myrank);	
	
        //printf ("Rank:%d\tsize:%d\n",myrank,size);

	/*The height of the function*/
	
 	 float integral_res = calculate(starting_point, ending_point,
                                   no_of_intervals);
 		total=( 3 * height / 8 ) * integral_res ;
		//printf ("\n Final Answer=%f",integral_res);
			MPI_Reduce(&total,&final_ans,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);

	if(myrank==0)
	{

		printf ("\n Final Answer=%f",final_ans);
	}

	MPI_Finalize();	
}





/*	summation=calculate_the_value(local_a)+3*calculate_the_value(((2*local_a)+local_b)/3)+3*calculate_the_value((local_a+(2*local_b))/3)+calculate_the_value(local_b);
	
	summation=((local_b-local_a)/8)*summation;	

	MPI_Reduce(&summation,&final_ans,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);

	if(myrank==0)
	{

		printf ("\n Final Answer=%f",final_ans);
	}

	//printf ("Rank:%d\tLocal A:%f\tLocal B:%f\n",myrank,local_a,local_b);
*/	
