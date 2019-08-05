//
// Created by chenda on 2019/7/28.
//

#ifndef CORENOTE_HAFFMAN_H
#define CORENOTE_HAFFMAN_H


/**
 * 哈夫曼树
 * */
template <class T>
struct HaffData{
    T data;
    int weight;
    bool operator>(const HaffData &haffData);
    bool operator<(const HaffData &haffData);
    bool operator==(const HaffData &haffData);
    char *haffCode;
};

/**
 * 哈夫曼编码表
 * */
template <class T>
struct HaffTable{
    T data;
    char *code;
};

/**
 * 建哈夫曼树
 * */
template <class T>
BiNode<HaffData<T>>* buildHaffTree(char *str, int size);

/**
 * 建哈夫曼表
 * */
//template <class T>
//LinkedList<HaffTable<T>> buildHaffTable(BiTree<T> tree);


/**
 * 哈夫曼编码
 * */
//template <class T>
//char* haffEncode(LinkedList<HaffTable<T>> tables,char *str, int size);


/**
 * 哈夫曼解码
 * */
template <class T>
char* haffDecode(BiTree<T> tree);


//=======================上面是声明，下面是定义============================//

template<class T>
bool HaffData<T>::operator>(const HaffData &haffData) {
    return this->weight>haffData.weight;
}

template<class T>
bool HaffData<T>::operator<(const HaffData &haffData) {
    return this->weight<haffData.weight;
}
template<class T>
bool HaffData<T>::operator==(const HaffData &haffData) {
    return this->weight==haffData.weight;
}

/**
 * 建哈夫曼树
 * */
template <class T>
BiNode<HaffData<T>>* buildHaffTree(char *str, int size){
    char *p = str;
    typedef typename LinkedList<HaffData<T>>::LLIterator It;
    LinkedList<HaffData<T>> list;
    It it = list.iterator();
    while(size--){
        HaffData<T> dataStr = it.next();
        if(it.hasNext() && dataStr.data==*p){
            dataStr.weight++;
        } else{
            HaffData<T> haffData;
            haffData.data = *p;
            haffData.weight=1;
            list.insert(haffData);
        }
        p++;
    }

    //有链表建一颗二叉树
    BiNode<HaffData<T>>*  tree = creatBiTree_M(list);

//    //构造优先队列
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
}

/**
 * 建哈夫曼表
 * */
template <class T>
LinkedList<HaffTable<T>> buildHaffTable(BiTree<T> tree);


/**
 * 哈夫曼编码
 * */
template <class T>
char* haffEncode(LinkedList<HaffTable<T>> tables,char *str, int size);


/**
 * 哈夫曼解码
 * */
template <class T>
char* haffDecode(BiTree<T> tree);


#endif //CORENOTE_HAFFMAN_H
