#include <iostream>
#include "myheap.h"
#include <ctime>
using namespace std;

//生成有n个元素的随机数组,元素范围为[rangel,ranger]
int* generateRandomArray(int n,int rangeL,int rangeR){
    assert(rangeL<=rangeR);
    int *arr=new int [n];
    //srand( (unsigned) time(NULL) );
    srand( (unsigned) rand() );
    for(int i=0;i<n;i++)
        arr[i]=rand()%(rangeR-rangeL+1)+rangeL;
    return arr;
}

void testswaptime(){
    int n=100000000;
    int *arr=generateRandomArray(n,0,n-1);

    clock_t startTime=clock();
    MaxHeap<int> maxheap1=MaxHeap<int>(n);
    for(int i=0;i<n;i++)
        maxheap1.insert(arr[i]);
    clock_t endTime=clock();
    cout<<"insert with swap : "<<double(endTime-startTime)/CLOCKS_PER_SEC<<" S "<<endl;

    startTime=clock();
    MaxHeap<int> maxheap2=MaxHeap<int>(n);
    for(int i=0;i<n;i++)
        maxheap2.insert2(arr[i]);
    endTime=clock();
    cout<<"insert without swap : "<<double(endTime-startTime)/CLOCKS_PER_SEC<<" S "<<endl;
}

void test1(){
    int n=30;
    int *arr=generateRandomArray(n,0,100);

    MaxHeap<int> maxheap=MaxHeap<int>(n);
    for(int i=0;i<n;i++)
        maxheap.insert(arr[i]);

    maxheap.treePrint();

    for(int i=0;i<n;i++)
        cout<<maxheap.getMax2()<<" ";
    cout<<endl;
}

template <typename T>
void heapSort(T arr[],int n){
    MaxHeap<T> maxheap=MaxHeap<T>(n);
    for(int i=0;i<n;i++)
        maxheap.insert2(arr[i]);
    for(int i=n-1;i>=0;i--)
        arr[i]=maxheap.getMax2();
}

template <typename T>
void heapSort2(T arr[],int n){
    MaxHeap<T> maxheap=MaxHeap<T>(arr,n);
    for(int i=n-1;i>=0;i--)
        arr[i]=maxheap.getMax2();
}

int main() {
    //windows7中两次随机序列相同
    int n=30;
    int *arr=generateRandomArray(n,10,99);
    int *arr2=generateRandomArray(n,10,99);
    for(int i=0;i<n;i++)
        cout <<arr[i]<<" ";
    cout<<endl;
    for(int i=0;i<n;i++)
        cout <<arr2[i]<<" ";
    cout<<endl;

    heapSort(arr,n);
    for(int i=0;i<n;i++)
        cout <<arr[i]<<" ";
    cout<<endl;


    heapSort2(arr2,n);
    for(int i=0;i<n;i++)
        cout <<arr2[i]<<" ";
    cout<<endl;

    return 0;
}