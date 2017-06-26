//
// Created by xcm on 17/6/25.
//
#include <iostream>
#include <queue>
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
            //粗心害死人!!!
        }
    };

    Node* root;
    int count;

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

    //中序遍历打印二叉树
    void printBST(Node* node){
        if(node== NULL)
            return;

        printBST(node->left);
        cout<< "( "<<node->key<<" , "<<node->value <<" ) ";
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

    //递归的search
    Value* search(Node* node,Key key){
        if(node == NULL)
            return NULL;
        if(key == node->key)
            // 返回值的形式是个重点。既考虑了类的封装，
            // 隐藏了数据，又保证了编程的便捷。(没找到则返回NULL)
            return &(node->value);
        else if(key < node->key )
            return search(node->left,key);
        else
            return search(node->right,key);
    }

    //后序遍历释放节点空间
    void destroy(Node* node){
        if(node==NULL)
            return;

        destroy(node->left);
        destroy(node->right);
        delete node;
        count--;
    }

public:
    BST(){
        root=NULL;
        count=0;
    }
    ~BST(){
        destroy(root);
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

    //递归contain的调用接口
    bool contain(Key key){
        return contain(root,key);
    }

    //非递归的contain函数
    bool contain2(Key key){
        Node* p=root;
        while(p!=NULL){
            if(key==p->key)
                return true;
            else if(key<p->key)
                p=p->left;
            else
                p=p->right;
        }
        return false;
    }

    //递归search的调用接口
    Value* search(Key key){
        return search(root,key);
    }

    //非递归的search
    Value* search2(Key key){
        Node* p=root;
        while(p!=NULL){
            if(key==p->key)
                return &(p->value);
            else if(key < p->key)
                p=p->left;
            else
                p=p->right;
        }
        return NULL;
    }

    //中序遍历打印二叉树的接口
    void PrintBST(){
        //cout<<"Begin to printing..."<<endl;
        if(root==NULL)
            cout<<"ERROR: the tree is empty!"<<endl;
        printBST(root);
        cout<<endl;
    }

    //
    void BFSPrintBST(){
        queue<Node*> q;
        Node* p;
        q.push(root);
        while( !q.empty() ){
            //pop函数没有返回值，取队列首元素需用front函数
            p=q.front();
            q.pop();

            if(p->left != NULL)
                q.push(p->left);
            if(p->right !=NULL)
                q.push(p->right);
            cout<< "( "<<p->key<<" , "<<p->value <<" ) ";
        }
        cout<<endl;
    }

    Value MinKey(){
        Node* p=root;
        while(p->left)
            p=p->left;
        return p->value;
    }


    Value MaxKey(){
        Node* p=root;
        while(p->right)
            p=p->right;
        return p->value;
    }
};

#endif //BST_BST_H
