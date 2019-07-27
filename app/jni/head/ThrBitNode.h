//
// Created by chenda on 2019/7/27.
//

#ifndef CORENOTE_THRBINODE_H
#define CORENOTE_THRBINODE_H

typedef char TElemType;

typedef enum PointerTag {Link,Thread};

typedef struct ThrBitNode{
    TElemType data;
    struct ThrBitNode *lchild,*rchild;
    PointerTag ltag,rtag;
}ThrBitNode,*ThrBiTree;

//建立头节点，中序线索二叉树
int inOrderThread_Head(ThrBiTree *t,TElemType *array, int length, int index);

//中序遍历线索二叉树
void inOrderTraverse_The(ThrBiTree t,void (*visit)(TElemType));



#endif //CORENOTE_THRBINODE_H
