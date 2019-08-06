/**
 * 作者：chenda
 * 时间：2019/8/2:15:39
 * 邮箱：
 * 说明：
 */

#ifndef CORENOTE_BITREE_H
#define CORENOTE_BITREE_H

#include "Stack.h"
#include "LQueue.h"

template <class DT>
struct BiNode{
    DT data;
    BiNode *lchild,*rchild;
};

template <class DT>
BiNode<DT>* createBiTreeNode_M(DT &newData);

template <class DT>
BiNode<DT>* creatBiTree_M(const DT *array, int size, int index);
template <class DT>
BiNode<DT>*  creatBiTree_M(LinkedList<DT> *list);

/**
 * 二叉搜索树插入
 * */
template <class DT>
void insertBiTree_M(BiNode<DT> *&tree, DT &newData);

//前序递归遍历二叉树,level当前层数,visit每次遍历到节点要做的事情
template <class DT>
void preOrder_M(BiNode<DT>* t,int level,void (*visit)(DT ,int ));

//前序非递归遍历二叉树
template <class DT>
void preOrder_stack_M(BiNode<DT>* t,int level,void (*visit)(DT ,int ));

//层序遍历二叉树,level当前层数,visit每次遍历到节点要做的事情
template <class DT>
void levelOrder_M(BiNode<DT>* t,void (*visit)(DT ));

/*
  * Description:     维持堆属性建堆
  * Return:          void
  */
template<class DT>
static void heap_M(int flag,BiNode<DT>* tree);

/*
    * Description:     二叉树转堆,二叉树要完全二叉树
    * Input:           flag     1:建最大堆，2：建最小堆
    *                  array    数据数组，建堆会改变传进来的数组
    *                  size     数组长度
    * Return:
    */
template<class DT>
void buildHeapMerge(int flag,BiNode<DT>* tree);


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
    int creatBiTree(LinkedList<DT> *list);
    void preOrder(void (*visit)(DT ,int ));
    void preOrder_stack(void (*visit)(DT ,int ));
    void levelOrder(void (*visit)(DT ));
    void heap(int flag);
};


template <class DT>
BiNode<DT>* createBiTreeNode_M(DT &newData){
    BiNode<DT>* biNode = new BiNode<DT>();
    biNode->data = newData;
    biNode->lchild=NULL;
    biNode->rchild=NULL;
    return biNode;
}

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
BiNode<DT>*  creatBiTree_M(LinkedList<DT> *list){
    LQueue* queue = creatLQueue(sizeof(BiNode<DT>*));
    typedef typename LinkedList<DT>::LLIterator It;
    It it = list->iterator();
    if(!it.hasNext())
        return NULL;
    DT dt = it.next();
    BiNode<DT> *tree = (BiNode<DT> *)malloc(sizeof(BiNode<DT>));
    tree->data = dt;
    tree->rchild = NULL;
    tree->lchild = NULL;

    BiNode<DT> *child;
    BiNode<DT> *node;
    enLQueue(queue,&tree);
    while (it.hasNext()){
        deLQueue(queue,&node);
        child = (BiNode<DT> *)malloc(sizeof(BiNode<DT>));
        child->data = it.next();
        child->rchild = NULL;
        child->lchild = NULL;
        node->lchild = child;
        enLQueue(queue,&child);
        if(it.hasNext()){
            child = (BiNode<DT> *)malloc(sizeof(BiNode<DT>));
            child->data = it.next();
            child->rchild = NULL;
            child->lchild = NULL;
            node->rchild = child;
            enLQueue(queue,&child);
        }
    }
    destroyLQueue(queue);
    return tree;
}

template <class DT>
void insertBiTree_M(BiNode<DT> *&tree, DT &newData){
    BiNode<DT> *parent = tree;
    BiNode<DT> *p = tree;
    if(tree==NULL){
        tree = createBiTreeNode_M(newData);
        return ;
    }
    while (p){
        parent = p;
        if(tree->data>newData){
            p = tree->lchild;
        } else{
            p = tree->rchild;
        }
    }
    BiNode<DT> *node = createBiTreeNode_M(newData);
    if(parent->data>newData){
        parent->lchild = node;
    } else{
        parent->rchild = node;
    }
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

/*
  * Description:     维持堆属性建堆
  * Return:          void
  */
template<class DT>
static void heap_M(int flag,BiNode<DT>* tree) {
    BiNode<DT>* max = tree;
    BiNode<DT>* l = tree->lchild;
    BiNode<DT>* r = tree->rchild;
    DT tmp;
    if(flag==1){
        if(l!=NULL &&  max->data<l->data)
            max=l;
        if(r!=NULL &&  max->data<r->data)
            max=r;
    } else{
        if(l!=NULL &&  max->data>l->data)
            max=l;
        if(r!=NULL &&  max->data>r->data)
            max=r;
    }
    if(max!=tree){
        tmp=tree->data;
        tree->data=max->data;
        max->data=tmp;
        heap_M(flag,max);
    }
}

/*
    * Description:     二叉树转堆,二叉树要完全二叉树
    * Input:           flag     1:建最大堆，2：建最小堆
    *                  array    数据数组，建堆会改变传进来的数组
    *                  size     数组长度
    * Return:
    */
template<class DT>
void buildHeapMerge(int flag,BiNode<DT>* tree) {
    if(tree->lchild==NULL)        //不存在子节点，叶子
        return;
    if(tree->lchild!=NULL)       //存在左子数
        buildHeapMerge(flag,tree->lchild);
    if(tree->rchild!=NULL)       //存在右子树
        buildHeapMerge(flag,tree->rchild);
    heap_M(flag,tree);
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
int BiTree<DT>::creatBiTree(LinkedList<DT> *list) {
    tree = creatBiTree_M(list);
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

template<class DT>
void BiTree<DT>::heap(int flag) {
    heap_M(flag,tree);
}




#endif //CORENOTE_BITREE_H
