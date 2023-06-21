# parallel-programming
project to get a better view on paralell programming

I'll be taking a look on the effectiveness of the saito-toriwaki algorithm for computing euclidean distances in binary images in the context of sequential and parallel code

I also pretend built a script to plot some statistics about the code

The code is compiled with gcc. Do not forget to add the -fopenmp flag to test the parallel programming algorithm

gcc -O3 -fopenmp -o TDEParallel TDEParallelAlgorithm.c

gcc -O3 TDESequentialAlgorithm.c -o TDESequential
