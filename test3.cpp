#include "omp.h"
#include "iostream"
#define ADD_COUNT 10000
int g;
int i;
int main()
{
	omp_set_num_threads(4);
	printf("Masterthread start \n ")
	#pragma omp parallel for
		for(i=0;i<ADD_COUNT;i++)
		{
		       	sleep(1); 
                   
			g=g+1;        
	      	}
	printf("g=%d\n",g);
	printf("Expected g= %d\n",ADD_COUNT);
	printf("Masterthread finish \n");
	return 0;
}


