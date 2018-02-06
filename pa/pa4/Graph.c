//-----------------------------------------------------------------------------
//  Graph.c
//  Ameer Khan
//  ammukhan
//  CS101 PA4
//  Implementation file for Graph ADT
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

// structs --------------------------------------------------------------------

// private GraphObj type
typedef struct GraphObj {
	List *adjacent;
	char *color;
	int *parent;
	int *distance;
	int order;
	int size;
	int source;
} GraphObj;

// Constructors-Destructors ---------------------------------------------------

// newGraph()
// returns a Graph pointing to a newly created GraphObj representing a graph having n vertices and no edges
Graph newGraph(int n) {
	Graph G = malloc(sizeof(GraphObj));
	G->adjacent = calloc(sizeof(List),(n+1));
	G->color = calloc(sizeof(char),(n+1));
	G->parent = calloc(sizeof(int),(n+1));
	G->distance = calloc(sizeof(int),(n+1));
	G->order = n;
	G->size = 0;
	G->source = NIL;

	for (int i = 0; i <= n; i++) {
		G->adjacent[i] = newList();
		G->color[i] = 'w';
		G->parent[i] = NIL;
		G->distance[i] = INF;
	}
	return G;
}

// freeGraph()
// frees all dynamic memory associated with the Graph *pG, 
// then sets the handle *pG to NULL
void freeGraph(Graph* pG) {
	for (int i = 0; i <= getOrder(*pG); i++) {
		freeList(&(*pG)->adjacent[i]);
	}
	free((*pG)->adjacent);
	free((*pG)->color);
	free((*pG)->parent);
	free((*pG)->distance);
	free(*pG);
	*pG = NULL;

}

// Access Functions --------------------------------------------------------

// getOrder()
// returns order
int getOrder(Graph G) {
	if (G == NULL) {
		printf("getOrder() Error: calling getOrder() on NULL graph\n");
		exit(1);
	}
	return G->order;

}

// getSize
// returns size
int getSize(Graph G) {
	if (G == NULL) {
		printf("getSize() Error: calling getSize() on NULL graph\n");
		exit(1);
	}
	return G->size;
}

// getSource
// returns the source vertex most recently used in function BFS(), 
// or NIL if BFS() has not yet been called
int getSource(Graph G) {
	if (G == NULL) {
		printf("getSource() Error: calling getSource() on NULL graph\n");
		exit(1);
	}
	return G->source;
}

// getParent()
// will return the parent of vertex u in the Breadth-First tree created by BFS(), 
// or NIL if BFS() has not  yet been called
// precondition 1 <= u <= getOrder(G)
int getParent(Graph G, int u) {
	if (G == NULL) {
		printf("getParent() Error: calling getParent() on NULL graph\n");
		exit(1);
	}
	if (u > getOrder(G) || u < 1) {
		printf("getParent() Error: calling getParent() on vertex u that is out of bounds\n");
		exit(1);
	}
	return G->parent[u];
}

// getDist()
// returns the distance from the most recent BFS source to vertex u, 
// or INF if BFS() has not yet been called
// precondition 1 <= u <= getOrder(G)
int getDist(Graph G, int u) {
	if (G == NULL) {
		printf("getDist() Error: calling getDist() on NULL graph\n");
		exit(1);
	}
	if (u > getOrder(G) || u < 1) {
		printf("getDist() Error: calling getDist() on vertex u that is out of bounds\n");
		exit(1);
	}

	if (getSource(G) == NIL){
		return INF;
	} else {
		return G->distance[u];
	}
}

// getPath()
// appends to the List L the vertices of a shortest path in G from source to u, 
// or appends to L the value NIL if no such path exists
// has the precondition getSource(G)!=NIL, so BFS() must be called before getPath()
// precondition 1 <= u <= getOrder(G)
void getPath(List L, Graph G, int u){
	if (G == NULL) {
		printf("getPath() Error: calling getPath() on NULL graph\n");
		exit(1);
	}
	if (getSource(G) == NIL) {
		printf("getPath() Error: calling getPath() on NIL graph\n");
		exit(1);
	}
	if (u > getOrder(G) || u < 1) {
		printf("getPath() Error: calling getPath() on vertex u that is out of bounds\n");
		exit(1);
	}

	if (u == getSource(G)) {
		append(L, u);
	} else if (getParent(G, u) == NIL) {
		append(L, NIL);
	} else {
		getPath(L, G, getParent(G, u));
		append(L, u);
	}
}

// Manipulation procedures ----------------------------------------------------

// makeNull()
// deletes all edges of G, restoring it to its original (no edge) state
void makeNull(Graph G) {
	if (G == NULL) {
		printf("makeNull() Error: calling makeNull() on NULL graph\n");
		exit(1);
	}

	for (int i = 1; i <= getOrder(G); i++) {
		clear(G->adjacent[i]);
		G->color[i] = 'w';
		G->parent[i] = NIL;
		G->distance[i] = INF;
	}
	G->source = NIL;
	G->size = 0;
}

// addEdge()
// inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, 
// and v to the adjacency List of u
// has the precondition that their two int arguments must lie in the range 1 to getOrder(G)
void addEdge(Graph G, int u, int v) {
	if (G == NULL) {
		printf("addEdge() Error: calling addEdge() on NULL graph\n");
		exit(1);
	}
	if (u > getOrder(G) || u < 1) {
		printf("addEdge() Error: calling addEdge() on vertex u that is out of bounds\n");
		exit(1);
	}
	if (v > getOrder(G) || v < 1) {
		printf("addEdge() Error: calling addEdge() on vertex v that is out of bounds\n");
		exit(1);
	}

	addArc(G, u, v);
	addArc(G, v, u);
	G->size--;
}

// addArc()
// inserts a new directed edge joining u to v, i.e. v is added to the adjacency List of u, 
// but not u to the adjacency List of v
// has the precondition that their two int arguments must lie in the range 1 to getOrder(G)
void addArc(Graph G, int u, int v) {
	if (G == NULL) {
		printf("addArc() Error: calling addArc() on NULL graph\n");
		exit(1);
	}
	if (u > getOrder(G) || u < 1) {
		printf("addArc() Error: calling addArc() on vertex u that is out of bounds\n");
		exit(1);
	}
	if (v > getOrder(G) || v < 1) {
		printf("addArc() Error: calling addArc() on vertex v that is out of bounds\n");
		exit(1);
	}

	moveFront(G->adjacent[u]);

	while (index(G->adjacent[u]) > -1 && v > get(G->adjacent[u])) {
		moveNext(G->adjacent[u]);
	}
	if (index(G->adjacent[u]) == -1) {
		append(G->adjacent[u], v);
	} else {
		insertBefore(G->adjacent[u], v);
	}
	G->size++;
}

// BFS()
// runs the BFS algorithm on the Graph G with source s, 
// setting the color, distance, parent, and source fields of G accordingly
void BFS(Graph G, int s) {
	if (G == NULL) {
		printf("BFS() Error: calling BFS() on NULL graph\n");
		exit(1);
	}
	if (s > getOrder(G) || s < 1) {
		printf("BFS() Error: calling BFS() on vertex u that is out of bounds\n");
		exit(1);
	}

	int u;
	int v;
	G->source = s;

	for (int i = 0; i <= getOrder(G); i++) {
		G->color[i] = 'w';
		G->parent[i] = NIL;
		G->distance[i] = INF;
	}

	G->color[s] = 'w';
	G->parent[s] = NIL;
	G->distance[s] = 0;

	List B = newList();
	append(B, s);

	while (length(B) != 0) {
		u = front(B);
		deleteFront(B);
		moveFront(G->adjacent[u]);
		while (index(G->adjacent[u]) != -1) {
			v = get(G->adjacent[u]);
			if (G->color[v] == 'w') {
				G->color[v] = 'g';
				G->parent[v] = u;
				G->distance[v] = (G->distance[u] + 1);
				append(B, v);
			}
			moveNext(G->adjacent[u]);
		}
		G->color[u] = 'b';
	}
	freeList(&B);
}

// Other methods ---------------------------------------------------------

// printGraph()
// prints the adjacency list representation of G to the file pointed to by out
void printGraph(FILE* out, Graph G) {
	if (out == NULL) {
		printf("printGraph() Error: calling printGraph() on NULL file\n");
		exit(1);
	}
	if (G == NULL) {
		printf("printGraph() Error: calling printGraph() on NULL graph\n");
		exit(1);
	}

	for (int i = 1; i <= getOrder(G); i++) {
		fprintf(out, "%d: ", i);
		printList(out, G->adjacent[i]);
		fprintf(out, "\n");
	}
}

