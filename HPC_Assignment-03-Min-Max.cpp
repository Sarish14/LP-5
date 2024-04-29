//============================================================================
// Name        : HPC_Assignment-03-Min-Max.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


// TIME COMPLEXITIES
//Normal     : O(n)
//Parallel 	: O(log n)

# include<bits/stdc++.h>

using namespace std;

// Function to perform parallel reduction for minimum value

int parallelMin(const vector<int> &arr)
{
    int result = arr[0];
#pragma omp parallel for reduction(min : result)
    for (int i = 0; i < arr.size(); ++i)
    {
        result = min(result, arr[i]);
    }
    return result;
}

// Function to perform parallel reduction for maximum value
int parallelMax(const vector<int> &arr)
{
    int result = arr[0];
#pragma omp parallel for reduction(max : result)
    for (int i = 0; i < arr.size(); ++i)
    {
        result = max(result, arr[i]);
    }
    return result;
}

// Function to perform parallel reduction for sum
int parallelSum(const vector<int> &arr)
{
    int result = arr[0];
#pragma omp parallel for reduction(+ : result)
    for (int i = 0; i < arr.size(); ++i)
    {
        result += arr[i];
    }
    return result;
}

// Function to perform parallel reduction for average

double parallelAverage(const vector<int> &arr)
{
    int sum = parallelSum(arr);
    return static_cast<double>(sum) / arr.size();
}

int main()
{
    const int size = 10;
    vector<int> arr(size);

    // Initialize the array with random values
    for (int i = 0; i < size; ++i)
    {
        arr[i] = rand() % 1000;
        cout << arr[i] << " ";
    }
    cout << endl;
    // Compute min, max, sum, and average using parallel reduction
    int minVal = parallelMin(arr);
    int maxVal = parallelMax(arr);
    int sum = parallelSum(arr);
    double average = parallelAverage(arr);

    cout << "Minimum value: " << minVal << endl;
    cout << "Maximum value: " << maxVal << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << average << endl;

    return 0;
}














//template <typename T>
//T parallelMin(const vector<T> &arr)
//{
//    T result = arr[0];
//#pragma omp parallel for reduction(min : result)
//    for (int i = 0; i < arr.size(); ++i)
//    {
//        result = min(result, arr[i]);
//    }
//    return result;
//}
