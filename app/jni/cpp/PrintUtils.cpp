//
// Created by chenda on 2019/6/23.
//

#include <cstdio>
#include <cstring>
#include "PrintUtils.h"
#include "log.h"

int intArray2String(int *intArray,int len,char *string){
    int offset = 0;
    for(int i=0;i<len;i++){
        offset += sprintf(string+offset,"%d ",intArray[i]);
    }
    string[offset] = '\0';
    return offset+1;
}