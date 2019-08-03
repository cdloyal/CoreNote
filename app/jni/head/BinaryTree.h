/**
 * 作者：chenda
 * 时间：2019/7/26:10:41
 * 邮箱：
 * 说明：
 */

#ifndef CORENOTE_BINARYTREE_H
#define CORENOTE_BINARYTREE_H

#include <cstdio>

//下面是二叉树的二叉链表存储结构
//其实还可以用顺序存储方式的

typedef char BTNElemType;

typedef struct BiTNode{
    BTNElemType data;
    struct BiTNode *lchild,*rchild;
}BiTNode, *BinTree;

//由一个数组创建二叉数
BinTree creatBiTree(char* array,int length,int index);

//前序递归遍历二叉树,level当前层数,visit每次遍历到节点要做的事情
void preOrderTraverse(BinTree t,int level,void (*visit)(BTNElemType ,int ));
//前序非递归遍历二叉树
void preOrderTraverse_stack(BinTree t,int level,void (*visit)(BTNElemType ,int ));

//层序遍历二叉树,level当前层数,visit每次遍历到节点要做的事情
void levelOrderTraverse(BinTree t,void (*visit)(BTNElemType ));

void destroyBitTree(BinTree t);


#endif //CORENOTE_BINARYTREE_H
