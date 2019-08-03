#include "HeapSort_PriorityQueue.h"
//
// Created by chenda on 2019/7/20.
//

/**
 * 堆、堆排序、优先队列
 *
 *
 * 堆：进似完全二叉树，除了最底层外，该树完全充满。顺序存储的特性就是数组元素连续
 *      A<=A.heap-size<=A.length
 *      A.heap-size ： 堆的有效元素
 *
 *  1  2  3  4  5  6  7  8  9  10                    2  3  4  5  6  7  8  9  10
 *  3  6  7  2  3  1  4  8  7  9                     6  7  2  3  1  4  8  7  9
 *
 *
 *                  1                                            2
 *             2        3                                   3         4
 *          4    5   6     7                             5    6    7     8
 *        8  9 10                                      9  10
 *
 * 最大堆：除根节点外的所有节点A[PARENT(i)]>=A[i]   例如:A[2]>=A[4]&&A[2]>=A[5]，node.data>=node.lchild&&node.data.rchild
 * 最小堆：A[PARENT(i)]=<A[i]
 *
 * 堆排序原理：最大堆，node.data>=node.lchild&&node.data.rchild,树的最大值在根节点，
 *             排序，根节点出来rootNode，最后一个节点替代根节点lastNode.lchild=rootNode.lchild...
 *             重新递归建最大堆，建好堆重复取根结点
 *
 * 弄清除两个概念：
 * 树的下标与数组原来的下标
 * Left(i)=i*2; Right(i)=i*2+1;Parent(i)=i/2
 * 树的叶节点：A[n/2+1 ... n]
 *
 * 所以一个数组建成一颗树  A[start ~ start+size-1]
 * start->1;j->i=j-(start-1)
 *          i->j=i+(start-1)
 * llleft(j)=Left(j-(start-1)) +(start-1) = (j-(start-1))*2 +(start-1) = 2j-(start-1)
 * rright(j)=Right(j-(start-1)) +(start-1) = (j-(start-1))*2+1 +(start-1) = 2j-(start-1)+1
 * Parent(j)=(j-(start-1))/2 +(start-1) = (j+(start-1))/2
 * 树的叶节点：A[n/2+1 ... n]  (j-(start-1))/2+1+(start-1)
 *
 * 建堆：
 *
 *  输入：无序数组A
 *  输出：数组A满足最大堆性质
 *
 *  BUILD_MAX_HEAP(A)
 *      for i   n/2-1 to 0        从底层往上建，
 *          MAX_HEAPIFY(A,i)      //从底层往上建，第i-1以下的节点已经建好堆
 *                                //第i的节点维持最大性质
 *
 * 维护最大堆性质
 *  输入：数组A,节点i。输入特点：第i-1以下的节点已经建好堆
 *  输出：数组A节点i满足最大堆性质
 *
 *  MAX_HEAPIFY(A,A.heap-size,i)
 *      l=Left(i)
 *      r=Right(i)
 *      max=i
 *      if(l<=A.heap-size && A[i]<A[l])
 *          max=l
 *      if(r<=A.heap-size && A[i]<A[r])
 *          max=r
 *      if(max==i)
 *          continue;
 *      if(max==l || max==r)
 *          tmp=A[i]
 *          A[i]=A[max]
 *          A[max]=tmp;
 *          MAX_HEAPIFY(A,max)      //这里是用了递归，递归和分治还是有些区别
 *
 * 这里能用递归吗？加入可以用递归
 *  输入：无序数组A
 *  输出：数组A满足最大堆性质
 *
 *  分解：无序树A，分成两个子树
 *  解决：两个子树递归调用。分解最小子问题，叶子，返回；
 *  归并：两个满足最大堆性质的子树合并成一个完整的满足最大堆性质的数组A
 *
 *  归并的函数：MAX_HEAPIFY(A,i)？MAX_HEAPIFY(A,i)的输入特点：第i-1以下的节点已经建好堆
 *  两个递归函数的
 *
 *
 * 堆排序：
 *  上面已经建好堆。根据堆的特点，堆的最大元素总在根节点A[1]，通过它与A[n]替换，我们可以
 *  将该元素放到正确位置;替换后，我们需要重新建堆
 *
 *  输入：无序数组A
 *  输出：排好序的数组
 *
 *  HEAPSORT(A,size)
 *      BUILD_MAX_HEAP(A)
 *      tmpsize = size
 *      for i   1 to tmpsize-1
 *          tmp=A[0]
 *          A[0]=A[size-1]
 *          A[size-1]=tmp
 *          size--
 *          MAX_HEAPIFY(A,size-1,0)
 *
 *
 *  优先队列：用来维护由一组元素构成的集合S的数据结构，其中每个元素都有一个相关的值,
 *            称为关键字Key。
 *  优先队列的应用之一，线程调度，最大优先队列记录将要执行的各个线程及它们之间的相对优先级
 *  当一个作业完成或者被中断后，调度器从最大优先队列选出优先级最高的作业来执行。
 *
 *  MAXIMUN(S)              返回最大关键字的元素
 *  EXTRACT_MAX(S)          去掉并返回最大关键字的元素
 *  INCREASE_KEY(S，x，k)   重置元素x的key值，新KEY要比原来的大
 *  INSERT(S,x)             把元素插入到集合S中
 * */

typedef struct Operation{
    void (*assign)(void *src, void *&dest);   //赋值操作,src原值，dest目标值
    bool (*greater)(void *a, void *b);       //大于操作,a>b?
}Operation;

//维持最大堆性质
static void maxHeap(int *A,int size,int i){
    int tmp,l=2*i+1,r=2*i+2,max=i;
    if(l<=size-1 &&  A[max]<A[l])
        max=l;
    if(r<=size-1 &&  A[max]<A[r])
        max=r;
    if(max!=i){
        tmp=A[i];
        A[i]=A[max];
        A[max]=tmp;
        maxHeap(A,size,max);
    }
}

//递归法建堆
void buildMaxHeapbyMerge(int *A,int size,int i){
    int l=2*i+1,r=2*i+2;
    if(l>size-1)        //不存在子节点，叶子
        return;
    if(l<=size-1)       //存在左子数
        buildMaxHeapbyMerge(A,size,l);
    if(r<=size-1)       //存在右子树
        buildMaxHeapbyMerge(A,size,r);
    maxHeap(A,size,i);
}

//非递归法建堆
void buildMaxHeap(int *A,int size){
    for (int i=(size+1)/2;i>=0;i--){     //(size-(start-1))/2+1+(start-1) =  (size+1)/2
        maxHeap(A,size,i);
    }
}

//排序
void maxHeapSort(int *A, int size){

    buildMaxHeap(A,size);
    int tmpSize = size;
    for(int i=1;i<tmpSize;i++){
        int tmp=A[0];
        A[0]=A[size-1];
        A[size-1]=tmp;
        size--;
        maxHeap(A,size,0);
    }
}

//返回最大值
int maxHeapMaximum(int *A){
    return A[0];
}
//将最大值取出
int extractMaxHeap(int *A, int *size,int *maxValue){
    if (*size < 1)
        return -1;
    *maxValue = A[0];

    A[0] = A[*size-1] ;
    (*size)--;

    maxHeap(A,*size,0);
    return 0;
}
//改变其中一个值
int heapIncreaseKey(int *A,int i,int key){
    if(key<A[i])
        return -1;

    A[i]=key;
    while(i>0 && A[(i-1)/2]<A[i]){  //(j+(start-1))/2
        int tmp=A[i];
        A[i]=A[(i-1)/2];
        A[(i-1)/2]=tmp;
        i = (i-1)/2;
    }

    return 0;
}
//插入一个值
void heapInsert(int *A,int size,int i){
    A[size]=i-1;
    size++;
    heapIncreaseKey(A,size-1,i);
}








