//
// Created by xcm on 17/6/19.
//经过测试发现，采不采用swap的两个函数，运行效率差距很小
//交换次数与二叉树的层级成正比

#ifndef HEAP_MYHEAP_H
#define HEAP_MYHEAP_H

#include <iostream>
#include <cassert>
#include <cmath>
#include <typeinfo>
using namespace std;

template <typename T>
class MaxHeap{
private:
    //采用指针的形式，通过构造函数来分配数据的存储空间，比较灵活
    T* data;
    int count;
    int capacity;//最大容量

    //大的节点往上移动，维护最大堆的正确性
    //比较父节点与其自身(p)的大小,确保父节点比子节点大
    void shiftUp(int p){
        //p>1
        while(data[p/2]<data[p] && p>1){
            swap(data[p],data[p/2]);
            p/=2;
        }
    }

    //大的节点往上移动，维护最大堆的正确性
    //比较父节点与其自身(p)的大小,确保父节点比子节点大
    //类似于插入排序的优化，不用swap操作，加快速度
    void shiftUp2(int p){
        //p>1
        T t=data[p];
        while(data[p/2]<t && p>1){
            data[p]=data[p/2];
            p/=2;
        }
        data[p]=t;
    }

    //小的节点往下移动，维护最大堆的正确性
    void shiftDown(int p){
        while(p*2<=count){                      //有左孩子
            int i=p*2;                          //指向左孩子
            if(i+1<=count && data[i+1]>data[i]) //有右孩子，且右孩子大
                i+=1;                           //指向右孩子
            //指向大的孩子节点
            if(data[p]>data[i])                 //父节点大于孩子节点
                break;
            swap(data[p],data[i]);
            p=i;
        }
    }

    //小的节点往下移动，维护最大堆的正确性
    //类似于插入排序的优化，不用swap操作，加快速度
    void shiftDown2(int p){
        T t=data[p];
        int i;
        while(p*2<=count){                      //有左孩子
            i=p*2;                              //指向左孩子
            if(i+1<=count && data[i+1]>data[i]) //有右孩子，且右孩子大
                i+=1;                           //指向右孩子
            //指向大的孩子节点
            if(t>data[i])                 //父节点大于孩子节点
                break;
            data[p]=data[i];
            p=i;
        }
        data[p]=t;
    }


    void putNumberInLine( int num, string &line, int index_cur_level, int cur_tree_width, bool isLeft){

        int sub_tree_width = (cur_tree_width - 1) / 2;
        int offset = index_cur_level * (cur_tree_width+1) + sub_tree_width;
        assert(offset + 1 < line.size());
        if( num >= 10 ) {
            line[offset + 0] = '0' + num / 10;
            line[offset + 1] = '0' + num % 10;
        }
        else{
            if( isLeft)
                line[offset + 0] = '0' + num;
            else
                line[offset + 1] = '0' + num;
        }
    }

    void putBranchInLine( string &line, int index_cur_level, int cur_tree_width){

        int sub_tree_width = (cur_tree_width - 1) / 2;
        int sub_sub_tree_width = (sub_tree_width - 1) / 2;
        int offset_left = index_cur_level * (cur_tree_width+1) + sub_sub_tree_width;
        assert( offset_left + 1 < line.size() );
        int offset_right = index_cur_level * (cur_tree_width+1) + sub_tree_width + 1 + sub_sub_tree_width;
        assert( offset_right < line.size() );

        line[offset_left + 1] = '/';
        line[offset_right + 0] = '\\';
    }

public:
    //构造函数：生成一个容量为capacity的空的堆
    MaxHeap(int capacity){
        //以数组形式存储的完全二叉树，0元素不使用
        data=new T[capacity+1];
        count=0;
        this->capacity=capacity;
    }

    //构造函数：Heapify形式，从一个数组直接构造一个最大堆
    MaxHeap(T arr[],int n){
        data=new T[n+1];
        capacity=n;
        for(int i=0;i<n;i++)
            data[i+1]=arr[i];
        count=n;
        for(int i=count/2;i>=1;i--)
            shiftDown2(i);
    }


    ~MaxHeap(){
        delete[] data;
    }

    int size(){
        return count;
    }

    bool isEmpty(){
        return count==0;
    }

    void insert(T item){
        assert(count+1 <= capacity);
        count++;
        data[count]=item;
        shiftUp(count);
    }

    void insert2(T item){
        assert(count+1 <= capacity);
        count++;
        data[count]=item;
        shiftUp2(count);
    }

    T getMax(){
        assert(count>0);
        T t=data[1];
        data[1]=data[count];
        count--;
        shiftDown(1);
        return t;
    }

    T getMax2(){
        assert(count>0);
        T t=data[1];
        data[1]=data[count];
        count--;
        shiftDown2(1);
        return t;
    }

    void treePrint(){

        if( size() >= 100 ){
            cout<<"Fancy print can only work for less than 100 int";
            return;
        }

        if( typeid(T) != typeid(int) ){
            cout <<"Fancy print can only work for int item";
            return;
        }

        cout<<"The Heap size is: "<<size()<<endl;
        cout<<"data in heap: ";
        for( int i = 1 ; i <= size() ; i ++ )
            cout<<data[i]<<" ";
        cout<<endl;
        cout<<endl;

        int n = size();
        int max_level = 0;
        int number_per_level = 1;
        while( n > 0 ) {
            max_level += 1;
            n -= number_per_level;
            number_per_level *= 2;
        }

        int max_level_number = int(pow(2, max_level-1));
        int cur_tree_max_level_number = max_level_number;
        int index = 1;
        for( int level = 0 ; level < max_level ; level ++ ){
            string line1 = string(max_level_number*3-1, ' ');

            int cur_level_number = min(count-int(pow(2,level))+1,int(pow(2,level)));
            bool isLeft = true;
            for( int index_cur_level = 0 ; index_cur_level < cur_level_number ; index ++ , index_cur_level ++ ){
                putNumberInLine( data[index] , line1 , index_cur_level , cur_tree_max_level_number*3-1 , isLeft );
                isLeft = !isLeft;
            }
            cout<<line1<<endl;

            if( level == max_level - 1 )
                break;

            string line2 = string(max_level_number*3-1, ' ');
            for( int index_cur_level = 0 ; index_cur_level < cur_level_number ; index_cur_level ++ )
                putBranchInLine( line2 , index_cur_level , cur_tree_max_level_number*3-1 );
            cout<<line2<<endl;

            cur_tree_max_level_number /= 2;
        }
    }



};


#endif //HEAP_MYHEAP_H
