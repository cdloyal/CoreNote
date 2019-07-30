//
// Created by chenda on 2019/7/30.
//

#include <cstdlib>
#include <log.h>
#include "OLGraph.h"

//创建图
int CreateOLGraph(OLGGraph *&olgGraph,OLGKind kind){
    olgGraph = (OLGGraph*)malloc(sizeof(OLGGraph));
    if(olgGraph==NULL){
        LOGD("OVERFLOW create graph error");
        return -1;
    }
    olgGraph->kind=kind;
    olgGraph->arcnum=0;
    olgGraph->vexnum=0;
    return 0;
}
//销毁图
int destroyOLGraph(OLGGraph *amlGraph){

}

//定位一个顶点值为途中的位置，否则返回-1
int locateOLVex(OLGGraph olgGraph,OLGVexType data){
    for (int i = 0; i < olgGraph.vexnum; ++i) {
        if(olgGraph.adjmulist[i].data == data){
            return i;
        }
    }
    return -1;
}

//插入一个顶点
int insertOLVex(OLGGraph *graph,OLGVexType data){
    for(int i=0;i<graph->vexnum;++i){
        if(graph->adjmulist[i].data==data){
            LOGD("insertVex errot,vertex %d is exist!",data);
            return -1;
        }
    }

    graph->adjmulist[graph->vexnum].data=data;
    graph->adjmulist[graph->vexnum].firstIn=NULL;
    graph->adjmulist[graph->vexnum].firstOut=NULL;
    graph->visited[graph->vexnum]=uvisited;
    graph->vexnum++;

    return 0;
}

//插入一条弧
int insertOLArc(OLGGraph *amlGraph,OLGVexType vi,OLGVexType vj,int weight){
    if(amlGraph==NULL){
        LOGD("error amlGraph==NULL!");
        return -1;
    }

    int indexVi = locateOLVex(*amlGraph,vi);
    if(vi==-1){
        LOGD("error vertex vi not exist!");
        return -1;
    }
    int indexVj = locateOLVex(*amlGraph,vj);
    if(vj==-1){
        LOGD("error vertex vj not exist!");
        return -1;
    }


    ARCBox* eBox = (ARCBox*)malloc(sizeof(ARCBox));
    eBox->headvex = indexVi;
    eBox->tailvex = indexVj;
    eBox->headLink = amlGraph->adjmulist[indexVi].firstIn;
    eBox->tailLink = amlGraph->adjmulist[indexVj].firstOut;
    amlGraph->adjmulist[indexVi].firstIn = eBox;
    amlGraph->adjmulist[indexVj].firstOut = eBox;
    if(amlGraph->kind==DN)
        eBox->weight = weight;

    return 0;
}

//递归实现深度遍历邻接点
//连通图/子图
void DFS(OLGGraph *G,int i,void (*visit)(OLGVexType)){
    G->visited[i] = visited;
    visit(G->adjmulist[i].data);

    ARCBox *eBox = G->adjmulist[i].firstIn;

    while (eBox!=NULL){
        int j = eBox->tailvex;
        if(G->visited[j]==visited){
            eBox=eBox->headLink;
            continue;
        }
        DFS(G,j,visit);
    }
}

//深度优先遍历
int DFSOLTraverse(OLGGraph *G, void (*visit)(OLGVexType)){
    if( G->vexnum<=0){
        LOGD("error vertex has none!");
        return -1;
    }

    for(int i=0;i<G->vexnum;++i){
        G->visited[i] = uvisited;
    }

    for(int i=0;i<G->vexnum;++i){
        if(G->visited[i]!=visited)
            DFS(G,i,visit);
    }

    return 0;
}