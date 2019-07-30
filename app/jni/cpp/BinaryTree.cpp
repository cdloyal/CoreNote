#include <cstdlib>
#include <Stack.h>
#include "BinaryTree.h"
/**
 * 二叉树的5种形态：
 *  空树
 *  只有根节点
 *  只有根节点和左子树
 *  只有根节点和右子树
 *  有根节点和左右子树
 *
 *  斜树：全部子树都在同一边
 *  满二叉树：所有分支节点都存在左子树和右子树，并且所有叶子都在同一层上。除最后一层无任何子节点外，每一层上的所有结点都有两个子结点二叉树。
 *  完全二叉树：叶节点只能出现在最下层和次下层，并且最下面一层的结点都集中在该层最左边的若干位置的二叉树
 *
 *  满二叉树:非叶节点的度都是2
 *
 * 性质：
 *  在二叉树的第i层上最多有2^(i-1)个节点
 *  深度为k的二叉树最多有2^k-1
 *
 *  终端结点(叶子)数为n0,度为2的节点数为n2,则n0=n2+1
 *      推到：假设度为1的节点数为n1，总节点数n=n0+n1+n2
 *            总连接总是为n-1,并且等于2*n2+n1
 *            合并：2*n2+n1 = n0+n1+n2 -1 ==>n0=n2+1
 *
 *  具有n个节点的完全二叉树的深度为  [log2(n)] + 1,   [log2(n)]取下限
 *      满二叉树总节点n=2^k-1，深度k=log2(n+1)
 *      完全二叉树倒数第二层节点数=2^(k-1)-1
 *      完全二叉树   2^(k-1)-1 < n <= 2^k-1
 *                   2^(k-1)  < n+1 <= 2^k
 *
 *                      k-1  <=  log2(n+1) < k
 *
 *  完全二叉树的节点按层编号，对任意节点i的性质
 *      -如果节点i=1;则节点i是二叉树的根，无双亲；
 *       如果i>1,则其双亲节点(int)i/2，(int)表示取下限
 *      -2i是左节点，2i+1是有节点
 *
 *  typedef struct BiTNode{
 *      ElemType data;
 *      struct BiTNode *lchild,rchild;
 *  }BiTNode, *BiTree;
 *
 * ABCDEFGHI   J
 *              A
 *        B          C
 *    D      E    F     G
 *  H   I           J
 * 前序遍历：若二叉树为空，则空操作返回，否则先访问根节点，然后前序遍历左子树，再前序遍历右子树.ABDHIECFJG
 * 中序遍历：若二叉树为空，则空操作返回，否则先中序遍历左子树，然后访问根节点，再中序遍历右子树.HDIBEAFJCG
 * 后序遍历：若二叉树为空，则空操作返回，否则从左到右先叶子后节点的方式遍历访问左右子树，最后访问根节点。HIDEBJFGCA
 * 层序遍历：
 *
 * */

BiTree creatBiTree(char* array,int length,int index){

    int l=2*index+1,r=2*index+2;
    if(array==NULL||length<=0)
        return NULL;

    auto biTree = (struct BiTNode *)malloc(sizeof(struct BiTNode));
    if(biTree==NULL)
        return NULL;

    biTree->data=array[index];
    if(l>length-1||array[l]==' '){
        biTree->lchild=NULL;
    } else{
        biTree->lchild=creatBiTree(array,length,l);
    }

    if(r>length-1||array[r]==' '){
        biTree->rchild=NULL;
    } else{
        biTree->rchild=creatBiTree(array,length,r);
    }
    return biTree;
}

void preOrderTraverse(BiTree t,int level,void (*visit)(BTNElemType ,int )){
    if(t==NULL)
        return;

    visit(t->data,level);
    preOrderTraverse(t->lchild,level+1,visit);
    preOrderTraverse(t->rchild,level+1,visit);
}
void preOrderTraverse_stack(BiTree t,int level,void (*visit)(BTNElemType ,int )){
    if(t==NULL)
        return;

    BiTNode biTNode;
    Stack* stack = createStack(sizeof(struct BiTNode));
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
//层序遍历二叉树,level当前层数,visit每次遍历到节点要做的事情
void levelOrderTraverse(BiTree t,void (*visit)(BTNElemType )){


}

void destroyBitTree(BiTree t){
    if(t==NULL)
        return;

    destroyBitTree(t->lchild);
    destroyBitTree(t->rchild);
    free(t);
}

