#include "MatMultiplication.h"
#include "TableSum.h"
#include "OrderingWithMutex.h"
#include <chrono>

using namespace std::chrono;

int main()
{
    auto globalTimeClockStart = high_resolution_clock::now();
    
    cout << "Matrix Multiplication :" << '\n';
    // matrices A and B
    vector<vector<int>> A = {{8, 20, 3}, {4, 9, 6}, {7, 8, 5}};
    vector<vector<int>> B = {{70, 8, 45}, {9, 10, 18}, {11, 12, 4}};
    
    MatMultiplication(A, B);

    
    cout <<'\n' << " ---------- " <<'\n';

    
    cout << '\n' << "Table Sum : " << '\n';
    //vector<int> table = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> table = {10, 4, 9, 13, 27, 8, 7, 2, 3, 1};
    int numThreads = 3; // For Parallel Sum With Mutex, default is 3
    
    TableSum(table, numThreads);
    
    
    cout <<'\n' << " ---------- " <<'\n';
    
    
    cout << '\n' << "Ordering with Mutex :" << '\n';
    
    OrderingWithMutex(100); // Default is 1000
    
    
    cout << '\n' << " ---------- " <<'\n';
    
    
    auto globalTimeClockEnd = high_resolution_clock::now();
    cout << '\n' << "Total Time taken : " << duration_cast<milliseconds>(globalTimeClockEnd - globalTimeClockStart).count() << " milliseconds" << '\n';
    
    return 0;
}
