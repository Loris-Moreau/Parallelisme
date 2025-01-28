#pragma once

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

// Function to compute sum sequentially
inline int sequentialSum(const vector<int> &table)
{
    int sum = 0;
    for (int val : table)
    {
        sum += val;
    }
    return sum;
}

// Function to compute sum using thread local variables
inline void computeLocalSum(const vector<int> &table, int start, int end, int &localSum)
{
    localSum = 0;
    for (int i = start; i < end; ++i)
    {
        localSum += table[i];
    }
}

inline int parallelSumWithLocalVariables(const vector<int> &table, int numThreads)
{
    int n = (int)table.size();
    int chunkSize = n / numThreads;
    vector<thread> threads;
    vector<int> localSums(numThreads, 0);

    for (int t = 0; t < numThreads; ++t)
    {
        int start = t * chunkSize;
        int end = (t == numThreads - 1) ? n : start + chunkSize;
        threads.emplace_back(computeLocalSum, cref(table), start, end, ref(localSums[t]));
    }

    for (auto &t : threads)
    {
        t.join();
    }

    int totalSum = 0;
    for (int localSum : localSums)
    {
        totalSum += localSum;
    }

    return totalSum;
}

// Function to compute sum using a global variable and mutex
mutex sumMutex;
int globalSum = 0;

inline void computeSumWithMutex(const vector<int> &table, int start, int end) {
    int localSum = 0;
    for (int i = start; i < end; ++i)
    {
        localSum += table[i];
    }
    lock_guard<mutex> guard(sumMutex);
    globalSum += localSum;
}

inline int parallelSumWithMutex(const vector<int> &table, int numThreads)
{
    int n = (int)table.size();
    int chunkSize = n / numThreads;
    vector<thread> threads;
    globalSum = 0;

    for (int t = 0; t < numThreads; ++t)
    {
        int start = t * chunkSize;
        int end = (t == numThreads - 1) ? n : start + chunkSize;
        threads.emplace_back(computeSumWithMutex, cref(table), start, end);
    }

    for (auto &t : threads)
    {
        t.join();
    }

    return globalSum;
}

inline void TableSum(vector<int> table, int numThreads = 3)
{
    // Sequential version
    cout << "Sequential Sum: " << sequentialSum(table) << '\n';

    // Parallel version with thread local variables
    cout << "Parallel Sum with Local Variables: " << parallelSumWithLocalVariables(table, numThreads) << '\n';

    // Parallel version with global sum and mutex
    cout << "Parallel Sum with Mutex: " << parallelSumWithMutex(table, numThreads) << '\n';
}
