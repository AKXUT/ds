/**
 * Created by David on Tue Oct 26 18:28:33 2021
 *
 * Descretption: 课件上的Prim算法实现
 *
 * Last Modified: 
 */
#include <stdio.h>
#include <stdlib.h>
#define MaxWeight 10000
#define MAX_GRAPH 50
#define INF 100000

// 邻接矩阵图的定义和操作如下：
typedef struct {
  int V;  // number of verteies
  int E;  // number of edges
  int adjMatrix[MAX_GRAPH][MAX_GRAPH];  // use a 2-D array to store edges
} AdjMWGraph;

void InitGraph(AdjMWGraph *p) {
  int i, j;
  p->V = 0;
  p->E = 0;
  for (i = 0; i < MAX_GRAPH; i++)
    for (j = 0; j < MAX_GRAPH; j++)
      p->adjMatrix[i][j] = INF;
}

void CreateGraph(AdjMWGraph *p) {
  int n, m, i;
  int v, u, weight;
  // printf("please input the number of verteies: \n");
  scanf("%d", &n);
  // printf("please input the number of edges: \n");
  scanf("%d", &m);
  p->V = n;
  p->E = m;
  for (i = 0; i < p->E; i++) {
    // printf("input edge: ");
    scanf("%d%d%d", &v, &u, &weight);
    p->adjMatrix[v][u] = weight;
    p->adjMatrix[u][v] = weight;
  }
}

void PrintGraph(AdjMWGraph *p) {
  int i, j;
  printf("a graph with %d verteies and %d edges\n", p->V, p->E);
  for (i = 0; i < p->V; i++)
    for (j = i; j < p->V; j++) {
      if (p->adjMatrix[i][j] != INF)
        printf("%d -- %d: %d\n", i, j, p->adjMatrix[i][j]);
    }
}

// 最小生成树的数据结构和操作定义
typedef struct {
  int vertex;
  int weight;
} MinSpanTree;
 
void Prim(AdjMWGraph G, MinSpanTree closeVertex[]) {
  int n = G.V, minCost;
  int *lowCost = (int *)malloc(sizeof(int)*n); // 定义lowCost一维数组
  int i, j, k;
  for(i = 1; i < n; i ++) { //更新 lowCost 和 closeVertex 数组
    lowCost[i] = G.adjMatrix[0][i];
    closeVertex[i].vertex = 0;
    closeVertex[i].weight = G.adjMatrix[0][i];
  }
  lowCost[0] = -1;
  for(i = 1; i < n; i++) {  // 寻找当前最小权值的边所对应的弧尾顶点k
    minCost = MaxWeight;
    
    for(j = 1; j < n; j++) {   // 选中最小割边
      if(lowCost[j] < minCost && lowCost[j] > 0) {
	minCost = lowCost[j];
	k = j;
      }
    }
    printf("(%d, %d): %d\n", closeVertex[k].vertex , k, minCost);
    lowCost[k] = -1;
    for(j = 1; j < n; j++) {   // 更新 lowCost 和 closeVertex 数组
      if(G.adjMatrix[k][j] < lowCost[j])  {
	lowCost[j] = G.adjMatrix[k][j];
	closeVertex[j].vertex = k;
	closeVertex[j].weight = G.adjMatrix[k][j];
      }
    }
  }
}								

void PrintArr(int a[], int n) {
  printf("[");
  for (int i = 0; i < n; ++i) {
    printf("%d ", a[i]);
  }
  printf("]\n");
}

int main() {
  MinSpanTree *t;
  AdjMWGraph G;
  InitGraph(&G);
  CreateGraph(&G);
  t = (MinSpanTree *)malloc(sizeof(MinSpanTree) * G.V);
  Prim(G, t);
  
  return 0;
}

/* 
输入：
7 10
0 1 50
0 2 60
1 3 65
1 4 40
2 3 52
2 6 45
3 6 42
3 4 50
3 5 30
4 5 70

输出：
(0, 1): 50
(1, 4): 40
(4, 3): 50
(3, 5): 30
(3, 6): 42
(6, 2): 45

 */

