#pragma once

#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;
using namespace std::chrono;

mutex displayMutex;

// Function for naive display of even numbers
inline void naiveDisplayEvenNumbers(const string &threadName, int start, int end)
{
    for (int i = start; i <= end; i += 2)
    {
        cout << "NS " << threadName << ": " << i << '\n';
    }
}

// Function for synchronized display of even numbers using mutex
inline void synchronizedDisplayEvenNumbers(const string &threadName, int start, int end)
{
    for (int i = start; i <= end; i += 2)
    {
        lock_guard<mutex> guard(displayMutex);
        cout << "S " << threadName << " : " << i << '\n';
    }
}

inline void OrderingWithMutex(int amount = 1000)
{
    auto startClock = high_resolution_clock::now();
    
    cout << "Naive Version (no synchronization):" << '\n';
    thread naiveThread1(naiveDisplayEvenNumbers, "Thread 1", 0, amount);
    thread naiveThread2(naiveDisplayEvenNumbers, "Thread 2", 1, amount);

    naiveThread1.join();
    naiveThread2.join();

    auto endClock = high_resolution_clock::now();
    cout << '\n' << "Naive Time taken: " << duration_cast<milliseconds>(endClock - startClock).count() << " milliseconds\n";

    
    cout <<'\n' << " ////////// " <<'\n';

    
    startClock = high_resolution_clock::now();
    
    cout << '\n' << "Synchronized Version (using mutex):" << '\n';
    thread syncThread1(synchronizedDisplayEvenNumbers, "Thread 1", 0, amount);
    thread syncThread2(synchronizedDisplayEvenNumbers, "Thread 2", 1, amount);

    syncThread1.join();
    syncThread2.join();
    
    endClock = high_resolution_clock::now();
    cout << '\n' << "Synchronised Time taken: " << duration_cast<milliseconds>(endClock - startClock).count() << " milliseconds\n";
}
