#include <iostream>
#include <random>
#include <chrono>
#include <vector>
using namespace std;

vector<vector<int>> A;
vector<int> x(20000), y(20000);

int main()
{
    for (int i = 0; i < 20000; i++) {
        vector<int> v1;
        for (int j = 0; j < 20000; j++) {
            v1.push_back(0);
        }
        A.push_back(v1);
    }

    for (int i = 0; i < 20000; i++)
    {
        for (int j = 0; j < 20000; j++)
        {
            A[i][j] = rand() % 100;
        }
    }
    for (int j = 0; j < 20000; j++)
    {
        x[j] = rand() % 100;
    }
    for (int j = 0; j < 20000; j++)
    {
        y[j] = 0;
    }
    //---------------------------------------

    auto started = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 20000; i++)
    {
        for (int j = 0; j < 20000; j++)
        {
            y[i] += A[i][j] * x[j];
        }
    }

    auto done = std::chrono::high_resolution_clock::now();

    std::cout <<"Tiempo en milisegundos del Loop 1:" <<std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count() << endl;
    //------------------------------------------


    for (int j = 0; j < 20000; j++)
    {
        y[j] = 0;
    }

    auto started1 = std::chrono::high_resolution_clock::now();

    for (int j = 0; j < 20000; j++)
    {
        for (int i = 0; i < 20000; i++)
        {
            y[j] += A[i][j] * x[j];
        }
    }

    auto done1 = std::chrono::high_resolution_clock::now();

    std::cout << "Tiempo en milisegundos del Loop 2:" << std::chrono::duration_cast<std::chrono::milliseconds>(done1 - started1).count() << endl;

}
