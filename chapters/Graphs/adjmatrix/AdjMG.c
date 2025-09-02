/******************************************************
 * Author:       David  Song                           *
 * Mail:         songxin@xaut.edu.cn                   *
 * Create Date: Fri May  6 10:18:22 2022               *
 * Last Modify:                                        *
 * Comment: 根据课件上的定义创建邻接矩阵图                 *
 ******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "SeqList.h"

typedef char DataType;		
#define MaxSize 100
#define MaxVertices 10
#define MaxEdges 100
#define MaxWeight 10000

typedef struct {
  SeqList Vertices;
  int edge[MaxVertices][MaxVertices];
  int numOfEdges;	
} AdjMWGraph;	

typedef struct {
  int row;	//行下标
  int col;	//列下标
  int weight;	//权值
} RowColWeight;


void Initiate(AdjMWGraph *G, int n) {
  int i, j;
  for(i = 0; i < n; i++)
    for(j = 0; j < n; j++) 
      if(i == j) G->edge[i][j] = 0;
      else G->edge[i][j] = MaxWeight;
  G->numOfEdges = 0;		/*边的条数置为0*/
  ListInitiate(&G->Vertices);	/*顺序表初始化*/
}

void InsertVertex(AdjMWGraph *G, DataType vertex) {
  ListInsert(&G->Vertices, G->Vertices.size, vertex);
}

void InsertEdge(AdjMWGraph *G, int v1, int v2, int weight) {
  if(v1 < 0 || v1 > G->Vertices.size || v2 < 0 || v2 > G->Vertices.size) {
    printf("参数v1或v2越界出错! in InsertEdge\n");
    exit(1);
  }
  G->edge[v1][v2] = weight;
  G->numOfEdges++;
}

void DeleteEdge(AdjMWGraph *G, int v1, int v2) {
  if(v1 < 0 || v1 > G->Vertices.size || v2 < 0 || v2 > G->Vertices.size || v1 == v2) {
    printf("参数v1或v2越界出错! in DeleteEdg\n");
    exit(1);
  }
  if(G->edge[v1][v2] == MaxWeight || v1 == v2){
    printf("该边不存在!\n");
    exit(0);
  }
  G->edge[v1][v2] = MaxWeight;
  G->numOfEdges--;
}


int GetFirstVex(AdjMWGraph G, int v) {
  int col;
  if(v < 0 || v > G.Vertices.size) {
    printf("参数v1越界出错!\n");
    exit(1);
  }
  for(col = 0; col <= G.Vertices.size; col++)
    if(G.edge[v][col] > 0 && G.edge[v][col] < MaxWeight)
      return col;
  return -1;
}

int GetNextVex(AdjMWGraph G, int v1, int v2) {
  int col;
  if(v1 < 0 || v1 > G.Vertices.size || v2 < 0 || v2 > G.Vertices.size) {
    printf("参数v1或v2越界出错!\n");
    exit(1);
  }
  for(col = v2+1; col <= G.Vertices.size; col++)
    if(G.edge[v1][col] > 0 && G.edge[v1][col] < MaxWeight)
      return col;
  return -1;
}


void CreatGraph(AdjMWGraph *G, DataType V[],  int n, RowColWeight E[],int e) {
  int i, k; /*在图G中插入n个顶点信息V和e条边信息E*/
  Initiate(G, n);  /*顶点顺序表初始化*/
  for(i = 0; i < n; i++)
    InsertVertex(G, V[i]);		/*顶点插入*/
  for(k = 0; k < e; k++) {
    printf("%d - %d: %d\n", E[k].row, E[k].col, E[k].weight);
    InsertEdge(G, E[k].row, E[k].col, E[k].weight);  /*边插入*/
  }
} 

int main(void)
{
  AdjMWGraph g1;
  DataType a[] = {'A','B','C','D','E'};
  RowColWeight rcw[] = {{0,1,10},{0,4,20},{1,3,30},{2,1,40},{3,2,50}};
  int n = 5, e = 5, i, j;
  CreatGraph(&g1, a, n, rcw, e);
  DeleteEdge(&g1, 0, 4);
  // DeleteVertex(&g1, 3);
  printf("顶点集合为：");
  for(i = 0; i < g1.Vertices.size; i++)  printf("%c   ", g1.Vertices.a[i]);
  printf("权值集合为：\n");
  for(i = 0; i < g1.Vertices.size; i++) {
    for(j = 0; j < g1.Vertices.size; j++)
      printf("%5d   ", g1.edge[i][j]);
    printf("\n");
  }
  return 0;
}
  
