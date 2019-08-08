//
// Created by chenda on 2019/8/8.
//

#ifndef CORENOTE_1_UTILS_H
#define CORENOTE_1_UTILS_H

/*
* Description:     增长
* Input:           src      要增长得数据
*                  OirByte  src目前长度
*                  wanByte  要增长到多少
* Return:          int     >=0成功返回array得实际长度，<失败
*/
template<class T>
static int increate(T *&src, int OirByte, int wanByte) {
    if (OirByte == 0 || src == NULL) {
        src = (T *) malloc(wanByte);
        if (src == NULL)
            return -1;
        return wanByte;
    }
    T *tmp = (T *) malloc(OirByte);
    memcpy(tmp, src, OirByte);
    free(src);
    src = (T *) malloc(wanByte);
    if (src == NULL) {
        free(tmp);
        return -1;
    }
    memcpy(src, tmp, OirByte);
    free(tmp);
    return wanByte;
};

#endif //CORENOTE_1_UTILS_H
