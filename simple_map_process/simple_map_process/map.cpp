#include<omp.h>
#include <iostream>

using namespace std;

long long * map(long long *A, long long N, long long(*f)(long long i))
{
	omp_set_num_threads(omp_get_max_threads());
	cout << omp_get_max_threads() << endl;
	long long  i = 0;
	
    #pragma omp parallel for
	for (i = 0;i < N;i++)
	{
		A[i] = f(A[i]);
    
		cout << omp_get_num_threads() << endl;

	 }
	return A;

}
long long f(long long i)
{
	return i * i;
}
