#include <jni.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "IntArrayPrinter.h"
#include "log.h"
#include "datastructure.h"
#include "algorithm.h"

//
// Created by chenda on 2019/6/23.
//

extern "C"
JNIEXPORT jint JNICALL
Java_cd_note_others_JniTest_sqListTest(JNIEnv *env, jclass type) {

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

    int array[] = {3,1,6,7,3,1,0,9};

    LOGD("--------insertSortTest--------");
    LOGD("array old:");
    printIntArr(array,sizeof(array)/ sizeof(int));

    insertSort(array, sizeof(array)/ sizeof(int));

    LOGD("array new:");
    printIntArr(array,sizeof(array)/ sizeof(int));

}extern "C"
JNIEXPORT void JNICALL
Java_cd_note_others_JniTest_mergeSortTest(JNIEnv *env, jclass type) {

    int array[] = {1,6,7,3,1,0,9,2};
//    int array[] = {3,1,6,7,39,1,20,9,21};

    LOGD("--------mergeSortTest--------");
    LOGD("array old:");
    printIntArr(array,sizeof(array)/ sizeof(int));

    insertSort(array, sizeof(array)/ sizeof(int));

    LOGD("array new:");
    printIntArr(array,sizeof(array)/ sizeof(int));

}extern "C"
JNIEXPORT jint JNICALL
Java_cd_note_others_JniTest_linkListTest(JNIEnv *env, jclass type) {

    LinkList *list;
    ElemType e;

    list = (LinkList *)malloc(sizeof(LinkList));

    linklistCreateTrail(list,10);
    LOGD("--------linkListTest--------");
    LOGD("old linkList:");
    for(int i=1; i<10;i++){
        linklistGet(list,i,&e);
        LOGD("%d ",e);
    }

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
        LOGD("%d ",e);
    }


    linklistClear(list);
    free(list);
    return 0;
}