#include "MatMultiplication.h"
#include "TableSum.h"
#include "OrderingWithMutex.h"

int main()
{
    cout << "Matrix Multiplication :" << '\n';
    // matrices A and B
    vector<vector<int>> A = {{1, 20, 3}, {4, 9, 6}, {7, 8, 5}};
    vector<vector<int>> B = {{7, 8, 45}, {9, 10, 18}, {11, 12, 4}};
    MatMultiplication(A, B);

    cout <<'\n' << " ---------- " <<'\n';
    
    cout << '\n' << "Table Sum :" << '\n';
    vector<int> table = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int numThreads = 3; // For Parallel Sum With Mutex
    TableSum(table, numThreads);
    
    cout <<'\n' << " ---------- " <<'\n';
    
    cout << '\n' << "Ordering with Mutex :" << '\n';
    OrderingWithMutex();
    
    cout <<'\n' << " ---------- " <<'\n';
    
    return 0;
}
