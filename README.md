# Parallelism
Multi Threading Exercises in C++

---

## Ex 1 : Matrix product
Write a program that compute the product of two matrices **P** = **A** x **B**. You remark the *Pij* are independent, which allow you to parallel the code.
1. Implement a sequential version, without threads.
2. Implement a by-value version : each value of the matrix is computed by a thread.
### Implementation
#### Sequential Version:
The ```matrixMultiplySequential``` function performs standard matrix multiplication in a nested loop, where the element
*pij* is computed by summing the products of corresponding elements from row *i* of matrix **A** and column *j* of matrix **B**.

#### Parallel Version:
The matrixMultiplyParallel function utilizes threads to compute each element *Pij* independently.
We launch a new thread for each element *Pij*, and each thread computes the corresponding value by summing the products of the corresponding row in *A* and column in *B*.
After launching all threads, we wait for all threads to finish by calling ```join()``` on each thread.

---

## Ex 2 : Sum of a table
Write a program that computes the sum of the elements of a table of n elements
1. Write a sequential version.
2. Write a version using thread local variable : the table is divided into m sub-tables, and each thread compute the sum into its own local variable and return it.
3. Write a version using a global sum variable and mutexes.
### Implementation

#### Sequential Version : 
The sum is computed in a single loop without any parallelism.

#### Thread Local Variables Version : 
The table is divided into ```m``` sub-tables, and each thread computes the sum of its respective sub-table. 
The results are stored in local variables, and the final sum is computed by adding these local sums.

#### Global Variable with Mutex Version : 
This version uses a global sum variable. 
Each thread computes the sum of its chunk of the table and then updates the global sum by locking the mutex to avoid race conditions.

---

## Ex 3 : Ordering with a mutex
Write a program that launch 2 threads : the first one displays even numbers between 0 and 1000, the second one displays uneven numbers between 0 and 1000.
1. Observe the result of a first naive version of this program.
2. Use mutexes to ensure the two threads display the numbers in the right order.
### Implementation

We use a shared ```counter``` variable to keep track of which number to print next.
A ```std::mutex``` is used to ensure that only one thread can access the ```counter``` at any given time.
```std::lock_guard<std::mutex>``` ensures the mutex is locked for the duration of the scope in which it is used, automatically unlocking the mutex when the scope is exited.
Both threads check the value of ```counter```. 

---
