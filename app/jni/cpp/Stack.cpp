#include <cstdlib>
#include "Stack.h"
/**
 * 作者：chenda
 * 时间：2019/7/23:17:06
 * 邮箱：
 * 说明：
 */

Stack* createStack(){
    Stack* stack = (Stack*)malloc(sizeof(struct node));
    if(stack==NULL)
        return NULL;

    stack->next=NULL;
    return stack;
}
void stackEmpty(Stack* stack){
    if(stack==NULL)
        return;
    DataType data;
    int ret = popEmpty(stack,&data);
    while (ret>=0){
        popEmpty(stack,&data);
    }
}
void stackDestory(Stack* stack){
    stackEmpty(stack);
    free(stack);
}

int isEmpty(Stack *stack) {
    return stack->next == NULL;
}

int pushStack(Stack* stack,DataType data){
    if(stack==NULL)
        return -1;

    Stack* node = (Stack*)malloc(sizeof(struct node));
    if(node==NULL)
        return -1;

    node->next = stack->next;
    node->data = data;

    stack->next = node;
    return 0;
}
int popEmpty(Stack* stack,DataType* data){
    if(stack==NULL || stack->next==NULL){
        data = NULL;
        return -1;
    }

    Stack* pop = stack->next;
    * data = pop->data;

    stack = pop->next;
    free(pop);

    return 0;
}

DataType getTopElement(Stack* stack){
    if(stack==NULL ){
        return NULL;
    }
    return stack->next->data;
}


