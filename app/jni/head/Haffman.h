//
// Created by chenda on 2019/7/28.
//

#ifndef CORENOTE_HAFFMAN_H
#define CORENOTE_HAFFMAN_H


template <class T>
struct HaffNode{
    char *haffCode;
    struct HaffNode *left,*right;
};

/**
 * 存储数据和权值的结构体
 * 还没学hash表，用一个链表存储
 * */
template <class T>
struct HaffData{
    T data;
    int weight;
};

template <class T>
struct HaffTableData{
    T data;
    char *code;
};

/**
 * 创建存储数据和权值的结构体链表
 * */
template <class T>
LinkedList<HaffData<T>> buildHaffData(char *str, int size);

/**
 * 建哈夫曼树
 * */
template <class T>
BiTree<HaffData<T>> buildHaffTree(LinkedList<HaffData<T>> listData);

/**
 * 建哈夫曼表
 * */
template <class T>
LinkedList<HaffTableData<T>> buildHaffTable(BiTree<HaffData<T>> tree);


/**
 * 哈夫曼编码
 * */
template <class T>
char* haffEncode(LinkedList<HaffTableData<T>> tables,char *str, int size);


/**
 * 哈夫曼解码
 * */
template <class T>
char* haffDecode(BiTree<HaffData<T>> tree);


#endif //CORENOTE_HAFFMAN_H
