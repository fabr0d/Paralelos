#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <time.h>

using namespace std;

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
	int RC;
	cout << "enter the number of row/cols size=";
	cin >> RC;

	int** matrixA = new int* [RC];
	for (int i = 0; i < RC; ++i)
		matrixA[i] = new int[RC];

	int** matrixB = new int* [RC];
	for (int i = 0; i < RC; ++i)
		matrixB[i] = new int[RC];

	int** matrixMult = new int* [RC];
	for (int i = 0; i < RC; ++i)
		matrixMult[i] = new int[RC];

    double resultado = 0;
	for (int i = 0; i < 5; i++)
	{
		resetMatrix(matrixA,RC);
		resetMatrix(matrixB,RC);
		auto started = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < RC; i++)
        {
            for (int j = 0; j < RC; j++)
            {
                matrixMult[i][j] = 0;
                for (int k = 0; k < RC; k++)
                {
                    matrixMult[i][j] += matrixA[i][k] * matrixB[k][j];
                }
            }
        }
		auto done = chrono::high_resolution_clock::now();
		int result = chrono::duration_cast<chrono::milliseconds>(done - started).count() ;
		cout << "Tiempo en milisegundos en : "<< result << endl;
		resultado = resultado + result;
	}
    cout<<"Tiempo Promedio: "<< resultado/5 <<endl;
	return 0;
}
