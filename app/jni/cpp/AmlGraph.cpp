//
// Created by chenda on 2019/7/28.
//
#include <cstdlib>
#include <log.h>
#include <LQueue.h>
#include "AmlGraph.hpp"

/**
 *
 * https://blog.csdn.net/doubleselect/article/details/40151877
 *
 * 图的定义：顶点和边的集合，顶点有穷非空,边可空。G(V,E)
 *
 * 无向边Edge， 无序偶(Vi,Vj)表示
 * 有向边Arg弧，有序偶<Vi,Vj>表示
 *
 * 无向完全图：任意两个顶点之间都存在边。边个数：n(n-1)/2
 * 有向完全图：任意两个顶点之间都存在互为相反的两条弧。边个数：n(n-1)
 *
 * 稀疏图和稠密图：稀疏图边或弧条数<nlogn
 *
 * 权：边或弧上的数字
 * 网：每条边上带有权的图
 *
 * 子图：V1是V2的子集，E1是E2的自己，则G1是G2的子图
 *
 * 图的顶点与边之间的关系：
 *
 * 无向图
 * 邻接点Adjacent，V1与V2有边连接，V1、V2是邻接点。
 * 度TD(V),顶点V相关联的边的数目
 *
 * 有向图
 * <V1,V2>,V1邻接到V2，V2邻接自V1
 * 入度ID(V),顶点V为头的弧的数目
 * 初读OD(V),顶点V为尾的弧的数目
 * 度TD(V)=ID(V)+OD(V)
 *
 * 路径
 * 回路或环路，第一个顶点和最后一个顶点相同的路径
 *
 * 简单路径：顶点不重复的路径
 * 简单环：除第一个顶点和最后一个顶点相同外的环
 *
 * 连通图：在无向图G中，如果从顶点V1到V2有路径，则V1和V2是连通的。
 *          图中任意顶点Vi和Vj都是连通的，则称为连通图
 * 连通分量：无向图中的极大连通子图
 *
 * 强连通图和强连通分量：针对有向图
 *
 * 一个连通图生成树是极小的连通子图，含有图中的全部n个节点，但只有足以构成一颗树的n-1条边
 * 如果一个有向图恰有一个顶点入度为0，其余顶点的入度都为1，则是一颗有向树
 *
 * 邻接矩阵（无向图）
 *  一维数组存储顶点
 *  二位数组存储边
 *  对称矩阵 A[i][j]=A[j][i]
 *  A[i][j]=1，代表顶点Vi和Vj存在边，是邻接点
 *  Vi的度等于A[i][0`n]，i行的元素和
 *
 * 邻接矩阵（有向图）
 *   A[i][j]=1，代表顶点Vi指向Vj
 *   入度：列元素之和
 *   出度：行元素之和
 *
 * 邻接矩阵（网）
 *  A[i][j]=k，代表顶点Vi指向Vj，权值为k。k等于正无穷（大于边上权值的最大值），Vi不指向Vj；i=j,K=0,没有指向自身的路径
 *
 * 邻接表
 *  邻接矩阵，使用数组进行存储，存在浪费内存；要预先分配内存，由于内存分配不合理，需要重新分配内存
 *  数组与链表结合一起存在
 *  顶点表节点结构：
 *      data    first
 *  边表结构
 *      index   next
 *
 *      typedef GRAPHDATATYPE int;
 *      typedef struct GraphArrayNode{
 *           GRAPHDATATYPE data;
 *           struct GraphNode* fist;
 *       };
 *       typedef struct GraphNode{
 *           int nextIndex;
 *           struct GraphNode* next;
 *       };
 *       #define Len 10
 *       typedef struct Graph{
 *           struct GraphArrayNode array[Len];
 *           int size;
 *       };
 *  缺陷：邻接表对于有向图，需要做基于出度的表和基于入度的表（逆邻接表）
 *
 * 十字链表(有向表)
 *  顶点表节点结构：
 *      data    firstIn     firstOut
 *  边表节点结构
 *      tailVex headVex headLink tailLink
 *
 * 邻接多重表(无向表)
 *  顶点表节点结构：
 *      data    first
 *  边表结构
 *      iVex    iLink   jVex    jLink
 *
 * 边集数组
 *  顶点数组
 *      data
 *  边数组
 *      begin end weight
 *
 * 图的普通遍历：有可能重复遍历，有可能漏了遍历
 *
 * 深度优先遍历DFS
 *  右手原则：再没有遇到重复顶点的情况下，分叉路口始终是面对分叉口的右手边走，
 *           每路过一个顶点就做一个记号，遇到重复顶点，面对分叉口的第二条右手边的路，
 *           都重复了就返回
 *  递归过程、像树的前序遍历
 *
 * 哈密尔顿路径：
 *  图G中的哈密尔顿路径是指经过图G中每个顶点且只经过一次的一条路径。
 * 哈密尔顿回路
 *
 *
 * */


//创建图
int CreateGraph(AMLGraph *&amlGraph,AmlKind kind){
    amlGraph = (AMLGraph*)malloc(sizeof(AMLGraph));
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
int locateVex(AMLGraph amlGraph,AmlVexType data){
    for (int i = 0; i < amlGraph.vexnum; ++i) {
        if(amlGraph.adjmulist[i].data == data){
            return i;
        }
    }
    return -1;
}

//插入一个顶点
int insertVex(AMLGraph *amlGraph,AmlVexType data){
    for(int i=0;i<amlGraph->vexnum;++i){
        if(amlGraph->adjmulist[i].data==data){
            LOGD("insertVex errot,vertex %d is exist!",data);
            return -1;
        }
    }

    amlGraph->adjmulist[amlGraph->vexnum].data=data;
    amlGraph->adjmulist[amlGraph->vexnum].firstarc=NULL;
    amlGraph->visited[amlGraph->vexnum]=unvisited;
    amlGraph->vexnum++;

    return 0;
}

//插入一条弧
int insertArc(AMLGraph *amlGraph,AmlVexType vi,AmlVexType vj,int weight){
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
    eBox->iLink = amlGraph->adjmulist[indexVi].firstarc;
    eBox->jLink = amlGraph->adjmulist[indexVj].firstarc;
    amlGraph->adjmulist[indexVi].firstarc = eBox;
    amlGraph->adjmulist[indexVj].firstarc = eBox;
    if(amlGraph->kind==UDN)
        eBox->weight = weight;

    return 0;
}

//递归实现深度遍历邻接点
//连通图/子图
void DFS(AMLGraph *G,int i,void (*visit)(AmlVexType)){
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
int DFSTraverse(AMLGraph *G,void (*visit)(AmlVexType)){
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
void BFS(AMLGraph *G,int i,void (*visit)(AmlVexType)){
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
int BFSTraverse(AMLGraph *G, void (*visit)(AmlVexType)){
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


