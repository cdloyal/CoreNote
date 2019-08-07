//
// Created by chenda on 2019/7/28.
//

#ifndef CORENOTE_HAFFMAN_H
#define CORENOTE_HAFFMAN_H

#include "Merge-Sort.h"
/**
 * 哈夫曼树
 * */
//template<class T>
//struct HaffData {
//    T data;
//    int weight;
//
//    bool operator>(const HaffData &haffData);
//
//    bool operator<(const HaffData &haffData);
//
//    bool operator==(const HaffData &haffData);
//
//    char *haffCode;
//
//    HaffData *lchild,*rchild;
//};

template<class T>
struct HaffNode {
    T data;
    int weight;

    HaffNode();
    HaffNode(const HaffNode<T> &haffData);
    ~HaffNode();

    bool operator>(const HaffNode &haffData);

    bool operator<(const HaffNode &haffData);

    bool operator==(const HaffNode &haffData);

    bool operator<=(const HaffNode &haffData);
    bool operator>=(const HaffNode &haffData);

    HaffNode& operator=(const HaffNode &haffData);

    char *haffCode;

    HaffNode *lchild, *rchild;

};

/**
 * 内核链表  https://www.ibm.com/developerworks/cn/linux/kernel/l-chain/index.html
 * */
/**
 * 哈夫曼编码表
 * */
template<class T>
struct HaffTable {
    T data;
    char *code;
};

/**
 * 建哈夫曼树
 * */
template<class T>
//BiNode<HaffData<T>> *buildHaffTree(char *str, int size);

int buildHaffTree(char *str, int size,HaffNode<T> *&tree,LinkedList<HaffTable<T>> *&table);



/**
 * 哈夫曼编码
 * */
//template <class T>
//char* haffEncode(LinkedList<HaffTable<T>> tables,char *str, int size);


/**
 * 哈夫曼解码
 * */
template<class T>
char *haffDecode(BiTree<T> tree);


//=======================上面是声明，下面是定义============================//

//template<class T>
//bool HaffData<T>::operator>(const HaffData &haffData) {
//    return this->weight > haffData.weight;
//}
//
//template<class T>
//bool HaffData<T>::operator<(const HaffData &haffData) {
//    return this->weight < haffData.weight;
//}
//
//template<class T>
//bool HaffData<T>::operator==(const HaffData &haffData) {
//    return this->weight == haffData.weight;
//}

template<class T>
bool HaffNode<T>::operator>(const HaffNode &haffData) {
    return this->weight > haffData.weight;
}

template<class T>
bool HaffNode<T>::operator<(const HaffNode &haffData) {
    return this->weight < haffData.weight;
}

template<class T>
bool HaffNode<T>::operator==(const HaffNode &haffData) {
    return this->weight == haffData.weight;
}
template<class T>
bool HaffNode<T>::operator<=(const HaffNode &haffData) {
    return *this<haffData || *this==haffData;
}
template<class T>
bool HaffNode<T>::operator>=(const HaffNode &haffData) {
    return *this>haffData || *this==haffData;
}
template<class T>
HaffNode<T> &HaffNode<T>::operator=(const HaffNode &haffData) {
    this->rchild=haffData.rchild;
    this->lchild=haffData.lchild;
    this->data=haffData.data;
    this->weight=haffData.weight;
    this->haffCode=haffData.haffCode;
    return *this;
}

template<class T>
HaffNode<T>::HaffNode() {
    this->rchild=NULL;
    this->lchild=NULL;
    this->weight=0;
    this->haffCode=NULL;
}

template<class T>
HaffNode<T>::HaffNode(const HaffNode<T> &haffData) {
    this->rchild=haffData.rchild;
    this->lchild=haffData.lchild;
    this->data=haffData.data;
    this->weight=haffData.weight;
    this->haffCode=haffData.haffCode;
}

template<class T>
HaffNode<T>::~HaffNode() {
    this->rchild=NULL;
    this->lchild=NULL;
}





//template<class T>
//void visit(HaffData<T> data) {
//    LOGD("HaffTree levelOrder data=%c, weight=%d", data.data,data.weight);
//}

/**
 * 建哈夫曼树
 * */
//template<class T>
//BiNode<HaffData<T>> *buildHaffTree(char *str, int size) {
//    if(size<1)
//        return NULL;
//    char *p = str;
//    typedef typename LinkedList<HaffData<T>>::LLIterator It;
//    LinkedList<HaffData<T>> list;
//    while (size--) {
//        It it = list.iterator();
//        HaffData<T> dataStr;
//        dataStr.weight=-1;
//        while (it.hasNext()) {
//            dataStr = it.next();
//            if (dataStr.data == *p) {
//                it.remove();
//                dataStr.weight++;
//                list.insert(dataStr);
//                break;
//            }
//        }
//
//        if (dataStr.weight==-1 || dataStr.data != *p){
//            dataStr.data = *p;
//            dataStr.weight = 1;
//            list.insert(dataStr);
//        }
//
//        p++;
//    }
//有链表建一颗二叉树
//    BiNode<HaffData<T>> *tree = creatBiTree_M(&list);
//
//    LOGD("HaffTree buildHeapMerge before");
//    levelOrder_M(tree,visit);
//    buildHeapMerge(2, tree);
//    LOGD("HaffTree buildHeapMerge after");
//    levelOrder_M(tree, visit);

//构造优先队列
//    BiNode<HaffData<T>> *array;
//    int arraySize = list.toArray(array);
//    if(arraySize<=0 || array==NULL){
//        LOGD("error buildHaffTree ");
//        return NULL;
//    }
//
//    Heap<BiNode<HaffData<T>>> *heap = new Heap<BiNode<HaffData<T>>>(2,array,size);
//    heap->buildHeap();
//    heap->heapSort();
//
//    while (heap->size>1){
//        //构造哈夫曼树
//        BiNode<HaffData<T>> leftNode = heap->extractheapHead();
//        BiNode<HaffData<T>> rightNode = heap->extractheapHead();
//
//        BiNode<HaffData<T>> parentNode;
//        parentNode.data.weight = leftNode.data.weight+rightNode.data.weight;
//        parentNode.lchild = &leftNode;
//        parentNode.rchild = &rightNode;
//
//        heap->heapInsert(parentNode);
//    }
//
//    BiNode<HaffData<T>> tree = heap->extractheapHead();
//    delete heap;
//
//    return &tree;

//}

template<class T>
int buildHaffTree(char *str, int size,HaffNode<T> *&tree,LinkedList<HaffTable<T>> *&table){

    //建链表
    if (size<1 || str==NULL)
        return -1;

    table = new LinkedList<HaffTable<T>>();

    if(size == 1){
        tree = new HaffNode<T>();
        tree->data = str[0];
        tree->weight = 1;
        tree->haffCode=0;
        table->insert();
        return 0;
    }

    char *p = str;

    LinkedList<HaffNode<T>> list;
    while (size--) {
        HaffNode <T> dataStr;
        dataStr.weight = -1;
        for(int i=0;i<list.size;i++){
            dataStr = list.get(i);
            if (dataStr.data == *p) {
                dataStr.weight++;
                list.set(i,dataStr);
                break;
            }
        }

        if (dataStr.weight == -1 || dataStr.data != *p) {
            dataStr.data = *p;
            dataStr.weight = 1;
            list.insert(dataStr);
        }

        p++;
    }

    //链表转数组排序,归并排序
    HaffNode<T> *haffArray;
    int len = list.toArray(haffArray);
    mergeSort(haffArray,0,len-1);
    for(int i=0;i<len;i++){
        LOGD("HaffTree mergeSort aft data=%c, weight=%d", haffArray[i].data,haffArray[i].weight);
    }

    //建haffman树
    int sortIndex = 0;
    int head = 0;
    while (head<len-1){
        tree = new HaffNode<T>();
        HaffNode<T> *lNode = new HaffNode<T>();
        *lNode = haffArray[head];
        HaffNode<T> *rNode = new HaffNode<T>();
        *rNode = haffArray[++head];
        tree->weight = lNode->weight+rNode->weight;
        tree->lchild = lNode;
        tree->rchild = rNode;
        //重新排序
        haffArray[head]=*tree;
        sortIndex = head;
        while (sortIndex<len-1){
            if(haffArray[sortIndex]>haffArray[sortIndex+1]){
                HaffNode<T> tmp = haffArray[sortIndex];
                haffArray[sortIndex] = haffArray[sortIndex+1];
                haffArray[sortIndex+1] = tmp;
                sortIndex++;
            } else{
                break;
            }
        }
    }


    //建haffman表,层序遍历
    LQueue *lQueue = creatLQueue(sizeof(HaffNode<T>));

    HaffNode<T> *node = new HaffNode<T>();
    tree->haffCode = new char[1];
    tree->haffCode[0] = '\0';
    enLQueue(lQueue, tree);
    while (!isLQueueEmpty(lQueue)){
        deLQueue(lQueue,node);
        if(node->lchild!=NULL){
            node->lchild->haffCode = new char[strlen(node->haffCode)+1+1];
            node->lchild->haffCode[0] = '0';
            strcpy(node->lchild->haffCode+1,node->haffCode);
            enLQueue(lQueue,node->lchild);
        }
        if(node->rchild!=NULL){
            node->rchild->haffCode = new char[strlen(node->haffCode)+1+1];
            node->rchild->haffCode[0] = '1';
            strcpy(node->lchild->haffCode+1,node->haffCode);
            enLQueue(lQueue,node->rchild);
        }
        if(node->lchild==NULL && node->rchild==NULL){

        }
    }
    delete node;
    destroyLQueue(lQueue);


}


/**
 * 哈夫曼编码
 * */
template<class T>
char *haffEncode(LinkedList<HaffTable<T>> tables, char *str, int size);


/**
 * 哈夫曼解码
 * */
template<class T>
char *haffDecode(BiTree<T> tree);


#endif //CORENOTE_HAFFMAN_H
