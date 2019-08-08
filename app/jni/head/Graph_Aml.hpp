/**
 * 作者：chenda
 * 时间：2019/7/29:9:39
 * 邮箱：
 * 说明：
 */

#ifndef CORENOTE_GRAPH_H
#define CORENOTE_GRAPH_H

/**
 * 邻接多重表（无向图）
 * */


#include "LinkedList.h"

//访问标记
typedef enum {unvisited,isvisited}VisitIf;
//图的类型:无向图/网
typedef enum {UDG,UDN}AmlKind;

//边结构
typedef struct EBox{
    VisitIf mark;       //访问标记
    int ivex;           //边顶点1
    int jvex;           //边顶点2
    struct EBox *iLink; //指向依附于顶点1的下一条边，类似于起点相同的一条弧
    struct EBox *jLink; //指向依附于顶点2的下一条边，类似于终点点相同的一条弧
    int weight;         //权值
}EBox;

//顶点结构
template <class T>
struct VexBox{
    T data;
    EBox *firstarc;     //指向第一条依附于该顶点的边
};

template <class T>
struct AMLGraph{
    VexBox<T> *Vlist;
    int vexnum,arcnum;  //顶点数量，边数量
    AmlKind kind;
    //访问标志数组
    int *visited;
};

//创建图
//defVexNum     初始化顶点数，
//defRiseNum    当插入顶点数>defVexNum，默认的增长数
template <class T>
int CreateGraph(AMLGraph<T> *&amlGraph,AmlKind kind,int defVexNum,int defRiseNum);
//销毁图
template <class T>
int destroyGraph(AMLGraph<T> *amlGraph);

//定位一个顶点值为途中的位置，否则返回-1
template <class T>
int locateVex(AMLGraph<T> amlGraph,T data);

//返回顶点的值
template <class T>
T getVex(AMLGraph<T> *amlGraph,int v);

//赋值
template <class T>
int putVex(AMLGraph<T> *amlGraph,T oldData,T newData);

//插入一个顶点
template <class T>
int insertVex(AMLGraph<T> *amlGraph,T data);

//插入一条弧
template <class T>
int insertArc(AMLGraph<T> *amlGraph,T vi,T vj,int weight);

//返回邻接矩阵

//返回顶点值为v的下一个邻接顶点的序号，否怎返回-1
template <class T>
int FirstAdjVex(AMLGraph<T> G,T v);

//返回顶点值为v相对于顶点值为w的下一个顶点的序号
template <class T>
int NextAdjVex(AMLGraph<T> G,T v,T w);

//深度优先遍历，起点i的连通图
template <class T>
void DFS(AMLGraph<T> *G,int i,void (*visit)(T));
//深度优先遍历，整图
template <class T>
int DFSTraverse(AMLGraph<T> *G, void (*visit)(T));

//广度优先遍历，起点i的连通图
template <class T>
void BFS(AMLGraph<T> *G,int i,void (*visit)(T));
//广度优先遍历，整图
template <class T>
int BFSTraverse(AMLGraph<T> *G, void (*visit)(T));














//创建图
template <class T>
int CreateGraph(AMLGraph<T> *&amlGraph,AmlKind kind){
    amlGraph = (AMLGraph<T>*)malloc(sizeof(AMLGraph<T>));
    if(amlGraph==NULL){
        LOGD("OVERFLOW create graph error");
        return -1;
    }
    amlGraph->kind=kind;
    amlGraph->arcnum=0;
    amlGraph->vexnum=0;
    return 0;
}

//定位一个顶点值为途中的位置，否则返回-1
template <class T>
int locateVex(AMLGraph<T> amlGraph,T data){
    for (int i = 0; i < amlGraph.vexnum; ++i) {
        if(amlGraph.Vlist.get(i).data == data){
            return i;
        }
    }
    return -1;
}

//插入一个顶点
template <class T>
int insertVex(AMLGraph<T> *amlGraph,T data){
    for(int i=0;i<amlGraph->vexnum;++i){
        if(amlGraph->Vlist.get(i).data==data){
            LOGD("insertVex errot,vertex %d is exist!",data);
            return -1;
        }
    }

    VexBox vexBox;
    vexBox.data = data;
    vexBox.firstarc = NULL;
    amlGraph->Vlist.insert(vexBox);

    amlGraph->visited.insert(unvisited);
    amlGraph->vexnum++;

    return 0;
}

//插入一条弧
template <class T>
int insertArc(AMLGraph<T> *amlGraph,T vi,T vj,int weight){
    if(amlGraph==NULL){
        LOGD("error amlGraph==NULL!");
        return -1;
    }

    int indexVi = locateVex(*amlGraph,vi);
    if(vi==-1){
        LOGD("error vertex vi not exist!");
        return -1;
    }
    int indexVj = locateVex(*amlGraph,vj);
    if(vj==-1){
        LOGD("error vertex vj not exist!");
        return -1;
    }


    EBox* eBox = (EBox*)malloc(sizeof(EBox));
    eBox->ivex = indexVi;
    eBox->jvex = indexVj;
    if(amlGraph->kind==UDN)
        eBox->weight = weight;
    VexBox<T> vbi = amlGraph->Vlist.get(indexVi);
    VexBox<T> vbj = amlGraph->Vlist.get(indexVj);
    eBox->iLink = vbi.firstarc;
    eBox->jLink = vbj.firstarc;
    vbi.firstarc = eBox;
    vbj.firstarc = eBox;
    amlGraph->Vlist.set(indexVi,vbi);
    amlGraph->Vlist.set(indexVi,vbj);
    return 0;
}

//递归实现深度遍历邻接点
//连通图/子图
template <class T>
void DFS(AMLGraph<T> *G,int i,void (*visit)(T)){
    G->visited[i] = isvisited;
    visit(G->adjmulist[i].data);

    EBox *eBox = G->adjmulist[i].firstarc;

    while (eBox!=NULL){
        int j = eBox->ivex==i?eBox->jvex:eBox->ivex;
        if(G->visited[j]==isvisited){
            eBox=eBox->ivex==i?eBox->iLink:eBox->jLink;
            continue;
        }
        DFS(G,j,visit);
    }
}

//深度优先遍历
//输入：图 G
//输出：遍历图G的每个点
//  图G可能有不同的子图
template <class T>
int DFSTraverse(AMLGraph<T> *G,void (*visit)(T)){
    if( G->vexnum<=0){
        LOGD("error vertex has none!");
        return -1;
    }

    for(int i=0;i<G->vexnum;++i){
        G->visited[i] = unvisited;
    }

    for(int i=0;i<G->vexnum;++i){
        if(G->visited[i]!=isvisited)
            DFS(G,i,visit);
    }

    return 0;
}

//广度优先遍历，起点i的连通图
template <class T>
void BFS(AMLGraph<T> *G,int i,void (*visit)(T)){
    if(G==NULL)
        return;
    if(G->visited[i]==isvisited){
        return;
    }

    LQueue *queue = creatLQueue(sizeof(int));

    int vex;
    EBox *eBox;

    visit(G->adjmulist[i].data);
    G->visited[i] = isvisited;
    enLQueue(queue,&i);

    while (!isLQueueEmpty(queue)){
        deLQueue(queue,&vex);
        eBox = G->adjmulist[vex].firstarc;
        while (eBox!=NULL){
            int j = eBox->ivex==vex?eBox->jvex:eBox->ivex;
            if(G->visited[j]!=isvisited){
                visit(G->adjmulist[j].data);
                G->visited[j]=isvisited;
                enLQueue(queue,&j);
            }
            eBox = eBox->ivex==vex?eBox->iLink:eBox->jLink;
        }
    }

    destroyLQueue(queue);
}

//广度优先遍历，整图
template <class T>
int BFSTraverse(AMLGraph<T> *G, void (*visit)(T)){
    if(G==NULL)
        return -1;

    for(int i=0; i<G->vexnum; i++){
        G->visited[i]=unvisited;
    }

    for(int i=0; i<G->vexnum; i++){
        if(G->visited[i]!=isvisited)
            BFS(G,i,visit);
    }
    return 0;
}
#endif //CORENOTE_GRAPH_H
