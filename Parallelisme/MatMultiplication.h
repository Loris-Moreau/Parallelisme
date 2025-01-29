#pragma once

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;
using namespace std::chrono;

// Function to print a matrix
inline void printMatrix(const vector<vector<int>> &matrix)
{
    for (const auto &row : matrix)
    {
        for (int val : row)
        {
            cout << val << " ";
        }
        cout << '\n';
    }
}

// Sequential version: Matrix multiplication
inline vector<vector<int>> sequentialMultiply(const vector<vector<int>> &A, const vector<vector<int>> &B)
{
    int rows = (int)A.size();
    int cols = (int)B[0].size();
    int inner = (int)B.size();
    vector<vector<int>> P(rows, vector<int>(cols, 0));

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            for (int k = 0; k < inner; ++k)
            {
                P[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return P;
}

// Parallel by-value version: Each value P[i][j] computed by a thread
inline void computeElement(const vector<vector<int>> &A, const vector<vector<int>> &B, vector<vector<int>> &P, int i, int j) {
    int inner = (int)B.size();
    P[i][j] = 0;
    for (int k = 0; k < inner; ++k)
    {
        P[i][j] += A[i][k] * B[k][j];
    }
}

inline vector<vector<int>> parallelMultiply(const vector<vector<int>> &A, const vector<vector<int>> &B)
{
    int rows = (int)A.size();
    int cols = (int)B.size();
    vector<vector<int>> P(rows, vector<int>(cols, 0));
    vector<thread> threads;

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            // Launch a thread for each element P[i][j]
            threads.emplace_back(computeElement, cref(A), cref(B), ref(P), i, j);
        }
    }

    // Join all threads
    for (auto &t : threads)
    {
        t.join();
    }

    return P;
}

inline void MatMultiplication( vector<vector<int>> A, vector<vector<int>> B)
{
    cout << "Matrix A :" << '\n';
    printMatrix(A);

    cout << "Matrix B :" << '\n';
    printMatrix(B);

    auto startClock = high_resolution_clock::now();
    
    // Sequential multiplication
    cout << '\n' << "Sequential Matrix Multiplication : " << '\n';
    vector<vector<int>> P1 = sequentialMultiply(A, B);
    printMatrix(P1);
    
    auto endClock = high_resolution_clock::now();
    cout << '\n' << "Sequential Time taken : " << duration_cast<microseconds>(endClock - startClock).count() << " microseconds" << '\n';

    cout << '\n' << " ////////// " << '\n';
    
    startClock = high_resolution_clock::now();
    
    // Parallel by-value multiplication
    cout << '\n' << "Parallel Matrix Multiplication:" << '\n';
    vector<vector<int>> P2 = parallelMultiply(A, B);
    printMatrix(P2);
    
    endClock = high_resolution_clock::now();
    cout << '\n' << "Parallel Time taken : " << duration_cast<microseconds>(endClock - startClock).count() << " microseconds" << '\n';
}
