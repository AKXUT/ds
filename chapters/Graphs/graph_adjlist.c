/*******************************************************
 * Created by David Song in 2022-1-16
 *
 * Note:
 *   1. graph implement using adjacent list
 *   2. Algorithms in c Part 5  p22
 ******************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "graph_matrix.h"

typedef struct node * link;
struct node { int v; link next;};

struct graph {int V; int E; link *adj; };

link NEW(int v, link next) {
  link x = malloc(sizeof(*x));
  x->v = v;
  x->next = next;
  return x;
}

Edge EDGE(int v, int w) {
  Edge e = {v, w};
  return e;
}

// 图初始化，创建二维数组邻接矩阵，填充0值
Graph GraphInit(int V) {
  int i;
  Graph G = malloc(sizeof(Graph));
  G->V = V;
  G->E = 0;
  G->adj = malloc(V * sizeof(link));
  for (i = 0; i < G->V; ++i) G->adj[i] = NULL;
  return G;
}

// 插入一条边
void GraphInsertE(Graph G, Edge e) {
  int v = e.v, w = e.w;
  G->adj[v] = NEW(w, G->adj[v]);
  G->adj[w] = NEW(v, G->adj[w]);
  G->E++;
}

// 删除一条边
void GraphRemoveE(Graph G, Edge e) {
  int v = e.v, w = e.w;
  // TODO: not finished yet
}

// 返回所有边
int GraphEdges(Edge a[], Graph G) {
  int v, E = 0;
  link t;
  for (v = 0; v < G->V; ++v) 
    for (t = G->adj[v]; t != NULL ; t = t->next) 
      if (v < t->v)
	a[E++] = EDGE(v, t->v);

  return E;
}

void GraphShow(Graph G) {
  int i;
  link t;
  printf("vertices: %d  edges: %d\n", G->V, G->E);
  for (i = 0; i < G->V; ++i) {
    printf("%2d:", i);
    for (t = G->adj[i]; t != NULL; t = t->next) 
      printf("%3d", t->v);
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

