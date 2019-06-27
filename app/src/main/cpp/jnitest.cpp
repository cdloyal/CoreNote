#include <jni.h>
#include <tool.h>
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
    initSqList(&sqList);
    LOGD("sqList.length=%d,sqList.data[0]=%d",sqList.length,sqList.data[0]);
    int ret = insertElem(&sqList,1,1);
    ret = GetElem(&sqList,1,&e);
    LOGD("sqList.length=%d,GetElem(&sqList,1,&e)=%d",sqList.length,e);
    ret = insertElem(&sqList,1,2);
    ret = GetElem(&sqList,1,&e);
    LOGD("sqList.length=%d,GetElem(&sqList,1,&e)=%d",sqList.length,e);
    ret = deleteElem(&sqList,1,&e);
    LOGD("sqList.length=%d,deleteElem(&sqList,1,&e)=%d",sqList.length,e);
    ret = GetElem(&sqList,1,&e);
    LOGD("sqList.length=%d,GetElem(&sqList,1,&e)=%d",sqList.length,e);
    ret = deleteElem(&sqList,1,&e);
    LOGD("sqList.length=%d,deleteElem(&sqList,1,&e)=%d",sqList.length,e);

    return 0;

}extern "C"
JNIEXPORT void JNICALL
Java_cd_note_others_JniTest_insertSortTest(JNIEnv *env, jclass type) {

    int array[] = {3,1,6,7,3,1,0,9};
    LOGD("array old:");
    printIntArr(array,sizeof(array)/ sizeof(int));
    insertSort(array, sizeof(array)/ sizeof(int));
    LOGD("array new:");
    printIntArr(array,sizeof(array)/ sizeof(int));

}