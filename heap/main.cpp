#include <iostream>
#include "myheap.h"
using namespace std;

//生成有n个元素的随机数组,元素范围为[rangel,ranger]
int* generateRandomArray(int n,int rangeL,int rangeR){
    assert(rangeL<=rangeR);
    int *arr=new int [n];
    srand(time(NULL));
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

int main() {
    int n=30;
    int *arr=generateRandomArray(n,0,100);

    MaxHeap<int> maxheap=MaxHeap<int>(n);
    for(int i=0;i<n;i++)
        maxheap.insert(arr[i]);

    maxheap.treePrint();

    for(int i=0;i<n;i++)
        cout<<maxheap.getMax2()<<" ";
    cout<<endl;
    return 0;
}