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
#include "PrintUtils.h"
#include <list>
#include <string>
#include <forward_list>
#include <deque>
#include <queue>

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
    VisitIf isvisit;       //访问标记
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


//最短路径  https://www.cnblogs.com/thousfeet/p/9229395.html

//迪杰斯特拉算法 https://blog.csdn.net/qq_35644234/article/details/60870719
//顶点head到图上个顶点的最短路径
template<class T>
void Dijkstra(const AMLGraph<T> graph, T head);

//弗洛伊德算法
template<class T>
void floyd(const AMLGraph<T> graph);

//Bellman-Ford算法
template<class T>
void bellman_Ford(const AMLGraph<T> graph);

/**
 * https://blog.csdn.net/qinzhaokun/article/details/48541117
 * https://blog.csdn.net/qq_35644234/article/details/52664108
 * 拓扑结构：
 *  将有向图中的顶点以线性方式进行排序。
 *  假设我非常想学习一门机器学习的课程，但是在修这么课程之前，我们必须要学习一些基础课程，
 *  比如计算机科学概论，C语言程序设计，数据结构，算法等等。那么这个制定选修课程顺序的过程，
 *  实际上就是一个拓扑排序的过程，每门课程相当于有向图中的一个顶点，而连接顶点之间的有向边
 *  就是课程学习的先后关系。不存在环，相互依赖的情况
 *
 * 顶点表示活动、边表示活动间先后关系的有向图称做顶点活动网(Activity On Vertex network)，简称AOV网
 * 顶点表示事件，以有向边表示活动，边上的权值表示活动的开销（如该活动持续的时间），则此带权的有向无环图称为AOE网
 *
 * 拓扑算法：
 * 1、Kahn算法 :   找入度为0的顶点i，存在以顶点i为头，j为尾的边，顶点j的入度数减1；重复。找不到入度为0的顶点，如果还存在没有访问的顶点，代表有环
 *      L← Empty list that will contain the sorted elements
 *      S ← Set of all nodes with no incoming edges
 *      while S is non-empty do
 *          remove a node n from S
 *          insert n into L
 *          foreach node m with an edge e from nto m do
 *              remove edge e from thegraph
 *              ifm has no other incoming edges then
 *                  insert m into S
 *      if graph has edges then
 *          return error (graph has at least onecycle)
 *      else
 *          return L (a topologically sortedorder)
 *
 * 2、DFS：图的深度遍历+遍历到的结点要判断入度+判断是否存在环
 *      L ← Empty list that will contain the sorted nodes
 *      S ← Set of all nodes with no ingoing edges
 *      for each node n in S do
 *          visit(n)
 *      function visit(node n)
 *          if n has not been visited yet && n with noingoing edges then
 *              mark n as visited
 *              for each node m with an edgefrom m to ndo
 *                  visit(m)
 *              add n to L
 * */

template<class T>
int Kahn(const AMLGraph<T> graph);

/**
 * https://blog.csdn.net/qq_35644234/article/details/52664108
 * 关键路径：
 * 顶点表示事件，以有向边表示活动，边上的权值表示活动的开销（如该活动持续的时间），则此带权的有向无环图称为AOE网
 *  AOE网，只有一个起点（入度为0的顶点）和一个终点（出度为0的顶点），研究：
 *  完成整个工程需要的时间
 *  哪些活动是影响工程进度的关键
 *
 * 活动最早发生时间e(i)：V0到Vi最长路径的长度。最长路径，因为要等Vi前面所有活动做完才能开始下一活动
 * 活动最迟发生时间l(i)：不推迟工期的最晚开工时间。
 * 关键活动：e(i)=l(i)的活动
 *
 * 活动最早发生时间e(i)：V0到Vi的最长路径。假设终点最早发生时间e(m)
 *                       节点i前可能有多个活动h1、h2，
 *                       e(i) = max(e(h1)+dut(<i,h1>)、e(h2)-dut(<i,h2>))
 * 活动最迟发生时间l(i)：不推迟工期终点最迟发生时间l(m)=e(m),反推个节点的最迟发生时间
 *                       节点i后可能有多个活动j1、j2，
 *                       l(i) = min(l(j1)-dut(<i,j1>)、l(j2)-dut(<i,j2>))
 *
 *
 * */
template<class T>
int criticalPath(const AMLGraph<T> graph);


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
    mGraph->kind = amlGraph.kind;   //TODO 有向边，下面要改的
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

//flag==1   最小路径
//flag==2   最大路径    取反操作？
template<class T>
void Dijkstra(const AMLGraph<T> graph, T head) {
    int hIndex = locateVex(graph, head);
    if (hIndex == -1){
        LOGD("can not find parm head");
        return;
    }


    MGraph<T> *mGraph = getMGraph(graph);
    if (mGraph == NULL)
        return;


    int vexnum = mGraph->vexnum;
    int *weight = new int[vexnum];  //存放当前head到个顶点的最短路径的值
    int *path = new int[vexnum];    //存放迭代路径
    int *vers = new int[vexnum];    //存放已经找到最短路径的结点
    int vers_size = 0;

    for (int i = 0; i < vexnum; i++) {
//        if (flag == 2) {
//            for (int j = 0; j < vexnum; j++) {
//                if (mGraph->edge[i][j] != NO_EDGE)
//                    mGraph->edge[i][j] = -mGraph->edge[i][j];
//                if(mGraph->edge[i][j] == 0)
//                    mGraph->edge[i][j] = -NO_EDGE;
//            }
//        }

        weight[i] = mGraph->edge[hIndex][i];
        path[i] = hIndex;
    }

    int miniIndex = hIndex;  //暂存，用于比较
    vers[vers_size++] = miniIndex;

//    char string[128];
//    for (int i = 0; i < vexnum; i++) {
//        intArray2String(mGraph->edge[i], vexnum, string);
//        LOGD("edge weight ： %s", string);
//    }

    while (vers_size != vexnum) {
        int miniW = NO_EDGE;  //

//        intArray2String(vers, vers_size, string);
//        LOGD("Dijkstra vers ： %s", string);

        for (int i = 0; i < vexnum; i++) {
            int j = 0;
            for (; j < vers_size; j++) {
                if (vers[j] == i)
                    break;
            }

            if (vers[j] == i) {
//                LOGD("Dijkstra (vers[j]==i) i=%d", i);
                continue;
            }

//            if (weight[lastIndex] <= weight[i] && miniW >= weight[i]) {
            if (miniW >= weight[i]) {
                miniW = weight[i];
                miniIndex = i;
            }
        }

//        intArray2String(weight, vexnum, string);
//        LOGD("Dijkstra weight ： %s", string);
//        LOGD("Dijkstra miniIndex = %d", miniIndex);

        vers[vers_size++] = miniIndex;
        weight[miniIndex] = miniW;

        //找miniIndex出度
//        for (int i = 0; i < vexnum; i++) {
//            int j = 0;
//            for (; j < vers_size; j++) {
//                if (vers[j] == i)
//                    break;
//            }
//
//            if (vers[j] == i) {
////                LOGD("Dijkstra (vers[j]==i) i=%d", i);
//                continue;
//            }
//            if (weight[miniIndex] == NO_EDGE || mGraph->edge[miniIndex][i] == NO_EDGE)
//                continue;
//            int tmp = weight[miniIndex] + mGraph->edge[miniIndex][i];
//            if (tmp < weight[i]) {
//                weight[i] = tmp;
//                path[i] = miniIndex;
//            }
//        }

        //贪心策略
        for (int i = 0; i < vexnum; i++) {
            if (weight[miniIndex] == NO_EDGE || mGraph->edge[miniIndex][i] == NO_EDGE)
                continue;
            int tmp = weight[miniIndex] + mGraph->edge[miniIndex][i];
            if (tmp < weight[i]) {
                weight[i] = tmp;
                path[i] = miniIndex;
            }
        }

    }


//    if (flag == 2) {
//        for (int i = 0; i < vexnum; i++) {
//            for (int j = 0; j < vexnum; j++) {
//                if(mGraph->edge[i][j] == -NO_EDGE)
//                    mGraph->edge[i][j] = 0;
//                if (mGraph->edge[i][j] != NO_EDGE)
//                    mGraph->edge[i][j] = -mGraph->edge[i][j];
//            }
//
//            if(weight[i] == -NO_EDGE)
//                weight[i] = 0;
//            if (weight[i] != NO_EDGE)
//                weight[i] = -weight[i];
//        }
//    }

    for (int i = 0; i < vexnum; i++) {
//        LOGD("Dijkstra path[%d]=%d", i, path[i]);

        std::string pt("");
        std::deque<int> list;
        int j = i;
        list.push_front(j);
        while (path[j] != hIndex) {
            list.push_front(path[j]);
            j = path[j];
        }
        list.push_front(hIndex);

        auto it = list.begin();
        while (it != list.end()) {
//            LOGD("Dijkstra (*it++) + \" \" = %d", (*it));
            pt += std::to_string((*it));
            pt += " ";
            it++;
//            pt.append((*it++) + " ");
        }
        LOGD("Dijkstra %d->%d ,path=%s miniWeight=%d", hIndex, i, pt.c_str(), weight[i]);
    }
}

template<class T>
void floyd(const AMLGraph<T> graph) {
    /**
     * 佛洛依德算法：
     *
     * D[i][j] = (D[i][j]>D[i][k]+D[k][j])?D[i][k]+D[k][j]:D[i][j]
     * 有N个顶点就迭代N次
     *
     * D[i][j] 表示顶点i(第i个顶点)到顶点j(第j个顶点)的距离
     * P[i][j] 表示顶点i到顶点j经过了P[i][j]记录的值所表示的顶点,即上面的k
     * */

    MGraph<T> *mGraph = getMGraph(graph);
    if (mGraph == NULL)
        return;

    int vexnum = mGraph->vexnum;
    int **D, **P;
    for (int i = 0; i < vexnum; i++) {
        D = new int *[vexnum];
        P = new int *[vexnum];
    }
    for (int i = 0; i < vexnum; i++) {
        D[i] = new int[vexnum];
        P[i] = new int[vexnum];
    }
    for (int i = 0; i < vexnum; i++) {
        for (int j = 0; j < vexnum; j++) {
            D[i][j] = mGraph->edge[i][j];
            P[i][j] = j;
        }
    }

    for (int k = 0; k < vexnum; k++) {
        for (int i = 0; i < vexnum; i++) {
            for (int j = 0; j < vexnum; j++) {
                if (D[i][k] == NO_EDGE || D[k][j] == NO_EDGE)
                    continue;
                if (D[i][j] > D[i][k] + D[k][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                    P[i][j] = k;
                }
            }
        }
    }

//    char string[128];
//    for (int i = 0; i < vexnum; i++) {
//        intArray2String(D[i], vexnum, string);
//        LOGD("floyd D[%d] = %s", i,string);
//        intArray2String(P[i], vexnum, string);
//        LOGD("floyd P[%d] = %s", i,string);
//    }
}


template<class T>
int Kahn(const AMLGraph<T> graph) {

    int *indegrees = new int[graph.vexnum](); // 记录每个顶点当前的入度
    int *list = new int[graph.vexnum];  //拓扑顺序结果
    int visitIndex = 0, listSize = 0;

    for (int i = 0; i < graph.vexnum; i++) {
        EBox *eBox = graph.Vlist[i].firstarc;
        while (eBox != NULL) {
            eBox->isvisit = unvisited;    //边设置为未访问
            if (eBox->ivex == i) {
                indegrees[eBox->jvex]++;
                eBox = eBox->iLink;
            } else {
                eBox = eBox->jLink;
            }
        }

//        graph.visited[i] = unvisited;   //顶点设置为未访问
        list[i] = -1;
    }

    for (int i = 0; i < graph.vexnum; i++) {
        if (indegrees[i] == 0) {
            list[listSize++] = i;
            graph.visited[i] = isvisited;
        }
    }

    while (visitIndex != listSize) {
        EBox *eBox = graph.Vlist[list[visitIndex]].firstarc;
        while (eBox != NULL) {
            if (eBox->ivex == list[visitIndex]) {
                eBox->isvisit = isvisited;    //边设置为访问
                if ((--indegrees[eBox->jvex]) == 0)
                    list[listSize++] = eBox->jvex;
                eBox = eBox->iLink;
            } else {
                eBox = eBox->jLink;
            }
        }
        visitIndex++;
    }

    for (int i = 0; i < graph.vexnum; i++) {
        EBox *eBox = graph.Vlist[i].firstarc;
        while (eBox != NULL) {
            if (eBox->isvisit == unvisited) {
                LOGD("Kahn 拓扑排序出错，拓扑结构存在环");
                delete[]indegrees;
                return -1;
            }
            eBox = eBox->ivex == i ? eBox->iLink : eBox->jLink;
        }
    }

    char string[128];
    intArray2String(list, listSize, string);
    LOGD("Kahn = %s", string);

    delete[]indegrees;

    return 0;
}

template<class T>
int criticalPath(const AMLGraph<T> graph) {
    if (Kahn(graph) == -1) {
        LOGD("图存在环，不是拓扑结构");
        return -1;
    }

    /**
    * 活动最早发生时间e(i)：V0到Vi的最长路径。假设终点最早发生时间e(m)
    *                       节点i前可能有多个活动h1、h2，
    *                       e(i) = max(e(h1)+dut(<i,h1>)、e(h2)-dut(<i,h2>))
    * 活动最迟发生时间l(i)：不推迟工期终点最迟发生时间l(m)=e(m),反推个节点的最迟发生时间
    *                       节点i后可能有多个活动j1、j2，
    *                       l(i) = min(l(j1)-dut(<i,j1>)、l(j2)-dut(<i,j2>))

    * */

    //用DFS拓扑排序获得活动最早发生时间e(i)


    //逆拓扑排序求活动最迟发生时间l(i)

    //比较e(i)==l(i)，求出关键路径


}


#endif //CORENOTE_GRAPH_H
