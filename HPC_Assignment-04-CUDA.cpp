//============================================================================
// Name        : HPC_Assignment-04-CUDA.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;


// CUDA code to multiply matrices
__global__ void multiply_gpu(int* A, int* B, int* C, int size) {
    // Uses thread indices and block indices to compute each element
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < size && col < size) {
        int sum = 0;
        for (int i = 0; i < size; i++) {
            sum += A[row * size + i] * B[i * size + col];
        }
        C[row * size + col] = sum;
    }
}

__global__ void matrix_multiplication_cpu(int *a, int *b, int *c, int size){
    for(int i = 0; i <size; i++){
        for(int j = 0; j < size; j++){
            int sum = 0;
            for(int k = 0; k < size; k++){
                sum += a[i*size + k] * b[k*size + j];
            }
            c[i*size + j] = sum;
        }
    }
}

void initialize(int* matrix, int size) {
    for (int i = 0; i < size * size; i++) {
        matrix[i] = rand() % 10;
    }
}


void print(int* matrix, int size) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            cout << matrix[row * size + col] << " ";
        }
        cout << '\n';
    }
    cout << '\n';
}


int main() {
    int* A, * B, * C;

    int N = 3;
    int blockSize =  16;

    int matrixSize = N * N;
    size_t matrixBytes = matrixSize * sizeof(int);

    A = new int[matrixSize];
    B = new int[matrixSize];
    C = new int[matrixSize];

    initialize(A, N);
    initialize(B, N);
    cout << "Matrix A: \n";
    print(A, N);

    cout << "Matrix B: \n";
    print(B, N);


    int* X, * Y, * Z;
    // Allocate space
    cudaMalloc(&X, matrixBytes);
    cudaMalloc(&Y, matrixBytes);
    cudaMalloc(&Z, matrixBytes);

    // Copy values from A to X
    cudaMemcpy(X, A, matrixBytes, cudaMemcpyHostToDevice);

    // Copy values from A to X and B to Y
    cudaMemcpy(Y, B, matrixBytes, cudaMemcpyHostToDevice);

    // Threads per CTA dimension
    int THREADS = 2;

    // Blocks per grid dimension
    int BLOCKS = N + THREADS - 1 / THREADS;

    cudaEvent_t start,stop;
    float elapsedTime;

    // Use dim3 structs for block  and grid dimensions
    dim3 threads(THREADS, THREADS);
    dim3 blocks(BLOCKS, BLOCKS);

     cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start,0);
    // Launch kernel
    multiply_gpu<<<blocks, threads>>>(X, Y, Z, N);
    cudaEventRecord(stop,0);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&elapsedTime,start,stop);

    cudaEventDestroy(start);
    cudaEventDestroy(stop);

    cudaMemcpy(C, Z, matrixBytes, cudaMemcpyDeviceToHost);
    cout << "Multiplication of matrix A and B: \n";
    print(C, N);
cout<<"Elapsed Time : "<<elapsedTime<<endl;


    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start,0);
    // Launch kernel
    matrix_multiplication_cpu<<<blocks, threads>>>(X, Y, Z, N);
    cudaEventRecord(stop,0);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&elapsedTime,start,stop);

    cudaEventDestroy(start);
    cudaEventDestroy(stop);

    cudaMemcpy(C, Z, matrixBytes, cudaMemcpyDeviceToHost);
    cout << "Multiplication of matrix A and B: \n";
    print(C, N);
cout<<"Elapsed Time : "<<elapsedTime<<endl;
    delete[] A;
    delete[] B;
    delete[] C;

    cudaFree(X);
    cudaFree(Y);
    cudaFree(Z);

    return 0;
}




































#include<bits/stdc++.h>
using namespace std;

void initialize(int *vector,int size){
    for(int i=0;i<size;i++){
        vector[i] = rand()%10;
    }
}

void print(int *vector,int size){
  for(int i=0;i<size;i++){
      cout<<vector[i] << " ";
  }
  cout<<endl;
}

__global__ void add_cpu(int *A, int *B,int *C,int size){
    for(int i=0;i<size;i++){
        C[i] = A[i] + B[i];
    }
}

__global__ void add_gpu(int *A, int *B,int *C,int size){
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    if(tid < size){
        C[tid] = A[tid] + B[tid];
    }
}

int main(){
    int N = 5;
    int vectorSize = N;
    size_t vectorBytes= vectorSize * sizeof(int);

    int *A,*B,*C;

    A = new int[vectorSize];
    B = new int[vectorSize];
    C = new int[vectorSize];

    initialize(A,N);
    initialize(B,N);

    cout<<"Vector A : ";
    print(A,N);

    cout<<"Vector B : ";
    print(B,N);

    int *X,*Y,*Z;
    cudaMalloc(&X,vectorBytes);
    cudaMalloc(&Y,vectorBytes);
    cudaMalloc(&Z,vectorBytes);

    cudaMemcpy(X,A,vectorBytes,cudaMemcpyHostToDevice);
    cudaMemcpy(Y,B,vectorBytes,cudaMemcpyHostToDevice);

    cudaEvent_t start,stop;
    float elapsedTime;

    int threadsPerBlock = 256;
    int blocksPerGrid = N + threadsPerBlock -1 / threadsPerBlock;

    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start,0);
    add_gpu<<<blocksPerGrid, threadsPerBlock>>>(X,Y,Z,N);
    cudaEventRecord(stop,0);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&elapsedTime,start,stop);

    cudaEventDestroy(start);
    cudaEventDestroy(stop);
    cudaMemcpy(C,Z,vectorBytes,cudaMemcpyDeviceToHost);
    cout<<"GPU RESULT : ";
    print(C,N);
    cout<<"Elapsed Time : "<<elapsedTime<<endl;

    //cpu
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start,0);
    add_cpu<<<blocksPerGrid, threadsPerBlock>>>(X,Y,Z,N);
    cudaEventRecord(stop,0);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&elapsedTime,start,stop);

    cudaEventDestroy(start);
    cudaEventDestroy(stop);
    cudaMemcpy(C,Z,vectorBytes,cudaMemcpyDeviceToHost);
    cout<<"CPU RESULT : ";
    print(C,N);
    cout<<"Elapsed Time : "<<elapsedTime<<endl;

    delete[] A;
    delete[] B;
    delete[] C;
    cudaFree(X);
    cudaFree(Y);
    cudaFree(Z);
    return 0;
}
