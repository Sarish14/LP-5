//============================================================================
// Name        : HPC_Assignment-02-Sorting.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

// TIME COMPLEXITIES
//Normal Bubble    : O(n^2)
//Normal Merge	: O(n log n)
//Parallel Bubble  : O(n^2/p)
//Parallel Merge  : O(n log n/p)


#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>

using namespace std;
using namespace std::chrono;

// Function to perform Bubble Sort
void bubbleSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Function to merge two sorted subarrays
void merge(vector<int> &arr, int low, int middle, int high)
{
    int n1 = middle - low + 1;
    int n2 = high - middle;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = arr[low + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[middle + 1 + j];

    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            ++i;
        }
        else
        {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

// Function to perform Merge Sort recursively
void mergeSort(vector<int> &arr, int l, int r)
{
    if (l < r)
    {
        int m = (l + r) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

// Parallel Bubble Sort
void parallelBubbleSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i)
    {
#pragma omp parallel for
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Parallel Merge Sort
void parallelMergeSort(vector<int> &arr, int l, int r)
{
    if (l < r)
    {
        int m = (l + r)/ 2;

#pragma omp parallel sections
        {
#pragma omp section
            parallelMergeSort(arr, l, m);

#pragma omp section
            parallelMergeSort(arr, m + 1, r);
        }

        merge(arr, l, m, r);
    }
}

int main()
{
    const int size = 100000; // Size of the array
    vector<int> arr(size), arr_copy(size);

    // Initialize the array with random values
    for (int i = 0; i < size; ++i)
    {
        arr[i] = rand() % 10000;
        arr_copy[i] = arr[i];
    }

    // Measure sequential Bubble Sort execution time
    auto start = high_resolution_clock::now();
    bubbleSort(arr_copy);
    auto stop = high_resolution_clock::now();
    auto seq_duration_bubble = duration_cast<milliseconds>(stop - start);

    // Measure parallel Bubble Sort execution time
    start = high_resolution_clock::now();
    parallelBubbleSort(arr);
    stop = high_resolution_clock::now();
    auto par_duration_bubble = duration_cast<milliseconds>(stop - start);

    // Measure sequential Merge Sort execution time
    start = high_resolution_clock::now();
    mergeSort(arr_copy, 0, size - 1);
    stop = high_resolution_clock::now();
    auto seq_duration_merge = duration_cast<milliseconds>(stop - start);

    // Measure parallel Merge Sort execution time
    start = high_resolution_clock::now();
    parallelMergeSort(arr, 0, size - 1);
    stop = high_resolution_clock::now();
    auto par_duration_merge = duration_cast<milliseconds>(stop - start);

    // Output results
    cout << "Sequential Bubble Sort Time: " << seq_duration_bubble.count() << " milliseconds" << endl;
    cout << "Parallel Bubble Sort Time: " << par_duration_bubble.count() << " milliseconds" << endl;
    cout << "Sequential Merge Sort Time: " << seq_duration_merge.count() << " milliseconds" << endl;
    cout << "Parallel Merge Sort Time: " << par_duration_merge.count() << " milliseconds" << endl;

    return 0;
}

/*
To Run Execute the following commands:
g++ -fopenmp Assignment2.cpp -o Assignment2
./Assignment2
*/


// // g++ 2_merge_bubble.cpp -lgomp -o 2_merge_bubble && ./2_merge_bubble







//Measure Sequential Merge Sort Time
//start_time = omp_get_wtime();
//mergeSort(arr, 0, n - 1);
//end_time = omp_get_wtime();
//printArray(arr, n);
//cout << "Sequential Merge Sort took: " << end_time - start_time << " seconds\n";
