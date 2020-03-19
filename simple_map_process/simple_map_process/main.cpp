#include<omp.h>
#include <iostream>
#include "map.h"
using namespace std;
int main()
{
	long long a[20];
	for (int i = 1;i < 20;i++)
	{
		a[i] = i;
	}
	long long*B = map(a, 20, f);
	for (int i = 1;i < 20;i++)
		cout << B[i] << endl;
	system("pause");
	return 0;
}