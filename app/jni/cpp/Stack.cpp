#include <cstdlib>
#include <cstring>
#include "Stack.h"

/**
 * 作者：chenda
 * 时间：2019/7/23:17:06
 * 邮箱：
 * 说明：
 */

Stack *createStack(int data_size) {
    Stack *stack = (Stack *) malloc(sizeof(struct Stack));
    if (stack == NULL)
        return NULL;

    stack->data_size = data_size;
    stack->stack = NULL;
    return stack;
}

void stackEmpty(Stack *stack) {
    if (stack == NULL)
        return;
    void* data;
    while (popStack(stack, &data) >= 0) {
    }
}

void stackDestory(Stack *&stack) {
    stackEmpty(stack);
    free(stack);
}

int isStackEmpty(Stack *stack) {
    return stack->stack == NULL;
}

int pushStack(Stack *stack, void* data) {
    if (stack == NULL)
        return -1;

    StackNode *node = (StackNode *) malloc(sizeof(struct StackNode));
    if (node == NULL)
        return -1;

    node->data = malloc(stack->data_size);
    if(node->data==NULL){
        free(node);
        node=NULL;
        return -1;
    }
    memcpy(node->data,data,stack->data_size);

    node->next = stack->stack;
    stack->stack = node;
    return 0;
}

int popStack(Stack *stack, void *data) {
    if (stack == NULL || stack->stack == NULL) {
        return -1;
    }

    StackNode *pop = stack->stack;
    memcpy(data,pop->data,stack->data_size);
    stack->stack = pop->next;
    free(pop->data);
    free(pop);
    pop=NULL;
    return 0;
}

int getTopElement(Stack* stack,void* data) {
    if (stack == NULL || stack->stack == NULL) {
        return -1;
    }
    memcpy(data,stack->stack->data,stack->data_size);
    return 0;
}


