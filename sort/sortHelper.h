//
// Created by Administrator on 2017/2/20.
//

#ifndef SORT_SORTHELPER_H
#define SORT_SORTHELPER_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cassert>
using namespace std;

namespace sortHelper{
    //生成有n个元素的随机数组,元素范围为[rangel,ranger]
    int* generateRandomArray(int n,int rangeL,int rangeR){
        assert(rangeL<=rangeR);
        int *arr=new int [n];
        srand(time(NULL));
        for(int i=0;i<n;i++)
            arr[i]=rand()%(rangeR-rangeL+1)+rangeL;
        return arr;
    }

    int * generateNearlySortedArray(int n,int swaptime){
        int *arr=new int [n];
        for(int i=0;i<n;i++)
            arr[i]=i;
        srand(time(NULL));
        for(int i=0;i<swaptime;i++){
            int p1=rand()%n;
            int p2=rand()%n;
            swap(arr[p1],arr[p2]);
        }
        return arr;
    }

    //打印数组arr
    template <typename T>
    void printArray(T arr[], int n) {
        for(int i=0;i<n;i++)
            cout<<arr[i]<<" ";
        cout<<endl;
        return;
    }

    //测试一个数组是否按从小到大的顺序排列
    template <typename T>
    bool isSorted(T arr[], int n){
        for(int i=0;i<n-1;i++)
            if(arr[i] > arr[i+1]) return false;
        return true;
    }

    //测试程序执行时间
    //通过函数指针，调用排序函数sort，对数组arr中的n个元素进行排序
    template <typename T>
    void testSort(string sortName, void(*sort)(T[],int),T arr[],int n){
        clock_t startTime=clock();
        sort(arr,n);
        clock_t endTime=clock();
        assert(isSorted(arr,n));
        cout<<sortName<<" : "<<double(endTime-startTime)/CLOCKS_PER_SEC<<" S "<<endl;
        return;
    }

    //拷贝数组
    int* copyArray(int arr[],int n){
        int *newarr=new int [n];
        for(int i=0;i<n;i++)
            newarr[i]=arr[i];
        return newarr;
    }

}
#endif //SORT_SORTHELPER_H
