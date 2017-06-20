#include <iostream>
#include "mySort.h"
#include "sortHelper.h"
#include "inversionpair.h"
#include "quickselection.h"

using namespace std;
//逆序对程序测试
void test_inversion_pair(){
    int n=10000;
    int *arr1=sortHelper::generateRandomArray(n,0,n);
    int *arr2=sortHelper::copyArray(arr1,n);
    //int arr1[]={1,2,3,4,5,6,7,8};
    //int arr1[]={9,8,7,6,5,4,3,2,1};

    testInversionPairTime("[brute force time]",inversionPairBF,arr1,0,n-1);
    testInversionPairTime("[merge sort time ]",inversionPairMS,arr1,0,n-1);
    testInversionPairTime2("[merge sort time ]",inversionPairMS,arr2,0,n-1);

}

//快速选择程序测试
void test_quickSelection(){
    //int arr1[]={49,38,65,97,76,13,27,48,55,4};
    int n=10000000;
    int k=4000;
    cout<<endl<<"data number is : "<<n<<endl;

    int* arr1=sortHelper::generateRandomArray(n,0,n);
    int* arr2=sortHelper::copyArray(arr1,n);
    cout<<endl<<" data type is  : random"<<endl;
    testQuickSelectionTime("brute  force",quickSelectionBF,arr1,n,k);
    //sortHelper::printArray(arr1,n);
    testQuickSelectionTime("quick select",quickSelectionQM,arr2,n,k);
    //sortHelper::printArray(arr2,n);
    delete [] arr1;
    delete [] arr2;

    arr1=sortHelper::generateNearlySortedArray(n,100);
    arr2=sortHelper::copyArray(arr1,n);
    cout<<endl<<" data type is : nearly random"<<endl;
    testQuickSelectionTime("brute  force",quickSelectionBF,arr1,n,k);
    //sortHelper::printArray(arr1,n);
    testQuickSelectionTime("quick select",quickSelectionQM,arr2,n,k);
    //sortHelper::printArray(arr2,n);
    delete[] arr1;
    delete[] arr2;
}


//用于测试单个程序的正确性
void testprog(){
    int n=10;
    //int *arr1=sortHelper::generateRandomArray(n,0,100);
    int arr1[]={49,38,65,97,76,13,27,48,55,4};
    sortHelper::printArray(arr1,n);
    mergeSort(arr1,n);
    sortHelper::printArray(arr1,n);
    //delete[] arr1;
}

//用于比较多个程序的运行效率
void testsorttime(){
    int n = 100000;

    // 测试1 一般性测试
    cout<<"Test for Random Array, size = "<<n<<", random range [0, "<<n<<"]"<<endl;
    int* arr1 = sortHelper::generateRandomArray(n,0,n);
    int* arr2 = sortHelper::copyArray(arr1,n);
    int* arr3 = sortHelper::copyArray(arr1,n);
    int* arr4 = sortHelper::copyArray(arr1,n);
    int* arr5 = sortHelper::copyArray(arr1,n);

    sortHelper::testSort("Merge Sort", mergeSort, arr1, n);
    sortHelper::testSort("Quick Sort 2 Ways", quickSort, arr2, n);
    sortHelper::testSort("Quick Sort 3 Ways", quickSort3Way, arr3, n);
    sortHelper::testSort("Heap sort 1", heapSort, arr4, n);
    sortHelper::testSort("Heap sort 2", heapSort2, arr5, n);

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    delete[] arr5;

    cout<<endl;


    // 测试2 测试近乎有序的数组
    int swapTimes = 100;
    cout<<"Test for Random Nearly Ordered Array, size = "<<n<<", swap time = "<<swapTimes<<endl;
    arr1 = sortHelper::generateNearlySortedArray(n,swapTimes);
    arr2 = sortHelper::copyArray(arr1, n);
    arr3 = sortHelper::copyArray(arr1, n);
    arr4 = sortHelper::copyArray(arr1,n);
    arr5 = sortHelper::copyArray(arr1,n);

    sortHelper::testSort("Merge Sort", mergeSort, arr1, n);
    sortHelper::testSort("Quick Sort 2 ways", quickSort, arr2, n);
    sortHelper::testSort("Quick Sort 3 Ways", quickSort3Way, arr3, n);
    sortHelper::testSort("Heap sort 1", heapSort, arr4, n);
    sortHelper::testSort("Heap sort 2", heapSort2, arr5, n);

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    delete[] arr5;

    cout<<endl;


    // 测试3 测试存在包含大量相同元素的数组
    cout<<"Test for Random Array, size = "<<n<<", random range [0,10]"<<endl;
    arr1 = sortHelper::generateRandomArray(n,0,10);
    arr2 = sortHelper::copyArray(arr1, n);
    arr3 = sortHelper::copyArray(arr1, n);
    arr4 = sortHelper::copyArray(arr1,n);
    arr5 = sortHelper::copyArray(arr1,n);

    sortHelper::testSort("Merge Sort", mergeSort, arr1, n);
    sortHelper::testSort("Quick Sort 2 Ways", quickSort, arr2, n);
    sortHelper::testSort("Quick Sort 3 Ways", quickSort3Way, arr3, n);
    sortHelper::testSort("Heap sort 1", heapSort, arr4, n);
    sortHelper::testSort("Heap sort 2", heapSort2, arr5, n);

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    delete[] arr5;
}

int main() {

    //testprog();
    testsorttime();
    //test_inversion_pair();
    //test_quickSelection();
    return 0;
}