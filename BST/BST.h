//
// Created by xcm on 17/6/25.
//
#include <iostream>
using namespace std;

#ifndef BST_BST_H
#define BST_BST_H

template <typename Key, typename Value>
class BST{
private:
    struct Node{
        //节点的数据结构及构造函数
        Key key;
        Value value;
        Node* left;
        Node* right;

        Node(Key key,Value value){
            this->key=key;
            this->value=value;
            this->left=this->right=NULL;
            //在这里折腾了我很久，因为把right写成了left
            //调试了很久也没找到错误原因，对比程序才最终发现
            //粗心害死人
        }
    };

    Node* root;
    int count;


public:
    BST(){
        root=NULL;
        count=0;
    }
    ~BST(){
        //TODO
    }
    int size(){
        return count;
    }
    bool isEmpty(){
        return count==0;
    }

    //插入函数接口，调用递归函数进行插入
    void insert(Key key,Value value){
        root=insert(root,key,value);
    }

    //非递归的插入函数
    void insert2(Key key,Value value){
        if(root==NULL){
            //根节点需要单独处理
            root=new Node(key,value);//生成新节点
            return;
        }

        Node* p=root;
        Node* fa=NULL;//父节点指针
        int dir=0;//左右孩子标志，0左1右
        while(true){
            if(p==NULL){
                p=new Node(key,value);//生成新节点
                //cout<<"add "<<key<<" "<<endl;
                if(fa != NULL){
                    //父节点非空,新节点与父节点建立联系
                    if(dir==0)
                        fa->left=p;
                    else
                        fa->right=p;
                }
                count++;
                break;
            }
            if(key == p->key){
                p->value=value;
                break;
            }
            if(key < p->key){
                fa=p;
                dir=0;
                p=p->left;
            }

            else{
                fa=p;
                dir=1;
                p=p->right;
            }
        }
    }

    bool contain(Key key){
        return contain(root,key);
    }

    Value* search(Key key){
        return search(root,key);
    }

    //前序遍历打印二叉树
    void printBST(){
        cout<<"Begin to printing..."<<endl;
        if(root==NULL)
            cout<<"ERROR: the tree is empty!"<<endl;
        printBST(root);
    }

private:
    //递归形式
    // 向以node为根节点的二叉搜索树，插入节点(key,value)
    //返回插入新节点后的二叉搜索树的根
    Node* insert(Node* node,Key key,Value value){
        if(node==NULL){
            count++;
            //新生成一个节点并利用构造函数为节点赋值
            //cout<<"add "<<key<<" "<<endl;
            return new Node(key,value);
        }
        if(key == node->key)
            node->value=value;
        else if(key < node->key)
            node->left=insert(node->left,key,value);
        else
            node->right=insert(node->right,key,value);

        //return node;
    }

    //前序遍历打印二叉树
    void printBST(Node* node){
        if(node== NULL)
            return;

        printBST(node->left);
        cout<< node->key <<" ";
        printBST(node->right);
    }

    //查看在以node为根的二叉搜索树中，是否包含键值为key的节点
    bool contain(Node* node,Key key){
        if(node == NULL)
            return false;

        if(node->key == key )
            return true;
        else if(key < node->key)
            return contain(node->left,key);
        else
            return contain(node->right,key);

    }

    Value* search(Node* node,Key key){
        if(node == NULL)
            return NULL;
        if(key == node->key)
            return &(node->value);
        else if(key < node->key )
            return search(node->left,key);
        else
            return search(node->right,key);
    }


};

#endif //BST_BST_H