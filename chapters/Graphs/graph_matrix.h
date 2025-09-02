typedef struct { int v; int w; } Edge;
Edge EDGE(int, int);

typedef struct graph *Graph;
Graph GraphInit(int);
void GraphInsertE(Graph, Edge);
void GraphRemoveE(Graph, Edge);
int GraphEdges(Edge [], Graph G);
Graph GraphCopy(Graph);
void GraphShow(Graph);
void GraphDestroy(Graph);


