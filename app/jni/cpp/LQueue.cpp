#include <cstdlib>
#include <log.h>
#include <cstring>
#include "LQueue.h"
/**
 * 作者：chenda
 * 时间：2019/7/23:17:07
 * 邮箱：
 * 说明：
 */

LQueue* creatLQueue(int data_size){
    LQueue *queue = (LQueue *) malloc(sizeof(LQueue));
    if(queue==NULL){
        LOGD("error,creatLQueue failed overflow");
        return NULL;
    }
    LQNode *node = (LQNode *) malloc(sizeof(LQNode));
    if(node==NULL){
        LOGD("error,creatLQueue failed overflow");
        free(queue);
        return NULL;
    }
    queue->front=node;
    queue->rear=node;
    queue->data_size = data_size;
    queue->front->next=NULL;
    return queue;
}
int emptyLQueue(LQueue* queue){
    void *e = malloc(queue->data_size);
    while (!isLQueueEmpty(queue)){
        deLQueue(queue,e);
    }
    free(e);
    return 0;
}
int destroyLQueue(LQueue* queue){
    emptyLQueue(queue);
    free(queue->front);
    free(queue);
    return 0;
}

int isLQueueEmpty(LQueue* queue){
    return queue->front==queue->rear;
}
int enLQueue(LQueue *queue, void *e){
    if (queue==NULL || e==NULL){
        LOGD("error,param input error");
        return -1;
    }
    LQNode *node = (LQNode *) malloc(sizeof(LQNode));
    if(node==NULL){
        LOGD("error,EnLQueue failed overflow");
        return -1;
    }
    memcpy(node->data,e,queue->data_size);
    node->next=queue->rear->next;
    queue->rear->next=node;
    queue->rear=node;
    return 0;
}
int deLQueue(LQueue* queue,void *e){
    if(isLQueueEmpty(queue)){
        LOGD("error,deLQueue failed LQueue is empty");
        return -1;
    }
    LQNode *node = queue->front->next;
    memcpy(e,node->data,queue->data_size);
    queue->front->next = node->next;
    free(node);
    return 0;
}