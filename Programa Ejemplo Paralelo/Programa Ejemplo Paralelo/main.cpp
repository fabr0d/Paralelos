#include <iostream> 
#include <thread> 
#include <time.h> 
#include <vector>
#include <random>
#include <chrono>
using namespace std;

void RowColMult(vector<vector<int>>& matrixA, vector<vector<int>>& matrixB, vector<vector<int>>& matrixC, int rowofA, int colofB)
{
	int result = 0;
	for (int i = 0; i < matrixB.size(); i++)
	{
		result = result + (matrixA[rowofA][i] * matrixB[i][colofB]);
	}
	matrixC[rowofA][colofB] = result;
}

void printmatrix(vector<vector<int>> matrixA, int rowA, int colsA)
{
	for (int i = 0; i < rowA; i++)
	{
		for (int j = 0; j < colsA; j++)
		{
			cout << matrixA[i][j] << ", ";
		}
		cout << endl;
	}
}

int main()
{
	srand(time(NULL));
	int rowA, colsA, rowB, colsB;
	cout << "rowA: "; cin >> rowA;
	cout << "colsA: "; cin >> colsA;
	cout << "rowB: "; cin >> rowB;
	cout << "colsB: "; cin >> colsB;

	vector<vector<int>> matrixA(rowA, vector<int>(colsA, 0));
	vector<vector<int>> matrixB(rowB, vector<int>(colsB, 0));
	vector<vector<int>> matrixC(rowA, vector<int>(colsB, 0));

	for (int i = 0; i < rowA; i++)
	{
		for (int j = 0; j < colsA; j++)
		{
			matrixA[i][j] = rand() % (100000 - 90000 + 1) + 90000;
		}
	}

	for (int i = 0; i < rowB; i++)
	{
		for (int j = 0; j < colsB; j++)
		{
			matrixB[i][j] = rand() % (100000 - 90000 + 1) + 90000;
		}
	}

	//printmatrix(matrixA, rowA, colsA);
	//cout << endl;
	//printmatrix(matrixB, rowB, colsB);
	//cout << endl;
	for (int i = 0; i < rowA; i++)
	{
		for (int j = 0; j < colsB; j++)
		{
			matrixC[i][j] = 0;
		}
	}

	vector<thread> threads; //rowA*colsB

	auto started = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < rowA; i++)
	{
		for (int j = 0; j < colsB; j++)
		{
			threads.push_back(thread(RowColMult, ref(matrixA), ref(matrixB), ref(matrixC), i, j));
		}
	}

	for (int i = 0; i < threads.size(); i++)
	{
		threads[i].join();
	}

	auto done = std::chrono::high_resolution_clock::now();
	std::cout << "Tiempo en milisegundos en una matriz " << rowA << "x" << colsB << " es : " << std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count() << endl;

	//printmatrix(matrixC, rowA, colsB);
	//cout << endl;

	return 0;
}
