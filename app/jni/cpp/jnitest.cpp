#include <jni.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <InsertSort.h>
#include <ctime>
#include <Sqlist.h>
#include <DulLinklist.h>
#include "PrintUtils.h"
#include "log.h"
#include "Linklist_C.h"
#include "DivideConquer.h"
#include "QuickSort.h"
#include <Random.h>
#include <ThrBitNode.h>
#include <Stack.h>
#include <Graph_Aml.hpp>
#include <queue>
#include <LQueue.h>
#include <CTest.h>
#include <LinkedList.h>
#include <BiTree.h>
#include <Heap.h>
#include <Haffman.h>
#include <MergeSort.h>
#include "HeapSort_PriorityQueue.h"
#include "BinaryTree.h"
//
// Created by chenda on 2019/6/23.
//
#include "Graph_Ol.h"

extern "C"
JNIEXPORT void JNICALL
Java_cd_note_others_JniTest_cTest(JNIEnv *env, jclass type) {

    ctest();

}

int large(const void* a,const void* b){
    return (*(int*)a)>=(*(int*)b)?1:0;
}

extern "C"
JNIEXPORT jint JNICALL
Java_cd_note_others_JniTest_sqListTest(JNIEnv *env, jclass type) {

    printf("线性表顺序存储结构");
    fflush(stdout);
    LOGD("线性表顺序存储结构");
    ElemType e;
    SqList sqList;
    sqlistInit(&sqList);
    LOGD("sqList.length=%d,sqList.data[0]=%d",sqList.length,sqList.data[0]);
    int ret = sqlistInsert(&sqList, 1, 1);
    ret = sqlistGet(&sqList, 1, &e);
    LOGD("sqList.length=%d,sqlistGet(&sqList,1,&e)=%d",sqList.length,e);
    ret = sqlistInsert(&sqList, 1, 2);
    ret = sqlistGet(&sqList, 1, &e);
    LOGD("sqList.length=%d,sqlistGet(&sqList,1,&e)=%d",sqList.length,e);
    ret = sqlistDelete(&sqList, 1, &e);
    LOGD("sqList.length=%d,sqlistDelete(&sqList,1,&e)=%d",sqList.length,e);
    ret = sqlistGet(&sqList, 1, &e);
    LOGD("sqList.length=%d,sqlistGet(&sqList,1,&e)=%d",sqList.length,e);
    ret = sqlistDelete(&sqList, 1, &e);
    LOGD("sqList.length=%d,sqlistDelete(&sqList,1,&e)=%d",sqList.length,e);

    return 0;

}extern "C"
JNIEXPORT void JNICALL
Java_cd_note_others_JniTest_insertSortTest(JNIEnv *env, jclass type) {

    clock_t start,finish;
    int array[] = {3,1,6,7,3,1,0,9};
    char string[128];

    LOGD("--------insertSortTest--------");
    LOGD("array old:");
    intArray2String(array,sizeof(array)/ sizeof(int),string);
    LOGD("%s",string);

    start = clock();
    insertSort(array, sizeof(array)/ sizeof(int));
    finish = clock();

    LOGD("array new:");
    intArray2String(array,sizeof(array)/ sizeof(int),string);
    LOGD("%s",string);
    LOGD("insertSort time= %lf s",(double)(finish-start)/CLOCKS_PER_SEC);

}extern "C"
JNIEXPORT void JNICALL
Java_cd_note_others_JniTest_mergeSortTest(JNIEnv *env, jclass type) {

    int array[] = {1,6,7,3,1,0,9,2};
//    int array[] = {3,1,6,7,39,1,20,9,21};
    char string[128];

    LOGD("--------mergeSortTest--------");
    LOGD("array old:");
    intArray2String(array,sizeof(array)/ sizeof(int),string);
    LOGD("%s",string);

    insertSort(array, sizeof(array)/ sizeof(int));

    LOGD("array new:");
    intArray2String(array,sizeof(array)/ sizeof(int),string);
    LOGD("%s",string);


    int array1[] = {4,7,1,4,3,2};
    int *array2 = array1;
    merge_sort(array2,0,sizeof(array1)/ sizeof(int)-1);
    for(int i=0;i<sizeof(array1)/ sizeof(int);i++){
        LOGD("mergeSort  array1=%d,", array1[i]);
    }
}
void linkedListTest(){
    //抽象链表
    LinkedList<int> linkedList ;
    linkedList.insert(135);
    linkedList.insert(136);
    linkedList.insert(137);
    LinkedList<int>::LLIterator it =linkedList.iterator();
    while (it.hasNext()){
        LOGD("it.next() = %d",it.next());
    }
}
extern "C"
JNIEXPORT jint JNICALL
Java_cd_note_others_JniTest_linkListTest(JNIEnv *env, jclass type) {

    LinkList *list;
    ElemType e;
    int offset=0;
    char string[128];

    list = (LinkList *)malloc(sizeof(LinkList));

    linklistCreateTrail(list,10);
    LOGD("--------linkListTest--------");
    LOGD("old linkList:");
    for(int i=1; i<10;i++){
        linklistGet(list,i,&e);
        offset += sprintf(string+offset,"%d ",e);
    }
    string[offset]='\0';
    LOGD("%s",string);

    linklistInsert(list,5,5);
    linklistInsert(list,6,6);
    linklistInsert(list,8,8);
    linklistInsert(list,11,11);
    linklistDelete(list,6,&e);
    linklistDelete(list,12,&e);
    linklistDelete(list,11,&e);

    LOGD("new linkList:");
    for(int i=1; i<10;i++){
        linklistGet(list,i,&e);
        offset += sprintf(string+offset,"%d ",e);
    }
    string[offset]='\0';
    LOGD("%s",string);


    linklistClear(list);
    free(list);

    linkedListTest();

    LOGD("linkedListTest end");

    return 0;
}extern "C"
JNIEXPORT jint JNICALL
Java_cd_note_others_JniTest_dulLinkListTest(JNIEnv *env, jclass type) {

    char string[128];
    int offset = 0;
    int max = -1;
    int array[] = {1,9,4,2,64,5};
    List list;
    LOGD("--------dulLinkListTest--------");

    initList(&list, sizeof(int));
    for(int i:array)
        insertLast(list,&i,NULL);

    DlIterator iterator = getIterator(list,0);
    while (iterator!=list->head){
        int* data = (int*)getData(iterator);
        offset += sprintf(string+offset,"%d ",*data);
        iterator = iterator->next;
    }
    LOGD("initList = %s",string);

    getMax(list,0,list->length-1,large,&max);
    LOGD("max = %d",max);

    return 0;
}extern "C"
JNIEXPORT void JNICALL
Java_cd_note_others_JniTest_divideConquer(JNIEnv *env, jclass type) {

    int A[] = {13,  -3, -25,  20,  -3, -16, -23,  18,  20,  -7,   12,  -5, -22,  15,  -4,   7};
    int B[] = {-13,  -3, -25,  -20,  -3, -16, -23};
    int C[] = {13,  3, 25,  20,  3, 16, 23};

    int max,left,right;
    LOGD("--------divideConquer--------");

    findMaxSubArray(A, 0, sizeof(A)/ sizeof(int)-1, &max, &left, &right);
    LOGD("A[] max=%d,left=%d,right=%d,",max,left,right);

    findMaxSubArray(B, 0, sizeof(B)/ sizeof(int)-1, &max, &left, &right);
    LOGD("B[] max=%d,left=%d,right=%d,",max,left,right);

    findMaxSubArray(C, 0, sizeof(C)/ sizeof(int)-1, &max, &left, &right);
    LOGD("C[] max=%d,left=%d,right=%d,",max,left,right);
}extern "C"
JNIEXPORT void JNICALL
Java_cd_note_others_JniTest_quickSort(JNIEnv *env, jclass type) {
    char string[128];
    int A[] = {13,  -3, -25,  20,  -3, -16, -23,  18,  20,  -7,   12,  -5, -22,  15,  -4,   7};
    LOGD("quickSort array src:");
    intArray2String(A,sizeof(A)/ sizeof(int),string);
    LOGD("%s",string);

    quickSort(A,0, sizeof(A)/ sizeof(int)-1);

    LOGD("quickSort array new:");
    intArray2String(A,sizeof(A)/ sizeof(int),string);
    LOGD("%s",string);
}extern "C"
JNIEXPORT void JNICALL
Java_cd_note_others_JniTest_randomSort(JNIEnv *env, jclass type) {
    char string[128];
    int A[] = {1,2,3,4,5,6,7,8,9,10};
    LOGD("randomSort array src:");
    intArray2String(A,sizeof(A)/ sizeof(int),string);
    LOGD("%s",string);

    randomize_in_place(A,0, sizeof(A)/ sizeof(int));

    LOGD("randomSort array new:");
    intArray2String(A,sizeof(A)/ sizeof(int),string);
    LOGD("%s",string);
}

extern "C"
JNIEXPORT void JNICALL
Java_cd_note_others_JniTest_buildMaxHeapbyMerge(JNIEnv *env, jclass type) {
    char string[128];
//    int A[] = {13,  -3, -25,  20,  -3, -16, -23,  18,  20,  -7,   12,  -5, -22,  15,  -4,   40};
    int A[] = {4,7,1,4,3,2};
    LOGD("buildMaxHeapbyMerge array src:");
    intArray2String(A,sizeof(A)/ sizeof(int),string);
    LOGD("%s",string);

    buildMaxHeapbyMerge(A, sizeof(A)/ sizeof(int),0);
//    buildMaxHeap(A, sizeof(A)/ sizeof(int));
//    maxHeapSort(A, sizeof(A) / sizeof(int));

    LOGD("buildMaxHeapbyMerge array new:");
    intArray2String(A,sizeof(A)/ sizeof(int),string);
    LOGD("%s",string);

    int B[] = {13,  -3, -25,  20,  -3, -16, -23,  18,  20,  -7,   12,  -5, -22,  15,  -4,   40};
    Heap<int> *heap = new Heap<int>(2,B,sizeof(B)/ sizeof(int));
    heap->buildHeap();
    heap->heapSort();
    LOGD("buildMaxHeapbyMerge B:");
    intArray2String(B,sizeof(B)/ sizeof(int),string);
    LOGD("%s",string);

}
template <class DT>
void visit(DT data,int level){
    LOGD("biTree data=%c,level=%d",data,level);
}
template <class DT>
void visitBiTree(DT data){
        LOGD("visitBiTree data=%c",data);
}
template <class DT>
void visitBiTree1(DT data,int level){
    LOGD("visitBiTree data=%c",data);
}
void bitreeTest(){
    /**
    * ABCDEFGHI   J
    *              A
    *        B          C
    *    D      E    F     G
    *  H   I           J
    * */
    char c[] = "ABCDEFGHI   J";

    BiTree<char> biTree;
    biTree.creatBiTree(c,strlen(c));
    biTree.preOrder(visitBiTree1);
    biTree.levelOrder(visitBiTree);
}
extern "C"
JNIEXPORT void JNICALL
Java_cd_note_others_JniTest_biTreeTest(JNIEnv *env, jclass type) {

    /**
     * ABCDEFGHI   J
     *              A
     *        B          C
     *    D      E    F     G
     *  H   I           J
     * */
    char c[] = "ABCDEFGHI   J";
    BinTree biTree = creatBiTree(c, strlen(c),0);
//    preOrderTraverse(biTree,0,visit);
    preOrderTraverse_stack(biTree,0,visit);
    destroyBitTree(biTree);

    bitreeTest();
}

void visit_thr(TElemType data){
    LOGD("thrBiTree data=%c",data);
}
extern "C"
JNIEXPORT void JNICALL
Java_cd_note_others_JniTest_thrBiTreeTest(JNIEnv *env, jclass type) {

    char c[] = "ABCDEFGHI   J";

    ThrBiTree t;
    //建立头节点，中序线索二叉树
    inOrderThread_Head(&t,c, strlen(c),0);

    //中序遍历线索二叉树
    inOrderTraverse_The(t,visit_thr);

}extern "C"
JNIEXPORT void JNICALL
Java_cd_note_others_JniTest_stackTest(JNIEnv *env, jclass type) {

    Stack* stack = createStack(sizeof(int));

    LOGD("isStackEmpty(stack)=%d",isStackEmpty(stack));
    int value = 5,top;
    pushStack(stack,&value);
    LOGD("isStackEmpty(stack)=%d",isStackEmpty(stack));
    getTopElement(stack,&top);
    LOGD("getTopElement()=%d",top);
    value = 4;
    pushStack(stack,&value);
    LOGD("isStackEmpty(stack)=%d",isStackEmpty(stack));
    getTopElement(stack,&top);
    LOGD("getTopElement()=%d",top);
    value = 3;
    pushStack(stack,&value);
    LOGD("isStackEmpty(stack)=%d",isStackEmpty(stack));
    getTopElement(stack,&top);
    LOGD("getTopElement()=%d",top);
    ElemType data;
    popStack(stack, &data);
    LOGD("popEmpty(stack)=%d",data);
    popStack(stack, &data);
    LOGD("popEmpty(stack)=%d",data);
    popStack(stack, &data);
    LOGD("popEmpty(stack)=%d",data);
    LOGD("isStackEmpty(stack)=%d",isStackEmpty(stack));
    stackDestory(stack);
}
template <class T>
void visitAMLGraph(T data){
    LOGD("AmlGraph data=%d",data);
}
extern "C"
JNIEXPORT void JNICALL
Java_cd_note_others_JniTest_AmlGraph(JNIEnv *env, jclass type) {

    AMLGraph<int> *amlGraph = new AMLGraph<int>();
    initGraph(amlGraph, UDN, 20, 20);
    insertVex(amlGraph,1);
    insertVex(amlGraph,2);
    insertVex(amlGraph,3);
    insertVex(amlGraph,4);
    insertVex(amlGraph,5);
    insertVex(amlGraph,6);
    insertVex(amlGraph,7);

    insertArc(amlGraph,1,2,2);
    insertArc(amlGraph,1,3,3);
    insertArc(amlGraph,2,5,1);
    insertArc(amlGraph,2,3,7);
    insertArc(amlGraph,3,5,3);
    insertArc(amlGraph,4,6,5);
    insertArc(amlGraph,4,7,8);
    insertArc(amlGraph,6,7,4);

//    DFSTraverse(amlGraph,visitAMLGraph);

    BFSTraverse(amlGraph,visitAMLGraph);

    MGraph<int>*  mGraph = getMGraph(*amlGraph);
    for(int i=0; i<mGraph->vexnum;i++){
        for(int j=0; j<mGraph->vexnum;j++){
            LOGD("AmlGraph edge[%d][%d]=%d",i,j,mGraph->edge[i][j]);
        }
    }

    auto *minTree = new AMLGraph<int>();
    initGraph(minTree, UDN, 20, 20);
    kruskal(*amlGraph,minTree);
    Dijkstra(*amlGraph,1,2);
    floyd(*amlGraph);
    Kahn(*amlGraph);

    delete mGraph;
    delete amlGraph;
    delete minTree;
}
void visitOLGraph(OLGVexType data){
    LOGD("OlGraph data=%d",data);
}
extern "C"
JNIEXPORT void JNICALL
Java_cd_note_others_JniTest_OLGraph(JNIEnv *env, jclass type) {

    OLGGraph *olgGraph;
    CreateOLGraph(olgGraph,DG);
    insertOLVex(olgGraph,1);
    insertOLVex(olgGraph,2);
    insertOLVex(olgGraph,3);
    insertOLVex(olgGraph,4);
    insertOLVex(olgGraph,5);

    insertOLArc(olgGraph,1,2,0);
    insertOLArc(olgGraph,1,3,0);
    insertOLArc(olgGraph,2,5,0);
    insertOLArc(olgGraph,2,3,0);
    insertOLArc(olgGraph,3,5,0);

    DFSOLTraverse(olgGraph,visitOLGraph);

}
extern "C"
JNIEXPORT void JNICALL
Java_cd_note_others_JniTest_queueTest(JNIEnv *env, jclass type) {

    LQueue *queue =  creatLQueue(sizeof(int));
    LOGD("isLQueueEmpty(queue)=%d",isLQueueEmpty(queue));
    int e = 1;
    enLQueue(queue,&e);
    LOGD("enQueue %d",e);
    LOGD("isLQueueEmpty(queue)=%d",isLQueueEmpty(queue));
    e = 3;
    LOGD("enQueue %d",e);
    enLQueue(queue,&e);
    e = 2;
    LOGD("enQueue %d",e);
    enLQueue(queue,&e);

    deLQueue(queue,&e);
    LOGD("deLQueue %d",e);
    deLQueue(queue,&e);
    LOGD("deLQueue %d",e);

    emptyLQueue(queue);
    destroyLQueue(queue);


}

extern "C"
JNIEXPORT void JNICALL
Java_cd_note_others_JniTest_haffman(JNIEnv *env, jclass type) {

    char str[] = "111444447321323344626";
//    BiNode<HaffData<char>> *tree =  buildHaffTree<char>(str, strlen(str));
    HaffNode<char> *tree ;
    LinkedList<HaffCode<char>> *table;
    buildHaffTree<char>(str, strlen(str),tree,table);

    typedef typename LinkedList<HaffCode<char>>::LLIterator It;
    It it = table->iterator();
    while (it.hasNext()){
        HaffCode<char> code = it.next();
        LOGD("haffTable data=%c,code=%s",code.data,code.code);
    }

    char *code;
    haffEncode(table,"123467", 6,code);
    LOGD("haffTable encode=%s",code);

    char *decode = haffDecode(tree,code, strlen(code));
    LOGD("haffTable decode=%s",decode);
}