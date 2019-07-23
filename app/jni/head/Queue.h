/**
 * 作者：chenda
 * 时间：2019/7/23:17:07
 * 邮箱：
 * 说明：
 */

#ifndef CORENOTE_QUEUE_H
#define CORENOTE_QUEUE_H

#define MAX 50
typedef int DataType;
typedef struct node{
    DataType data[MAX];
    int front,rear;
}Queue;



#endif //CORENOTE_QUEUE_H
