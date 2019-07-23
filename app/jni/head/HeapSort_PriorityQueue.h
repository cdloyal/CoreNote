//
// Created by chenda on 2019/7/20.
//

#ifndef CORENOTE_HEAPSORT_PRIORITYQUEUE_H
#define CORENOTE_HEAPSORT_PRIORITYQUEUE_H

void buildMaxHeapbyMerge(int *A,int size,int i);
void buildMaxHeap(int *A,int size);
void maxHeapSort(int *A, int size);

int maxHeapMaximum(int *A);
int extractMaxHeap(int *A, int *size,int *maxValue);
int heapIncreaseKey(int *A,int i,int key);
void heapInsert(int *A,int size,int i);

#endif //CORENOTE_HEAPSORT_PRIORITYQUEUE_H
