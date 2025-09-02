/*******************************************************
 * Created by David Song in 2022-1-16
 *
 * Note:
 *   1. graph implement using adjacent matrix
 *   2. Algorithms in c Part 5  p22
 ******************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "graph_matrix.h"

struct graph {int V; int E; int **adj; };

Edge EDGE(int v, int w) {
  Edge e = {v, w};
  return e;
}

int ** MatrixInt(int r, int c, int val) {
  int i, j;
  int **t = malloc(r * sizeof(int *));
  for (i = 0; i < r; i++)
    t[i] = malloc(c * sizeof(int));
  for (i = 0; i < r; i++)
    for (j = 0; j < c; j++)
      t[i][j] = val;
  return t;
}

// 图初始化，创建二维数组邻接矩阵，填充0值
Graph GraphInit(int V) {
  Graph G = malloc(sizeof(Graph));
  G->V = V;
  G->E = 0;
  G->adj = MatrixInt(V, V, 0);
  return G;
}

// 插入一条边
void GraphInsertE(Graph G, Edge e) {
  int v = e.v, w = e.w;
  if (G->adj[v][w] == 0)
    G->E++;
  G->adj[v][w] = 1;
  G->adj[w][v] = 1;
}

// 删除一条边
void GraphRemoveE(Graph G, Edge e) {
  int v = e.v, w = e.w;
  if (G->adj[v][w] == 1)
    G->E--;
  G->adj[v][w] = 0;
  G->adj[w][v] = 0;
}

// 返回所有边
int GraphEdges(Edge a[], Graph G) {
  int v, w, E = 0;
  for (v = 0; v < G->V; ++v) {
    for (w = v + 1; w < G->V; ++w) {
      if (G->adj[v][w] == 1)
	a[E++] = EDGE(v, w);
    }
  }
  return E;
}

void GraphShow(Graph G) {
  int i, j;
  printf("vertices: %d  edges: %d", G->V, G->E);
  for (i = 0; i < G->V; ++i) {
    printf("%2d:", i);
    for (j = 0; j < G->V; ++j) 
      if (G->adj[i][j] == 1)
	printf("%3d", j);
    puts("");
  }
}


/*
10 11
-----
3 7
1 4
7 8
0 5
5 2
3 8
2 9
0 6
4 9
2 6
5 4
*/

int main(int argc, char *argv[])
{
  int n, m, v, w, i;
  Graph G;
  puts("Input the number of verticise and edges:");
  scanf("%d%d", &n, &m);
  G = GraphInit(n);

  puts("Input the edges:");
  for (i = 0; i < m; ++i) {
    scanf("%d%d", &v, &w);
    GraphInsertE(G, EDGE(v, w));
  }
  GraphShow(G);
  return 0;
}
