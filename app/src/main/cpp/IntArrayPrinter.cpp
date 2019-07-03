//
// Created by chenda on 2019/6/23.
//

#include <cstdio>
#include <cstring>
#include "IntArrayPrinter.h"
#include "log.h"

void printIntArr(int *array, int size){

    int i = 0;
    for (i = 0; i < size; i++)
    {
        LOGD("%d ", array[i]);
    }
}
