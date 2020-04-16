#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <iostream> 
#include <thread> 
#include <time.h> 
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

void printmatrix(int** matrixA, int rowA)
{
	for (int i = 0; i < rowA; i++)
	{
		for (int j = 0; j < rowA; j++)
		{
			cout << matrixA[i][j] << ", ";
		}
		cout << endl;
	}
}

void resetMatrix(int** A, int n)
{
	for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            A[i][j] = rand() % (9 - 5 + 1) + 5;
        }
    }
}

int main()
{
	srand (time(NULL));
    int n;
    cout << "enter the number of row/cols size=";
    cin>>n;

    int** A = new int* [n];
    for (int i = 0; i < n; ++i)
        A[i] = new int[n];

    int** B = new int* [n];
    for (int i = 0; i < n; ++i)
        B[i] = new int[n];
    
    int** C = new int* [n];
    for (int i = 0; i < n; ++i)
        C[i] = new int[n];

	double resultado = 0;
	for (int i = 0; i < 5; i++)
	{
		resetMatrix(A,n);
		resetMatrix(B,n);
		auto started = std::chrono::high_resolution_clock::now();
		for (int k = 0; k < n; k += 6)
		{
			for (int j = 0; j < n; j += 6)
			{
				for (int i = 0; i < n; ++i)
				{
					for (int jj = j; jj < min(j + 6, n); ++jj)
					{
						for (int kk = k; kk < min(k + 6, n); ++kk)
						{
							C[i][jj] += A[i][kk] * B[kk][jj];
						}
					}
				}
			}
		}
		auto done = chrono::high_resolution_clock::now();
		int result = chrono::duration_cast<chrono::milliseconds>(done - started).count() ;
		cout << "Tiempo en milisegundos en : "<< result << endl;
		resultado = resultado + result;
	}
	cout<<"Tiempo Promedio: "<< resultado/5 <<endl;
}