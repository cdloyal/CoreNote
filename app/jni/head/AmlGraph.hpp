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

#define MAX_VERTEX_NUM 20
//顶点数据类型
typedef int AmlVexType;
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
typedef struct VexBox{
    AmlVexType data;
    struct EBox *firstarc;     //指向第一条依附于该顶点的边
}VexBox;

typedef struct {
    VexBox adjmulist[MAX_VERTEX_NUM];
    int vexnum,arcnum;  //顶点数量，边数量
    AmlKind kind;
    //访问标志数组
    int visited[MAX_VERTEX_NUM];
}AMLGraph;

//创建图
int CreateGraph(AMLGraph *&amlGraph,AmlKind kind);
//销毁图
int destroyGraph(AMLGraph *amlGraph);

//定位一个顶点值为途中的位置，否则返回-1
int locateVex(AMLGraph amlGraph,AmlVexType data);

//返回顶点的值
AmlVexType getVex(AMLGraph *amlGraph,int v);

//赋值
int putVex(AMLGraph *amlGraph,AmlVexType oldData,AmlVexType newData);

//插入一个顶点
int insertVex(AMLGraph *amlGraph,AmlVexType data);

//插入一条弧
int insertArc(AMLGraph *amlGraph,AmlVexType vi,AmlVexType vj,int weight);

//返回顶点值为v的下一个邻接顶点的序号，否怎返回-1
int FirstAdjVex(AMLGraph G,AmlVexType v);

//返回顶点值为v相对于顶点值为w的下一个顶点的序号
int NextAdjVex(AMLGraph G,AmlVexType v,AmlVexType w);

//深度优先遍历，起点i的连通图
void DFS(AMLGraph *G,int i,void (*visit)(AmlVexType));
//深度优先遍历，整图
int DFSTraverse(AMLGraph *G, void (*visit)(AmlVexType));



#endif //CORENOTE_GRAPH_H
