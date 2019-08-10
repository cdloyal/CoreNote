/**
 * 作者：chenda
 * 时间：2019/7/29:9:39
 * 邮箱：
 * 说明：
 */

#ifndef CORENOTE_GRAPH_H
#define CORENOTE_GRAPH_H


#include <limits>
#include <memory>
#include "LQueue.h"
#include "LinkedList.h"
#include "Utils.h"
#include "Cmp.h"
#include <list>
#include <string>
#include <forward_list>
#include <deque>

#define NO_EDGE 2147483647  //定义无边

//访问标记
typedef enum {
    unvisited, isvisited
} VisitIf;
//图的类型:无向图/网
typedef enum {
    UDG, UDN
} AmlKind;

//边结构
typedef struct EBox {
    VisitIf mark;       //访问标记
    int ivex;           //边顶点1
    int jvex;           //边顶点2
    struct EBox *iLink; //指向依附于顶点1的下一条边，类似于起点相同的一条弧
    struct EBox *jLink; //指向依附于顶点2的下一条边，类似于终点点相同的一条弧
    int weight;         //权值

    int operator-(const EBox &eBox);
} EBox;

//顶点结构
template<class T>
struct VexBox {
    T data;
    EBox *firstarc;     //指向第一条依附于该顶点的边
};

/**
 * 邻接多重表（无向图）
 * */
template<class T>
struct AMLGraph {
    VexBox<T> *Vlist;
    int vexnum, arcnum, maxVexNum, defRiseNum;  //顶点数量，边数量
    AmlKind kind;
    //访问标志数组
    int *visited;
};

/**
 * 邻接矩阵
 * */
template<class T>
struct MGraph {
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
template<class T>
int initGraph(AMLGraph<T> *&amlGraph, AmlKind kind, int defVexNum, int defRiseNum);

//销毁图
template<class T>
int destroyGraph(AMLGraph<T> *amlGraph);

//定位一个顶点值为途中的位置，否则返回-1
template<class T>
int locateVex(AMLGraph<T> amlGraph, T data);

//返回顶点的值
template<class T>
T getVex(AMLGraph<T> *amlGraph, int v);

//赋值
template<class T>
int putVex(AMLGraph<T> *amlGraph, T oldData, T newData);

//插入一个顶点
template<class T>
int insertVex(AMLGraph<T> *amlGraph, T data);

//插入一条弧
template<class T>
int insertArc(AMLGraph<T> *amlGraph, T vi, T vj, int weight);

//返回邻接矩阵
//返回NULL或者
template<class T>
MGraph<T> *getMGraph(const AMLGraph<T> &amlGraph);

//返回顶点值为v的下一个邻接顶点的序号，否怎返回-1
template<class T>
int FirstAdjVex(AMLGraph<T> G, T v);

//返回顶点值为v相对于顶点值为w的下一个顶点的序号
template<class T>
int NextAdjVex(AMLGraph<T> G, T v, T w);

//深度优先遍历，起点i的连通图
template<class T>
void DFS(AMLGraph<T> *G, int i, void (*visit)(T));

//深度优先遍历，整图
template<class T>
int DFSTraverse(AMLGraph<T> *G, void (*visit)(T));

//广度优先遍历，起点i的连通图
template<class T>
void BFS(AMLGraph<T> *G, int i, void (*visit)(T));

//广度优先遍历，整图
template<class T>
int BFSTraverse(AMLGraph<T> *G, void (*visit)(T));

int getFather_Graph(int u, int *road);

//最小生成树  https://blog.csdn.net/luoshixian099/article/details/51908175
//最小生成树:克鲁斯卡尔算法（kruskal）
template<class T>
int kruskal(const AMLGraph<T> graph, AMLGraph<T> *minTree);

//最小生成树:普利姆算法（Prim）


//最短路径

//迪杰斯特拉算法 https://blog.csdn.net/qq_35644234/article/details/60870719
//顶点head到图上个顶点的最短路径
template<class T>
void Dijkstra(const AMLGraph<T> graph, T head);


//创建图
template<class T>
int initGraph(AMLGraph<T> *&amlGraph, AmlKind kind, int defVexNum, int defRiseNum) {
    amlGraph->maxVexNum = defVexNum;
    amlGraph->defRiseNum = defRiseNum;
    amlGraph->Vlist = new VexBox<T>[defVexNum]();
    amlGraph->visited = new int[defVexNum]();
    amlGraph->kind = kind;
    amlGraph->arcnum = 0;
    amlGraph->vexnum = 0;
    return 0;
}

//定位一个顶点值为途中的位置，否则返回-1
template<class T>
int locateVex(AMLGraph<T> amlGraph, T data) {
    for (int i = 0; i < amlGraph.vexnum; ++i) {
        if (amlGraph.Vlist[i].data == data) {
            return i;
        }
    }
    return -1;
}

//插入一个顶点
template<class T>
int insertVex(AMLGraph<T> *amlGraph, T data) {
    for (int i = 0; i < amlGraph->vexnum; ++i) {
        if (amlGraph->Vlist[i].data == data) {
            LOGD("insertVex errot,vertex %d is exist!", data);
            return -1;
        }
    }

    if (amlGraph->vexnum >= amlGraph->maxVexNum) {
        VexBox<T> *list = new VexBox<T>[amlGraph->maxVexNum + amlGraph->defRiseNum];
        for (int i = 0; i < amlGraph->maxVexNum; i++) {
            list[i] = amlGraph->Vlist[i];
            delete[]amlGraph->Vlist;
            amlGraph->Vlist = list;
        }
        amlGraph->maxVexNum += amlGraph->defRiseNum;
    }

    amlGraph->Vlist[amlGraph->vexnum].data = data;
    amlGraph->Vlist[amlGraph->vexnum].firstarc = NULL;
    amlGraph->visited[amlGraph->vexnum] = unvisited;
    amlGraph->vexnum++;

    return 0;
}

//插入一条弧
template<class T>
int insertArc(AMLGraph<T> *amlGraph, T vi, T vj, int weight) {
    if (amlGraph == NULL) {
        LOGD("error amlGraph==NULL!");
        return -1;
    }

    int indexVi = locateVex(*amlGraph, vi);
    if (vi == -1) {
        LOGD("error vertex vi not exist!");
        return -1;
    }
    int indexVj = locateVex(*amlGraph, vj);
    if (vj == -1) {
        LOGD("error vertex vj not exist!");
        return -1;
    }


    EBox *eBox = (EBox *) malloc(sizeof(EBox));
    eBox->ivex = indexVi;
    eBox->jvex = indexVj;
    eBox->iLink = amlGraph->Vlist[indexVi].firstarc;
    eBox->jLink = amlGraph->Vlist[indexVj].firstarc;
    amlGraph->Vlist[indexVi].firstarc = eBox;
    amlGraph->Vlist[indexVj].firstarc = eBox;
    if (amlGraph->kind == UDN)
        eBox->weight = weight;
    else
        eBox->weight = 1;

    amlGraph->arcnum++;
    return 0;
}

template<class T>
MGraph<T> *getMGraph(const AMLGraph<T> &amlGraph) {
    MGraph<T> *mGraph = new MGraph<T>();
    mGraph->vexnum = amlGraph.vexnum;
    mGraph->kind = amlGraph.kind;
    mGraph->visited = new int[mGraph->vexnum];
    mGraph->Vlist = new T[mGraph->vexnum];

    for (int i = 0; i < mGraph->vexnum; i++) {
        mGraph->Vlist[i] = amlGraph.Vlist[i].data;
        mGraph->visited[i] = 0;
        mGraph->edge = new int *[mGraph->vexnum];
    }
    for (int i = 0; i < mGraph->vexnum; i++) {
        mGraph->edge[i] = new int[mGraph->vexnum];
    }
    for (int i = 0; i < mGraph->vexnum; i++) {
        for (int j = 0; j < mGraph->vexnum; j++) {
            mGraph->edge[i][j] = NO_EDGE;
        }
        mGraph->edge[i][i] = 0;

        EBox *eBox = amlGraph.Vlist[i].firstarc;
        while (eBox != NULL) {
            int j = eBox->ivex == i ? eBox->jvex : eBox->ivex;
            mGraph->edge[i][j] = eBox->weight;
            eBox = eBox->ivex == i ? eBox->iLink : eBox->jLink;
        }
    }

    return mGraph;
}


//递归实现深度遍历邻接点
//连通图/子图
template<class T>
void DFS(AMLGraph<T> *G, int i, void (*visit)(T)) {
    G->visited[i] = isvisited;
    visit(G->Vlist[i].data);

    EBox *eBox = G->Vlist[i].firstarc;

    while (eBox != NULL) {
        int j = eBox->ivex == i ? eBox->jvex : eBox->ivex;
        if (G->visited[j] == isvisited) {
            eBox = eBox->ivex == i ? eBox->iLink : eBox->jLink;
            continue;
        }
        DFS(G, j, visit);
    }
}

//深度优先遍历
//输入：图 G
//输出：遍历图G的每个点
//  图G可能有不同的子图
template<class T>
int DFSTraverse(AMLGraph<T> *G, void (*visit)(T)) {
    if (G->vexnum <= 0) {
        LOGD("error vertex has none!");
        return -1;
    }

    for (int i = 0; i < G->vexnum; ++i) {
        G->visited[i] = unvisited;
    }

    for (int i = 0; i < G->vexnum; ++i) {
        if (G->visited[i] != isvisited)
            DFS(G, i, visit);
    }

    return 0;
}

//广度优先遍历，起点i的连通图
template<class T>
void BFS(AMLGraph<T> *G, int i, void (*visit)(T)) {
    if (G == NULL)
        return;
    if (G->visited[i] == isvisited) {
        return;
    }

    LQueue *queue = creatLQueue(sizeof(int));

    int vex;
    EBox *eBox;

    visit(G->Vlist[i].data);
    G->visited[i] = isvisited;
    enLQueue(queue, &i);

    while (!isLQueueEmpty(queue)) {
        deLQueue(queue, &vex);
        eBox = G->Vlist[vex].firstarc;
        while (eBox != NULL) {
            int j = eBox->ivex == vex ? eBox->jvex : eBox->ivex;
            if (G->visited[j] != isvisited) {
                visit(G->Vlist[j].data);
                G->visited[j] = isvisited;
                enLQueue(queue, &j);
            }
            eBox = eBox->ivex == vex ? eBox->iLink : eBox->jLink;
        }
    }

    destroyLQueue(queue);
}

//广度优先遍历，整图
template<class T>
int BFSTraverse(AMLGraph<T> *G, void (*visit)(T)) {
    if (G == NULL)
        return -1;

    for (int i = 0; i < G->vexnum; i++) {
        G->visited[i] = unvisited;
    }

    for (int i = 0; i < G->vexnum; i++) {
        if (G->visited[i] != isvisited)
            BFS(G, i, visit);
    }
    return 0;
}


template<class T>
int kruskal(const AMLGraph<T> graph, AMLGraph<T> *minTree) {

    //建一个数组由权值从小到大排序
    //由权值由小到大选择边，边连接的两个顶点ui、vi应属于不同树，并将两颗树合并成一个树
    //怎么判断两个顶点ui、vi属于不同树？

    //建一个数组由权值从小到大排序
    //    std::shared_ptr<EBox> *eBoxArray =  new std::shared_ptr<EBox>[graph.arcnum];
    EBox **eBoxArray = new EBox *[graph.arcnum]();
    int j = 0;
    for (int i = 0; i < graph.vexnum; i++) {
        EBox *eBox = graph.Vlist[i].firstarc;
        while (eBox != NULL) {
            int k = 0;
            for (; k < j; k++) {
                if (eBoxArray[k] == eBox) {
                    break;
                }
            }
            if (k == j) {
                eBoxArray[j++] = eBox;
            }
            eBox = eBox->ivex == i ? eBox->iLink : eBox->jLink;
        }
    }
    std::qsort(eBoxArray, graph.arcnum, sizeof(eBoxArray[0]), cmp_ptr<EBox *>);

//    for (int i=0;i<graph.arcnum;i++){
//        LOGD("edge %d,%d,%d",eBoxArray[i]->ivex,eBoxArray[i]->jvex,eBoxArray[i]->weight);
//    }

    //由权值由小到大选择边，边连接的两个顶点ui、vi应属于不同树，并将两颗树合并成一个树
    int *road = new int[graph.vexnum];  //用来判断是否成环
    for (int i = 0; i < graph.vexnum; i++) {
        road[i] = i;
        insertVex(minTree, graph.Vlist[i].data);
    }
    for (int i = 0; minTree->arcnum <= graph.vexnum - 1 && i < graph.arcnum; i++) {
        EBox *eBox = eBoxArray[i];
        int father_i = getFather_Graph(eBox->ivex, road);
        int father_j = getFather_Graph(eBox->jvex, road);
        if (father_i == father_j) {
            continue;
        }
        road[father_i] = father_j;
        insertArc(minTree, graph.Vlist[eBox->ivex].data, graph.Vlist[eBox->jvex].data,
                  eBox->weight);
    }

//    for(int i=0;i<minTree->vexnum;i++){
//        EBox * eBox = minTree->Vlist[i].firstarc;
//        while (eBox!=NULL){
//            LOGD("minTree edge %d,%d,%d",eBox->ivex,eBox->jvex,eBox->weight);
//            eBox = eBox->ivex==i?eBox->iLink:eBox->jLink;
//        }
//    }

    delete[]road;
    delete[]eBoxArray;

    return 0;
}

template<class T>
void Dijkstra(const AMLGraph<T> graph, T head) {
    int hIndex = locateVex(graph, head);
    if (hIndex == -1)
        return;

    MGraph<T> *mGraph = getMGraph(graph);
    if (mGraph == NULL)
        return;


    int vexnum = mGraph->vexnum;
    int *weight = new int[vexnum];  //存放当前head到个顶点的最短路径的值
    int *path = new int[vexnum];    //存放迭代路径
    std::list<int> vexs;            //存放已经找到最短路径的点

    vexs.push_back(hIndex);

    for (int i = 0; i < vexnum; i++) {
        weight[i] = mGraph->edge[hIndex][i];
        path[i] = hIndex;
    }

    int lastIndex = hIndex;  //刚刚求出的最短路径的结点
    int miniIndex = lastIndex;

    while (vexs.size() != vexnum) {
        int miniW = NO_EDGE;  //
        for (int i = 0; i < vexnum; i++) {
            if (weight[lastIndex] < weight[i] && miniW > weight[i]) {
                miniW = weight[i];
                miniIndex = i;
            }
        }
        lastIndex = miniW;
        vexs.push_front(lastIndex);
        path[miniIndex] = hIndex;
        weight[miniIndex] = miniW;


        //找miniIndex出度
        for (int i = 0; i < vexnum; i++) {
            int tmp = weight[miniIndex] + mGraph->edge[miniIndex][i];
            if (tmp < weight[i]) {
                weight[i] = tmp;
                path[i] = miniIndex;
            }
        }
    }

    for (int i = 0; i < vexnum; i++){
        std::string pt;
        std::deque<int> list;
        int j=i;
        while (path[j]!=hIndex){
            list.push_front(path[i]);
            j=path[j];
        }

        auto it  =list.rend();
        while(it != list.rbegin()){
            pt.append((*it++)+" ");
        }

        LOGD("AMLGraph %d->%d ,path=%s miniWeight=%d",hIndex,i,pt.c_str(),weight[i]);
    }

}

#endif //CORENOTE_GRAPH_H
