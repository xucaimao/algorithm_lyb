//
// Created by xcm on 17/6/25.
//
#include <iostream>

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
            this->left=this->left=NULL;
        }
    };

    Node* root;
    int count;

    //向以node为根节点的二叉搜索树，插入节点(key,value)
    //返回插入新节点后的二叉搜索树的根
    Node* insert(Node* node,Key key,Value value){
        if(node==NULL){
            count++;
            //新生成一个节点并利用构造函数为节点赋值
            return new Node(key,value);
        }
        if(key==node->key)
            node->value=value;
        else if(key<node->key)
            node->left=insert(node->left,key,value);
        else
            node->right=insert(node->right,key,value);

        return node;
    }


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
    void insert(Key key,Value value){
        root=insert(root,key,value);
    }
};

#endif //BST_BST_H
