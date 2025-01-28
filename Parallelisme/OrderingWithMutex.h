#pragma once

#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

mutex displayMutex;

// Function for naive display of even numbers
inline void naiveDisplayEvenNumbers(const string &threadName, int start, int end)
{
    for (int i = start; i <= end; i += 2)
    {
        cout << threadName << ": " << i << '\n';
    }
}

// Function for synchronized display of even numbers using mutex
inline void synchronizedDisplayEvenNumbers(const string &threadName, int start, int end)
{
    for (int i = start; i <= end; i += 2)
    {
        lock_guard<mutex> guard(displayMutex);
        cout << threadName << " : " << i << '\n';
    }
}

inline void OrderingWithMutex()
{
    cout << "Naive Version (no synchronization):" << '\n';
    thread naiveThread1(naiveDisplayEvenNumbers, "Thread 1", 0, 1000);
    thread naiveThread2(naiveDisplayEvenNumbers, "Thread 2", 1, 1000);

    naiveThread1.join();
    naiveThread2.join();

    cout << '\n' << "Synchronized Version (using mutex):" << '\n';
    thread syncThread1(synchronizedDisplayEvenNumbers, "Thread 1", 0, 1000);
    thread syncThread2(synchronizedDisplayEvenNumbers, "Thread 2", 1, 1000);

    syncThread1.join();
    syncThread2.join();
}
