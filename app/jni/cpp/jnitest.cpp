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
#include "Linklist.h"
#include "DivideConquer.h"
#include "QuickSort.h"
#include <Random.h>

//
// Created by chenda on 2019/6/23.
//

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