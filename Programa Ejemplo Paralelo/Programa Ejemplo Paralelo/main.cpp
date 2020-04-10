#include <iostream> 
#include <thread> 
#include <time.h> 
#include <vector>
#include <random>

using namespace std;

void RowColMult(vector<vector<int>> matrixA, vector<vector<int>> matrixB, vector<vector<int>>& matrixC, int rowofA, int colofB)
{
	//rowofA [0 ... matrixA rofs -1]
	//colofB [0 ... matrixB cols -1]
	int result = 0;
	vector<int>fromA;
	vector<int>fromB;
	for (int i = 0; i < matrixB.size(); i++) //los elementos de una fila de la matrizA
	{
		fromA.push_back(matrixA[rowofA][i]);
	}
	for (int i = 0; i < matrixA[0].size(); i++) //los elementos de una calumna de la matrizB
	{
		fromB.push_back(matrixB[i][colofB]);
	}

	for (int i = 0; i < fromA.size(); i++)
	{
		result = result + (fromA[i] * fromB[i]);
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
	cout << endl;
	cout << "colsA: "; cin >> colsA;
	cout << endl;
	cout << "rowB: "; cin >> rowB;
	cout << endl;
	cout << "colsB: "; cin >> colsB;
	cout << endl;

	vector<vector<int>> matrixA(rowA, vector<int>(colsA, 0));
	vector<vector<int>> matrixB(rowB, vector<int>(colsB, 0));
	vector<vector<int>> matrixC(rowA, vector<int>(colsB, 0));

	for (int i = 0; i < rowA; i++)
	{
		for (int j = 0; j < colsA; j++)
		{
			matrixA[i][j] = (rand() % 100) + 1;
		}
	}

	for (int i = 0; i < rowB; i++)
	{
		for (int j = 0; j < colsB; j++)
		{
			matrixB[i][j] = (rand() % 100) + 1;
		}
	}

	printmatrix(matrixA, rowA, colsA);
	cout << endl;
	printmatrix(matrixB, rowB, colsB);
	cout << endl;
	for (int i = 0; i < rowA; i++)
	{
		for (int j = 0; j < colsB; j++)
		{
			matrixC[i][j] = 0;
		}
	}

	vector<thread> threads; //rowA*colsB

	for (int i = 0; i < rowA; i++)
	{
		for (int j = 0; j < colsB; j++)
		{
			threads.push_back(thread(RowColMult, matrixA, matrixB, ref(matrixC), i, j));
		}
	}

	for (int i = 0; i < threads.size(); i++)
	{
		threads[i].join();
	}


	printmatrix(matrixC, rowA, colsB);
	cout << endl;

	return 0;
}
