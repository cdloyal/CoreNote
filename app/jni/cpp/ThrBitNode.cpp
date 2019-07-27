#include <cstdio>
#include <cstdlib>
#include <log.h>
#include "ThrBitNode.h"
//
// Created by chenda on 2019/7/27.
//

/**
 *
 * https://blog.csdn.net/u014492609/article/details/40477795
 *
 * 线索二叉树
 *
 * n个节点的二叉树，有2n个指针，非空链域为n-1指向左右孩子，空链域有n+1个
 * 用这些空链域指向该节点的直接前驱或者后继，称为线索。
 *
 * p->lchild为空，则存放指向中序遍历序列中该节点的前驱节点，该节点称为p的中序前驱。
 * p->rchild为空，则存放指向中序遍历序列中该节点的后继节点，该节点称为p的中序后继。
 *
 * 需要tag去标记child指向的是指针还是线索
 *
 *      lchild ltag data rtag rchild
 *
 * 非线索二叉树中序遍历：
 *  对于节点i的后继
 *       1、节点是根节点： 有右子树,后继=右子树的；无右子树，后继=NULL
 *       2、节点i在左子树：有右子树,后继=右子树；无右子树，后继=NULL
 *       3、节点i在右子树：有右子树,后继=右子树；无右子树，后继=父节点
 *
 * 有了线索二叉树之后的中序遍历：向链表一样遍历
 * 找到第一个节点最深左子树
 * 当前节点i的后继：1、t.rtag==Thread,后继=p->rchild
 *                  2、t.rtag==Link,后继=右子树的最深左子树
 * */

static ThrBiTree preThrBitNode;

static ThrBiTree creatThrBiTree(TElemType *array, int length, int index) {

    int l = 2 * index + 1, r = 2 * index + 2;
    if (array == NULL || length <= 0)
        return NULL;

    auto biTree = (struct ThrBitNode *) malloc(sizeof(struct ThrBitNode));
    if (biTree == NULL)
        return NULL;

    biTree->data = array[index];
    biTree->ltag = Link;
    biTree->rtag = Link;
    if (l > length - 1 || array[l] == ' ') {
        biTree->lchild = NULL;
    } else {
        biTree->lchild = creatThrBiTree(array, length, l);
    }

    if (r > length - 1 || array[r] == ' ') {
        biTree->rchild = NULL;
    } else {
        biTree->rchild = creatThrBiTree(array, length, r);
    }

    preThrBitNode = NULL;
    return biTree;
}

void inOrderTraverse(ThrBiTree t, int level, void (*visit)(TElemType, int)) {
    if (t == NULL)
        return;

    inOrderTraverse(t->lchild, level + 1, visit);
    visit(t->data, level);
    inOrderTraverse(t->rchild, level + 1, visit);
}

//中序遍历进行中序线索化
static void inThreading(ThrBiTree t) {
    if (t == NULL)
        return;
    inThreading(t->lchild);

    //p->lchild为空，则存放指向中序遍历序列中该节点的前驱节点，该节点称为p的中序前驱。
    //p->rchild为空，则存放指向中序遍历序列中该节点的后继节点，该节点称为p的中序后继。
    if (t->lchild == NULL) {
        t->ltag = Thread;
        t->lchild = preThrBitNode;
    }
    if (preThrBitNode->rchild == NULL) {    //
        preThrBitNode->rtag = Thread;
        preThrBitNode->rchild = t;
    }
    preThrBitNode = t;
    inThreading(t->rchild);
}

//建立头节点，中序线索二叉树
int inOrderThread_Head(ThrBiTree *t, TElemType *array, int length, int index) {

    (*t) = (ThrBiTree) malloc(sizeof(struct ThrBitNode));
    if (*t == NULL) {
        LOGD("create ThrBiTree head error");
        return -1;
    }
    (*t)->rtag=Thread;
    (*t)->rchild=NULL;

    ThrBiTree thrBiTree = creatThrBiTree(array, length, index);
    if (thrBiTree == NULL) {
        (*t)->ltag = Link;
        (*t)->lchild = *t;
    } else {
        preThrBitNode = *t;
        (*t)->ltag = Link;
        (*t)->lchild = thrBiTree;
        inThreading(thrBiTree);
        preThrBitNode->rtag = Thread;
        preThrBitNode->rchild = *t;
        (*t)->rtag = Thread;
        (*t)->rchild = preThrBitNode;
    }
    return 0;
}

void inOrderTraverse_The(ThrBiTree t, void (*visit)(TElemType)) {
    /**
     * 有了线索二叉树之后的中序遍历：向链表一样遍历
     * 找到第一个节点最深左子树
     * 当前节点i的后继：1、t.rtag==Thread,后继=p->rchild
     *                  2、t.rtag==Link,后继=右子树(p->rchild)的最深左子树
     *
     * */

    ThrBiTree p=t->lchild;
    while (p!=t){
        while (p->ltag==Link){
            p=p->lchild;
        }
        visit(p->data);
        while(p->rtag==Thread && p->rchild!=t){
            p=p->rchild;
            visit(p->data);
        }
        p=p->rchild;
    }

}

