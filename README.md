# Parallel_Computing
Parallel Computing Codes 

1]Hello World Works Properly
2]Addition of N Numbers (Do odd number of processors ,if condition remaining)
3] Matrix vector multiplication works well
4] Matrix Vector multiplication by file is remainig to code

matrix.txt and vector.txt are the input files.



To compile a file:
mpicc File_Matrix_Multiplcation.c -o File_Matrix_Multiplcation

To run a file:
mpirun -np 4 File_Matrix_Multiplcation
