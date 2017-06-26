//
// Created by xcm on 17/6/25.
//
#include <iostream>
#include <cassert>
#include "BST.h"
using namespace std;

//生成有n个元素的随机数组,元素范围为[rangel,ranger]
int* generateRandomArray(int n,int rangeL,int rangeR){
    assert(rangeL<=rangeR);
    int *arr=new int [n];
    //srand( (unsigned) time(NULL) );
    //上面的程序会造成两次生成的随机序列相同，因为time返回值只精确到秒，
    //会造成两次随机函数执行时time的返回值相同的情况，进而使得随机序列相同
    srand( (unsigned) rand() );
    for(int i=0;i<n;i++)
        arr[i]=rand()%(rangeR-rangeL+1)+rangeL;
    return arr;
}

//测试程序
void test(){
    //两种定义形式都是可以的
    //BST<int,int> bst=BST<int,int>();
    BST<int,int> bst;
    int arr[]={41,22,58,15,33,50,60,13,28,37,42,53};
    //        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,11}
    int n=12;
    //int* arr=generateRandomArray(n,10,99);
    cout<<"The data is : "<<endl;
    for(int i=0;i<n;i++)
        cout<<arr[i]<<" ";
    cout<<endl;

    cout<<"begin insert data to tree..."<<endl;
    for(int i=0;i<n;i++)
        bst.insert2(arr[i],1);

    bst.printBST();

    int target;
    while(cin>>target && target!=-1){
        cout << "The element [ "<<target <<" ]  ";
        if( bst.contain(target) )
            cout<<"exist!"<<endl;
        else
            cout<<"not exist!"<<endl;
    }
}

int main() {

    test();
    return 0;
}