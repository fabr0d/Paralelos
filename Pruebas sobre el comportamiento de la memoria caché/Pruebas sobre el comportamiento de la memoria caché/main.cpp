/*
Pruebas sobre el comportamiento de la memoria caché
El alumno debe realizar un informe en formato artículo(en Latex) donde la implementación y los resultados de la ejecución para los siguientes problemas :

Implementar en C / C++ la multiplicación de matrices clásica, la versión de tres bucles anidados y evaluar su desempeño considerando diferentes tamaños de matriz.
Implementar la version por bloques(investigar en internet), seis bloques anidados, evaluar su desempeño y compararlo con la multiplicación de matrices clásica.

Ejecutar ambos algoritmos paso a paso, y analisar el movimiento de datos entre la memoria principal y la memoria cache.Hacer una evaluación de acuerdo a la complejidad algoritmica.
Ejecutar ambos algoritmos utilizando las herramientas valgrind y kcachegrind para obtener una evaluación mas precisa de su desempeño en términos de cache misses.

*/


//la multiplicación de matrices clásica, 
/*/
#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <time.h>

using namespace std;

int main()
{
	int rows, cols;

	cout << "enter the number of row=";
	cin >> rows;
	cout << "enter the number of column=";
	cin >> cols;

	int** matrixA = new int* [rows];
	for (int i = 0; i < rows; ++i)
		matrixA[i] = new int[cols];

	int** matrixB = new int* [rows];
	for (int i = 0; i < rows; ++i)
		matrixB[i] = new int[cols];

	int** matrixMult = new int* [rows];
	for (int i = 0; i < rows; ++i)
		matrixMult[i] = new int[cols];

	
	cout << "enter the first matrix element=\n";
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			matrixA[i][j] = rand() % (500 - 250 + 1) + 250;
		}
	}
	cout << "enter the second matrix element=\n";
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			matrixB[i][j] = rand() % (500 - 250 + 1) + 250;
		}
	}
	cout << "multiply of the matrix=\n";
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			matrixMult[i][j] = 0;
			for (int k = 0; k < cols; k++)
			{
				matrixMult[i][j] += matrixA[i][k] * matrixB[k][j];
			}
		}
	}
	//for printing result    
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << matrixMult[i][j] << " ";
		}
		cout << "\n";
	}
	return 0;
}
*/
//la version por bloques

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

int main()
{
    int n;
    int numreps = 5;
    cout << "Please enter matrix dimension n : " << endl;
    cin>>n;
    // allocate memory for the matrices

    ///////////////////// Matrix A //////////////////////////

    int** A = new int* [n];
    for (int i = 0; i < n; ++i)
        A[i] = new int[n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            A[i][j] = rand() % (100 - 1 + 1) + 1;
        }
    }
	//printmatrix(A, n);
    ///////////////////// Matrix B //////////////////////////

    int** B = new int* [n];
    for (int i = 0; i < n; ++i)
        B[i] = new int[n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            B[i][j] = rand() % (100 - 1 + 1) + 1;
        }
    }
	//printmatrix(B, n);
    ///////////////////// Matrix C //////////////////////////
    int** C = new int* [n];
    for (int i = 0; i < n; ++i)
        C[i] = new int[n];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = 0;
        }
    }
	auto started = std::chrono::high_resolution_clock::now();
	for (int k = 0; k < n; k += 6)
		for (int j = 0; j < n; j += 6)
			for (int i = 0; i < n; ++i)
				for (int jj = j; jj < min(j + 6, n); ++jj)
					for (int kk = k; kk < min(k + 6, n); ++kk)
						C[i][jj] += A[i][kk] * B[kk][jj];
	auto done = std::chrono::high_resolution_clock::now();
	std::cout << "Tiempo en milisegundos en : "<< std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count() << endl;

	//printmatrix(C, n);
}