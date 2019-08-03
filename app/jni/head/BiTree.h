/**
 * 作者：chenda
 * 时间：2019/8/2:15:39
 * 邮箱：
 * 说明：
 */

#ifndef CORENOTE_BITREE_H
#define CORENOTE_BITREE_H

#include "Stack.h"

template <class DT>
struct BiNode{
    DT data;
    BiNode *lchild,*rchild;
};
template <class DT>
BiNode<DT>* creatBiTree_M(const DT *array, int size, int index);

//前序递归遍历二叉树,level当前层数,visit每次遍历到节点要做的事情
template <class DT>
void preOrder_M(BiNode<DT>* t,int level,void (*visit)(DT ,int ));

//前序非递归遍历二叉树
template <class DT>
void preOrder_stack_M(BiNode<DT>* t,int level,void (*visit)(DT ,int ));

//层序遍历二叉树,level当前层数,visit每次遍历到节点要做的事情
template <class DT>
void levelOrder_M(BiNode<DT>* t,void (*visit)(DT ));

template <class DT>
void destroyBiTree_M(BiNode<DT>* t);

template <class DT>
class BiTree{
private:
    BiNode<DT> *tree;

public:
    BiTree();
    ~BiTree();

    /*
    * Description:     根据数组创建二叉树，链表法
    * Input:           array   数组头指针
    *                  size    数组长度
    * Return:          int     >=0成功，<失败
    */
    int creatBiTree(DT* array,int size);
    void preOrder(void (*visit)(DT ,int ));
    void preOrder_stack(void (*visit)(DT ,int ));
    void levelOrder(void (*visit)(DT ));

};


template<class DT>
BiNode<DT>* creatBiTree_M(const DT *array, int size, int index) {
    int l=2*index+1,r=2*index+2;
    if(array==NULL||size<=0)
        return NULL;

    auto biTree = new BiNode<DT>();
    if(biTree==NULL)
        return NULL;

    biTree->data=array[index];
    if(l>size-1||array[l]==' '){
        biTree->lchild=NULL;
    } else{
        biTree->lchild=creatBiTree_M(array,size,l);
    }

    if(r>size-1||array[r]==' '){
        biTree->rchild=NULL;
    } else {
        biTree->rchild = creatBiTree_M(array, size, r);
    }
    return biTree;
}

template<class DT>
void preOrder_M(BiNode<DT> *t, int level, void (*visit)(DT, int)) {
    if(t==NULL)
        return;

    visit(t->data,level);
    preOrder_M(t->lchild,level+1,visit);
    preOrder_M(t->rchild,level+1,visit);
}

template<class DT>
void preOrder_stack_M(BiNode<DT> *t, int level, void (*visit)(DT, int)) {
    if(t==NULL)
        return;

    BiNode<DT> biTNode;
    Stack* stack = createStack(sizeof(BiNode<DT>));
    pushStack(stack,t);
    while (!isStackEmpty(stack)){
        popStack(stack,&biTNode);
        visit(biTNode.data,level++);
        if(biTNode.rchild!=NULL)
            pushStack(stack,biTNode.rchild);
        if(biTNode.lchild!=NULL)
            pushStack(stack,biTNode.lchild);
    }
}

template<class DT>
void levelOrder_M(BiNode<DT> *t, void (*visit)(DT)) {
    LQueue *lQueue = creatLQueue(sizeof(BiNode<DT>));

    visit(t->data);
    BiNode<DT> *node = (BiNode<DT> *)malloc(sizeof(BiNode<DT>));
    enLQueue(lQueue, t);
    while (!isLQueueEmpty(lQueue)){
        deLQueue(lQueue,node);
        if(node->lchild!=NULL){
            visit(node->lchild->data);
            enLQueue(lQueue,node->lchild);
        }
        if(node->rchild!=NULL){
            visit(node->rchild->data);
            enLQueue(lQueue,node->rchild);
        }
    }
    destroyLQueue(lQueue);
}

template<class DT>
void destroyBiTree_M(BiNode<DT> *t) {
    if(t==NULL)
        return;

    destroyBiTree_M(t->lchild);
    destroyBiTree_M(t->rchild);
    free(t);
}

template<class DT>
BiTree<DT>::BiTree() {
    tree = nullptr;
}
template<class DT>
BiTree<DT>::~BiTree() {
    destroyBiTree_M(tree);
}

template<class DT>
int BiTree<DT>::creatBiTree(DT *array, int size) {
    if(array==NULL||size<=0)
        return -1;
    tree = creatBiTree_M(array, size, 0);
    return 0;
}

template<class DT>
void BiTree<DT>::preOrder(void (*visit)(DT ,int )){
    preOrder_M(tree, 0, visit);
}

template<class DT>
void BiTree<DT>::levelOrder(void (*visit)(DT )){
    levelOrder_M(tree, visit);
//    visit(tree->data);
//    visit(tree->data);
}

template<class DT>
void BiTree<DT>::preOrder_stack(void (*visit)(DT ,int )){
    preOrder_stack_M(tree, 0, visit);
}


#endif //CORENOTE_BITREE_H
