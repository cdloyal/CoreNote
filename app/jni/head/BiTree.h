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
#include <stack>

template <class DT>
struct BiNode{
    DT data;
    int height; //二叉平衡树用到
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

/**
 * 二叉搜索树删除
 * */
template <class DT>
int deleteBiTree_M(BiNode<DT> *&tree, DT &deleteData);

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
int getHeigh(BiNode<DT> *node){
    if(node==NULL)
        return 0;
    return node->height;
}

template <class DT>
void updateAVLHeigh(BiNode<DT> *node){
    node->height = getHeigh(node->lchild)>=getHeigh(node->rchild)?getHeigh(node->lchild)+1:getHeigh(node->rchild)+1;
}

template <class DT>
void leftRotation(BiNode<DT> *&tree){
    BiNode<DT> *tmp = tree->rchild;
    tree->rchild = tmp->lchild;
    tmp->lchild=tree;
    updateAVLHeigh(tree);
    updateAVLHeigh(tmp);
    tree=tmp;
}

template <class DT>
void rightRotation(BiNode<DT> *&tree){
    BiNode<DT> *tmp = tree->lchild;
    tree->lchild = tmp->rchild;
    tmp->rchild=tree;
    updateAVLHeigh(tree);
    updateAVLHeigh(tmp);
    tree=tmp;
}

template <class DT>
void insertAVL_M(BiNode<DT> *&tree, DT &newData){
    /**
     * 平衡二叉树
     *  要么是空树；要么它的左子树和右子树都是平衡二叉排序树，且左右子树的深度相差1
     *
     * 二叉查找树和平衡二叉树的中序遍历都是有序的
     *
     * 平衡因子BF：二叉树上结点上的左子树深度减去右子树的深度
     * 平衡二叉树所有结点的平衡因子小于等于1的树
     *
     * https://blog.csdn.net/qq_25940921/article/details/82183093
     * https://www.cnblogs.com/sgatbl/p/9426394.html
     *
     * 输入：平衡二叉树tree，要插入的数据newData
     * 输出：插入新的结点得到新的平衡二叉树
     *
     * 分解：根结点、平衡二叉左子树、平衡二叉右子树
     * 解决：根结点和要插入数据的大小判断，递归调用，得到新的平衡二叉子树。退出条件，tree==null，插入新的结点
     * 合并：判断左右子树的深度，进行旋转
     *
     * 实际应用要讨论相同元素问题,可以用一个freq结点变量记录
     *
     * 平衡二叉树删除结点比较麻烦，后面后中和谐更好的红黑树
     * */

    if(tree==NULL){
        tree = new BiNode<DT>();
        tree->lchild=NULL;
        tree->rchild=NULL;
        tree->data=newData;
        tree->height=1;
        return;
    }
    if(tree->data>newData){
        insertAVL_M(tree->lchild,newData);
    } else if(tree->data<newData){
        insertAVL_M(tree->rchild,newData);
    } else{
        LOGD("已经存在新插入的结点");
        return;
    }

    //更新自己的高度
    updateAVLHeigh(tree);
    //判断左右子树高度
    if(getHeigh(tree->lchild)-getHeigh(tree->rchild)==2){
        //判断左左，还是左右
        BiNode<DT> *l = tree->lchild;
        if(getHeigh(l->lchild)-getHeigh(l->rchild)==1){
            //左左:右旋
            rightRotation(tree);
        }else{
            //左右：左旋右旋
            leftRotation(tree->lchild);
            rightRotation(tree);
        }
    } else if(getHeigh(tree->rchild)-getHeigh(tree->lchild)==2){
        BiNode<DT> *r = tree->rchild;
        if(getHeigh(r->rchild)-getHeigh(r->lchild)==1){
            //右右：左旋
            leftRotation(tree);
        }else{
            //右左：右旋左旋
            rightRotation(tree->rchild);
            leftRotation(tree);
        }
    }

}

template <class DT>
void insertBiTree_M(BiNode<DT> *&tree, DT &newData){
    //实际应用要讨论相同元素问题
    BiNode<DT> *parent = tree;
    BiNode<DT> *p = tree;
    if(tree==NULL){
        tree = createBiTreeNode_M(newData);
        return ;
    }
    while (p){
        parent = p;
        if(parent->data>newData){
            p = parent->lchild;
        } else{
            p = parent->rchild;
        }
    }
    BiNode<DT> *node = createBiTreeNode_M(newData);
    if(parent->data>newData){
        parent->lchild = node;
    } else{
        parent->rchild = node;
    }
}

template <class DT>
int deleteBiTree_M(BiNode<DT> *&tree, DT &deleteData){
    /**
     * 根据二叉排序树性质：
     *  1、如果要删除的结点是叶子节点，直接删除
     *  2、如果要删除的结点只存在左子树或者右子树，删除结点后，将它的左子树或者右子树整个移动到删除结点的位置
     *  3、如果删除的结点存在左子树和右子树
     *      3-1 找到直接前驱（即左子树的最右边子树），如果直接前驱有左孩子，则将直接前驱代替要删除的结点，将直接前驱的左孩子代替直接前驱
     *      3-2 找到直接后继（即右子树的最左边子树），如果直接后继有右孩子，则将直接后继代替要删除的结点，将直接后继的右孩子代替直接前驱
     * */

    if(tree==NULL){
        LOGD("删除结点出错，二叉树为空");
        return -1;
    }

    //因为我们要删除结点，然后让父节点的结点指针指向新的结点
    //1、使用两个指针，一个指向父结点的指针node *father，一个指向要删除的结点指针node *child。这个就麻烦在要记录父结点的指针
    //                  father.child=newchild;  delete child;
    //2、要删除的结点指针    node **child = &father.child;
    //突然想到与其使用指针的指针操作前驱结点，不如用后继结点
    BiNode<DT> *tmp,*tmpTree=tree;
    BiNode<DT> **pre=&tmpTree,**curr=&tmpTree;

    //用栈进行中序遍历
    std::stack<BiNode<DT> **> stack;

    //中序遍历
    while ((*curr)!=NULL){
        stack.push(curr);
        curr = &(*curr)->lchild;
    }
    while (stack.size()!=0){
        curr = stack.top();
        stack.pop();
        //visit
        if((*curr)->data==deleteData){
            if((*curr)->lchild!=NULL && (*curr)->rchild!=NULL){
                (*curr)->data = (*pre)->data;
                tmp = *pre;
                *pre = (*pre)->lchild;
                free(tmp);
            } else if((*curr)->lchild!=NULL){
                tmp = *curr;
                *curr = (*curr)->lchild;
                free(tmp);
            } else if((*curr)->rchild!=NULL){
                tmp = *curr;
                *curr = (*curr)->rchild;
                free(tmp);
            } else{
            }
            return 0;
        }
        pre = curr;
        //end visit
        if((*curr)->rchild!=NULL){
            curr = &(*curr)->rchild;
            while ((*curr)!=NULL){
                stack.push(curr);
                curr = &(*curr)->lchild;
            }
        }
    }

    LOGD("删除结点出错，没找到结点");
    return -1;
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
