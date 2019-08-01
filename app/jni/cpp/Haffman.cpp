//
// Created by chenda on 2019/7/28.
//
#include "Haffman.h"

/**
 * 哈夫曼编码
 *
 * 带权的二叉树:节点之间连线相关的数叫权
 * 结点的路径长度：从根结点到该结点的路径上的连接数
 * 树的路径长度：树中每个结点的路径长度之和
 * 节点带权路径长度：结点的路径长度 * 权
 * 树的带权路径长度（WPL）：树中每个结点的节点带权路径长度之和
 *
 * WPL越小，说明构造出来的二叉树性能越优
 *
 * 定长编码、变长编码、前缀码
 *
 * build a priority queue
 * build a huffmanTree
 * build a huffmanTable
 * encode
 * decode
 *
 *
 * */


template <class T>
struct HaffNode{
    T data;
    int weight;
    char *haffCode;
    struct HaffNode *left,*right;
};

template <class T>
class Haffman{
public:
    char* haffEncode();
    char* haffDecode();
};
