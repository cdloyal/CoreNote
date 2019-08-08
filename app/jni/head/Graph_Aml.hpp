/**
 * 作者：chenda
 * 时间：2019/7/29:9:39
 * 邮箱：
 * 说明：
 */

#ifndef CORENOTE_GRAPH_H
#define CORENOTE_GRAPH_H


#include <limits>
#include "LQueue.h"
#include "LinkedList.h"
#include "Utils.h"

#define NO_EDGE 2147483647  //定义无边

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

/**
 * 邻接多重表（无向图）
 * */
template <class T>
struct AMLGraph{
    VexBox<T> *Vlist;
    int vexnum,arcnum,maxVexNum,defRiseNum;  //顶点数量，边数量
    AmlKind kind;
    //访问标志数组
    int *visited;
};

/**
 * 邻接矩阵
 * */
template <class T>
struct MGraph{
    T *Vlist;     //顶点数据
    int **edge;
    int vexnum;  //顶点数量，边数量
    AmlKind kind;
    //访问标志数组
    int *visited;
};

//创建图
//defVexNum     初始化最大顶点数，
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
//返回NULL或者
template <class T>
MGraph<T>* getMGraph(AMLGraph<T> *amlGraph);

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
int CreateGraph(AMLGraph<T> *&amlGraph,AmlKind kind,int defVexNum,int defRiseNum){
    amlGraph = new AMLGraph<T>();
    amlGraph->maxVexNum = defVexNum;
    amlGraph->defRiseNum = defRiseNum;
    amlGraph->Vlist = new VexBox<T>[defVexNum]();
    amlGraph->visited = new int[defVexNum]();
    amlGraph->kind=kind;
    amlGraph->arcnum=0;
    amlGraph->vexnum=0;
    return 0;
}

//定位一个顶点值为途中的位置，否则返回-1
template <class T>
int locateVex(AMLGraph<T> amlGraph,T data){
    for (int i = 0; i < amlGraph.vexnum; ++i) {
        if(amlGraph.Vlist[i].data == data){
            return i;
        }
    }
    return -1;
}

//插入一个顶点
template <class T>
int insertVex(AMLGraph<T> *amlGraph,T data){
    for(int i=0;i<amlGraph->vexnum;++i){
        if(amlGraph->Vlist[i].data==data){
            LOGD("insertVex errot,vertex %d is exist!",data);
            return -1;
        }
    }

    if(amlGraph->arcnum>=amlGraph->maxVexNum){
        VexBox<T> *list = new VexBox<T>[amlGraph->maxVexNum+amlGraph->defRiseNum];
        for(int i=0;i<amlGraph->maxVexNum;i++){
            list[i] = amlGraph->Vlist[i];
            delete []amlGraph->Vlist;
            amlGraph->Vlist = list;
        }
        amlGraph->maxVexNum+=amlGraph->defRiseNum;
    }

    amlGraph->Vlist[amlGraph->vexnum].data=data;
    amlGraph->Vlist[amlGraph->vexnum].firstarc=NULL;
    amlGraph->visited[amlGraph->vexnum]=unvisited;
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
    eBox->iLink = amlGraph->Vlist[indexVi].firstarc;
    eBox->jLink = amlGraph->Vlist[indexVj].firstarc;
    amlGraph->Vlist[indexVi].firstarc = eBox;
    amlGraph->Vlist[indexVj].firstarc = eBox;
    if(amlGraph->kind==UDN)
        eBox->weight = weight;
    else
        eBox->weight = 1;
    return 0;
}

template <class T>
MGraph<T>*  getMGraph(AMLGraph<T> *amlGraph){
    MGraph<T>* mGraph = new MGraph<T>();
    mGraph->vexnum = amlGraph->vexnum;
    mGraph->kind = amlGraph->kind;
    mGraph->visited = new int[mGraph->vexnum];
    mGraph->Vlist = new T[mGraph->vexnum];

    for(int i=0;i<mGraph->vexnum;i++){
        mGraph->Vlist[i] = amlGraph->Vlist[i].data;
        mGraph->visited[i] = 0;
        mGraph->edge = new int* [mGraph->vexnum];
    }
    for(int i=0;i<mGraph->vexnum;i++){
        mGraph->edge[i] = new int[mGraph->vexnum];
    }
    for(int i=0;i<mGraph->vexnum;i++){
        for(int j=0;j<mGraph->vexnum;j++){
            mGraph->edge[i][j]=NO_EDGE;
        }
        mGraph->edge[i][i] = 0;

        EBox *eBox = amlGraph->Vlist[i].firstarc;
        while (eBox!=NULL){
            int j = eBox->ivex==i?eBox->jvex:eBox->ivex;
            mGraph->edge[i][i] = eBox->weight;
            eBox=eBox->ivex==i?eBox->iLink:eBox->jLink;
        }
    }

    return mGraph;
}


//递归实现深度遍历邻接点
//连通图/子图
template <class T>
void DFS(AMLGraph<T> *G,int i,void (*visit)(T)){
    G->visited[i] = isvisited;
    visit(G->Vlist[i].data);

    EBox *eBox = G->Vlist[i].firstarc;

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

    visit(G->Vlist[i].data);
    G->visited[i] = isvisited;
    enLQueue(queue,&i);

    while (!isLQueueEmpty(queue)){
        deLQueue(queue,&vex);
        eBox = G->Vlist[vex].firstarc;
        while (eBox!=NULL){
            int j = eBox->ivex==vex?eBox->jvex:eBox->ivex;
            if(G->visited[j]!=isvisited){
                visit(G->Vlist[j].data);
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
