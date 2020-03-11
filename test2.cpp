#include <iostream>
#include "omp.h"

int main()
{
	omp_set_num_threads(4);
        #pragma omp parallel
	{
             #pragma omp sections
		{
        #pragma omp section
		     printf("section 1 threadid = %d \n", omp_get_thread_num());
        #pragma omp section
		     printf( "section 2 threadid = %d \n",omp_get_thread_num());}

        #pragma omp sections
		{
	#pragma omp section
	            printf("section 3 threadid = %d \n",omp_get_thread_num());
	#pragma omp section
		    printf("section 4 threadid = %d \n",omp_get_thread_num());}
	}
	
	return 0;
}
