#include <cstdlib>
#include <ctime>
#include <log.h>
#include "Random.h"
//
// Created by chenda on 2019/7/18.
//


/**
 * 随机算法：对输入进行随机排序
 * */
void randomize_in_place(int *array,int start,int len){
    srand(static_cast<unsigned int>(time(0)));    //设置随机数种子
    int tmp;
    int rand;
    for(int i=0;i<len;i++){
        tmp = array[start+i];
        rand = random()%len;
        LOGD("rand=%d",rand);
        array[start+i] = array[start+rand];
        array[start+rand]=tmp;
    }
}
