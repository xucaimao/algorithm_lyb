//
// Created by xcm on 17/6/25.
//
#include <iostream>
#include <queue>
#include <cassert>
#include <cmath>
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

        //复制节点的构造函数
        Node(Node* node){
            this->key=node->key;
            this->value=node->value;
            this->left=node->left;
            this->right=node->right;
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

    //在以node为根节点的二叉树中查找最小元素，返回节点的指针
    Node* MinNode(Node* node){
        if(node->left == NULL)
            return node;
        return MinNode(node->left);
    }

    //在以node为根节点的二叉树中查找最小元素，返回节点的指针
    Node* MaxNode(Node* node){
        if(node->right == NULL)
            return node;
        return MaxNode2(node->right);
    }

    //在以node为根节点的二叉树中删除最小元素,并返回新的根节点
    Node* delMin(Node* node){
        if(node->left==NULL){
            //找到最小节点
            Node* next=NULL;
            //如果最小节点存在右子树(右子树中节点的值都大于该节点)，保存右子树的节点
            if(node->right)
                next=node->right;
            delete node;    //删除节点本身
            count--;        //注意此值的维护
            return next;    //返回NULL或右子树的根节点，赋值给父节点的左孩子
        }
        node->left=delMin(node->left);
        return node;
    }

    Node* delMax(Node* node){
        if(node->right==NULL){
            //找到最大节点
            Node* next=NULL;
            if(node->left)
                next=node->left;

            //如果最大节点存在左子树(左子树中节点的值都大于该节点)，保存左子树的节点
            //如果不存在，该值为NULL。

            delete node;
            count--;
            return next;
        }
        node->right=delMax(node->right);
        return node;
    }

    //在以node为根节点的竖二叉树中，删除值为key的节点，并返回新的二叉树的根
    Node* delNode(Node* node,Key key){
        if(node==NULL)
            return NULL;
        if(key < node->key){
            node->left=delNode(node->left,key);
        }
        else if(key > node->key){
            node->right=delNode(node->right,key);
        }
        else{   //找到该节点
            if(node->left==NULL){
                Node* next=node->right;
                delete node;
                count--;
                return next;
            }
            else if(node->right==NULL){
                Node* next=node->left;
                delete node;
                count--;
                return next;
            }
            else{   //左右孩子都不为空

                //找到右子树中的最小节点,并复制一份
                //复制节点是因为下面要删除该节点，一旦删除指针就失效了
                Node* next=new Node( MinNode(node->right) );
                count++;
                //这里不能直接把node->right复制给next->right,考虑到右子树只有一个节点的情况
                next->right=delMin(node->right);
                next->left=node->left;
                delete node;
                count--;
                return next;
            }
        }
    }

    //返回二叉树的最大深度
    int getMaxDeepth(Node* node){
        if(node==NULL)
            return 0;
        int dl=getMaxDeepth(node->left);
        int dr=getMaxDeepth(node->right);
        return max(dl,dr)+1;
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
            count++;    //此处少了，发现bug
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
        else{
            printBST(root);
            cout<<endl;
        }
    }

    int widthOfNum(Key key){
        //本程序按int型返回数组的位数
        int n=0;
        while(key>0){
            n++;
            key/=10;
        }
        return n;
    }

    //广度遍历，按树形打印二叉树
    //构建一个完全二叉树
    void BFSPrint(){
        //TODO
        int deep=getMaxDeepth(root);    //二叉树的最大深度
        int sz=(int) pow( 2, deep );    //二叉树的完全形式的节点数+1
        Key key[]=new Key [sz];         //一顺序数组的形式存储要打印的值
        bool hasnode[]=new bool [sz];   //该节点是否存在的标志数组
        for(int i=0;i<sz;i++){
            hasnode=false;
        }


        queue<Node*> nodeq;             //节点序列
        queue<int> posq;                //节点对于在完全二叉树中的位置
        Node* node;
        int pos;
        int maxkey=root->key;
        nodeq.push(root);
        posq.push(1);                   //第1个元素作为根节点
        while( !nodeq.empty() ){        //开始构建完全二叉树的数组形式
            //pop函数没有返回值，取队列首元素需用front函数
            node=nodeq.front();
            nodeq.pop();
            pos=posq.front();
            posq.pop();

            key[pos]=node->key;
            if(node->key > maxkey)
                maxkey=node->key;       //取得最大值，用于计算打印宽度
            hasnode[pos]=true;

            if(node->left != NULL){
                nodeq.push(node->left);
                posq.push(pos*2);   //左子孩子在完全二叉树中的位置是父节点的位置*2

            }

            if(node->right !=NULL){
                nodeq.push(node->right);
                posq.push(pos*2+1); //右子孩子在完全二叉树中的位置是父节点的位置*2+1
            }

        }   //完全二叉树的顺序存储数组构建结束



        int wkey=widthOfNum(maxkey);
        for(int i=1;i<sz;i++){//开始打印

        }

    }

    //非递归的查找最小值
    Value MinNode(){
        assert(count!=0);
        Node* p=root;
        while(p->left)
            p=p->left;
        return p->value;
    }

    //递归形式的查找最小值
    Value MinNode2(){
        assert(count!=0);
        Node* minnode=MinNode(root);
        return minnode->value;
    }

    //非递归的查找最大值
    Value MaxNode(){
        Node* p=root;
        while(p->right)
            p=p->right;
        return p->value;
    }

    void delMin(){
        if(root)    //根不为空才进行操作
           root=delMin(root);   //少了root=  好大一个bug
    }

    void delMax(){
        if(root)    //根不为空才进行操作
            root=delMax(root);  //少了root=  好大一个bug
    }

    bool delNode(Key key){
        assert(count!=0);
        if(contain(key)){
            root=delNode(root,key);
            return true;
        }
        else
            return false;
    }

    int getMaxDeepth(){
        return getMaxDeepth(root);
    }




};

#endif //BST_BST_H
