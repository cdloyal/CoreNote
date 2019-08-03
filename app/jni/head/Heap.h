//
// Created by chenda on 2019/8/3.
//

#ifndef CORENOTE_HEAP_H
#define CORENOTE_HEAP_H


template <class DT>
class Heap{
private:
    DT *A;
    int size;
    int flag;
    /*
   * Description:     维持堆属性建堆
   * Return:          void
   */
    void heap(int i);

    //递归法建堆
    void buildHeapMerge(int i);
public:
    /*
    * Description:     建堆，非递归法建堆
    * Input:           flag     1:建最大堆，2：建最小堆
    *                  array    数据数组，建堆会改变传进来的数组
    *                  size     数组长度
    * Return:
    */
    Heap(int flag,DT *array, int size);
    ~Heap();

    /*
    * Description:     非递归法建堆
    * Return:          返回建好堆的array
    */
    DT* buildHeap();
    /*
    * Description:     堆排序,此函数要在buildHeap()调用后才能用
    * Return:          flag==1，返回从小到大的数组；flag==2，返回从大到小的数组；
    */
    DT* heapSort();

    /*
    * Description:     返回堆的根节点，即数组最大值/最小值
    * Return:          flag==1，返回数组最大值；flag==2，返回数组最小值
    */
    DT heapHead();

    /*
    * Description:     删除堆的根节点，并返回根节点数据
    * Return:          失败返回NULL
    */
    DT extractheapHead();

    /*
    * Description:     改变堆其中一个节点并重新建堆，此函数要在buildHeap()调用后才能用
    * Input:           i : array的下标
    *                  key ： 要改成的值；flag==1，key>=array[i]；flag==2，key<=array[i]
    * Return:          >=0成功
    */
    int resetKey(int i,DT key);

    /*
    * Description:     插入一个节点并重新建堆
    * Input:           key ： 要改成的值
    * Return:          >=0成功
    */
    void heapInsert(DT key);
};

template<class DT>
void Heap<DT>::heap(int i) {
    int tmp,l=2*i+1,r=2*i+2,max=i;
    if(flag==1){
        if(l<=size-1 &&  A[max]<A[l])
            max=l;
        if(r<=size-1 &&  A[max]<A[r])
            max=r;
    } else{
        if(l<=size-1 &&  A[max]>A[l])
            max=l;
        if(r<=size-1 &&  A[max]>A[r])
            max=r;
    }
    if(max!=i){
        tmp=A[i];
        A[i]=A[max];
        A[max]=tmp;
        heap(max);
    }
}

template<class DT>
void Heap<DT>::buildHeapMerge(int i) {
    int l=2*i+1,r=2*i+2;
    if(l>size-1)        //不存在子节点，叶子
        return;
    if(l<=size-1)       //存在左子数
        buildHeapMerge(l);
    if(r<=size-1)       //存在右子树
        buildHeapMerge(r);
    heap(i);
}

template<class DT>
Heap<DT>::Heap(int flag, DT *array, int size) {
    this->flag = flag;
    this->A = array;
    this->size = size;
}

template<class DT>
Heap<DT>::~Heap() {

}

template<class DT>
DT *Heap<DT>::buildHeap() {
    for (int i=(size+1)/2;i>=0;i--){     //(size-(start-1))/2+1+(start-1) =  (size+1)/2
        heap(i);
    }
    return A;
}

template<class DT>
DT *Heap<DT>::heapSort() {
    int tmpSize = size;
    for(int i=1;i<tmpSize;i++){
        int tmp=A[0];
        A[0]=A[size-1];
        A[size-1]=tmp;
        size--;
        heap(0);
    }
    return A;
}

template<class DT>
DT Heap<DT>::heapHead() {
    if(size>0)
        return A[0];
    return nullptr;
}

template<class DT>
DT Heap<DT>::extractheapHead() {
    if(size<=0)
        return nullptr;

    DT ret = A[0];

    A[0] = A[size-1] ;
    (size)--;

    heap(0);
    return ret;
}

template<class DT>
int Heap<DT>::resetKey(int i, DT key) {
    if(flag==1){
        if(key<A[i])
            return -1;

        A[i]=key;
        while(i>0 && A[(i-1)/2]<A[i]){  //(j+(start-1))/2
            int tmp=A[i];
            A[i]=A[(i-1)/2];
            A[(i-1)/2]=tmp;
            i = (i-1)/2;
        }
    } else{
        if(key>A[i])
            return -1;

        A[i]=key;
        while(i>0 && A[(i-1)/2]>A[i]){  //(j+(start-1))/2
            int tmp=A[i];
            A[i]=A[(i-1)/2];
            A[(i-1)/2]=tmp;
            i = (i-1)/2;
        }
    }
    return 0;
}

template<class DT>
void Heap<DT>::heapInsert(DT key) {
    if(flag==1){
        A[size]=key--;
    } else{
        A[size]=key++;
    }
    size++;
    resetKey(size-1,key);
}

#endif //CORENOTE_HEAP_H
