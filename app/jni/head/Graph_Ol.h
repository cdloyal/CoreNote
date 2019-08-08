//
// Created by chenda on 2019/7/30.
//

#ifndef CORENOTE_OLGRAPH_H
#define CORENOTE_OLGRAPH_H

/**
 * 十字链表法（有向图）
 * */

#define MAX_OLGVERTEX_NUM 20
//顶点数据类型
typedef int OLGVexType;
//访问标记
typedef enum {uvisited,visited}VisitFlag;
//图的类型:有向图/网
typedef enum {DG,DN}OLGKind;

//边结构
typedef struct ARCBox{
    VisitFlag mark;               //访问标记
    int headvex;                //弧顶点1
    int tailvex;                //弧顶点2
    struct ARCBox *headLink;   //指向依附于起点head的下一条边
    struct ARCBox *tailLink;   //指向依附于终点tail的下一条边
    int weight;                 //权值
}ARCBox;

//顶点结构
typedef struct OLGVexBox{
    OLGVexType data;
    struct ARCBox *firstIn;     //指向第一条依附于该顶点的边
    struct ARCBox *firstOut;     //指向第一条依附于该顶点的边
}OLGVexBox;

typedef struct {
    OLGVexBox adjmulist[MAX_OLGVERTEX_NUM];
    int vexnum,arcnum;  //顶点数量，边数量
    OLGKind kind;
    //访问标志数组
    int visited[MAX_OLGVERTEX_NUM];
}OLGGraph;

//创建图
int CreateOLGraph(OLGGraph *&olgGraph,OLGKind kind);
//销毁图
int destroyOLGraph(OLGGraph *amlGraph);

//定位一个顶点值为途中的位置，否则返回-1
int locateOLVex(OLGGraph olgGraph,OLGVexType data);

//插入一个顶点
int insertOLVex(OLGGraph *graph,OLGVexType data);

//插入一条弧
int insertOLArc(OLGGraph *amlGraph,OLGVexType vi,OLGVexType vj,int weight);

//递归实现深度遍历邻接点，起点i的连通图
void DFSOL(OLGGraph *G,int i,void (*visit)(OLGVexType));
//深度优先遍历，整图
int DFSOLTraverse(OLGGraph *G, void (*visit)(OLGVexType));

#endif //CORENOTE_OLGRAPH_H
