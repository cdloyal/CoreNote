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
#include <AmlGraph.hpp>
#include <queue>
#include <LQueue.h>
#include <TemplateUse.h>
#include <CTest.h>
#include "HeapSort_PriorityQueue.h"
#include "BinaryTree.h"
//
// Created by chenda on 2019/6/23.
//
#include "OLGraph.h"

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

}extern "C"
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

    Iterator iterator = getIterator(list,0);
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
    int A[] = {13,  -3, -25,  20,  -3, -16, -23,  18,  20,  -7,   12,  -5, -22,  15,  -4,   40};
    LOGD("buildMaxHeapbyMerge array src:");
    intArray2String(A,sizeof(A)/ sizeof(int),string);
    LOGD("%s",string);

//    buildMaxHeapbyMerge(A, sizeof(A)/ sizeof(int),0);
//    buildMaxHeap(A, sizeof(A)/ sizeof(int));
    maxHeapSort(A, sizeof(A) / sizeof(int));

    LOGD("buildMaxHeapbyMerge array new:");
    intArray2String(A,sizeof(A)/ sizeof(int),string);
    LOGD("%s",string);
}
void visit(BTNElemType data,int level){
    LOGD("biTree data=%c,level=%d",data,level);
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
    BiTree biTree = creatBiTree(c, strlen(c),0);
//    preOrderTraverse(biTree,0,visit);
    preOrderTraverse_stack(biTree,0,visit);
    destroyBitTree(biTree);
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
void visitAMLGraph(AmlVexType data){
    LOGD("AmlGraph data=%d",data);
}
extern "C"
JNIEXPORT void JNICALL
Java_cd_note_others_JniTest_AmlGraph(JNIEnv *env, jclass type) {

    AMLGraph *amlGraph;
    CreateGraph(amlGraph,UDG);
    insertVex(amlGraph,1);
    insertVex(amlGraph,2);
    insertVex(amlGraph,3);
    insertVex(amlGraph,4);
    insertVex(amlGraph,5);

    insertArc(amlGraph,1,2,0);
    insertArc(amlGraph,1,3,0);
    insertArc(amlGraph,2,5,0);
    insertArc(amlGraph,2,3,0);
    insertArc(amlGraph,3,5,0);

//    DFSTraverse(amlGraph,visitAMLGraph);

    BFSTraverse(amlGraph,visitAMLGraph);
}
void visitOLGraph(AmlVexType data){
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

