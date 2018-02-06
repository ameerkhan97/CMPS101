//-----------------------------------------------------------------------------
//  Graph.c
//  Ameer Khan
//  ammukhan
//  CS101 PA5
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
	int *discover;
	int *finish;
	int order;
	int size;
} GraphObj;

// Constructors-Destructors ---------------------------------------------------

// newGraph()
// returns a Graph pointing to a newly created GraphObj representing a graph having n vertices and no edges
Graph newGraph(int n) {
	Graph G = malloc(sizeof(GraphObj));
	G->adjacent = calloc(sizeof(List),(n+1));
	G->color = calloc(sizeof(char),(n+1));
	G->parent = calloc(sizeof(int),(n+1));
	G->discover = calloc(sizeof(int),(n+1));
	G->finish = calloc(sizeof(int),(n+1));
	G->order = n;
	G->size = 0;

	for (int i = 0; i <= n; i++) {
		G->adjacent[i] = newList();
		G->color[i] = 'w';
		G->parent[i] = NIL;
		G->discover[i] = UNDEF;
		G->finish[i] = UNDEF;
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
	free((*pG)->discover);
	free((*pG)->finish);
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

// getDiscover()
// returns the discovery time of vertex u, 
// precondition 1 <= u <= getOrder(G)
int getDiscover(Graph G, int u) {
	if (G == NULL) {
		printf("getDiscover() Error: calling getDiscover() on NULL graph\n");
		exit(1);
	}
	if (u > getOrder(G) || u < 1) {
		printf("getDiscover() Error: calling getDiscover() on vertex u that is out of bounds\n");
		exit(1);
	}
	return G->discover[u];
}

// getFinish()
// returns the finish time of vertex u, 
// precondition 1 <= u <= getOrder(G)
int getFinish(Graph G, int u) {
	if (G == NULL) {
		printf("getFinish() Error: calling getFinish() on NULL graph\n");
		exit(1);
	}
	if (u > getOrder(G) || u < 1) {
		printf("getFinish() Error: calling getFinish() on vertex u that is out of bounds\n");
		exit(1);
	}
	return G->finish[u];
}

// Manipulation procedures ----------------------------------------------------

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

// Visit()
// private helper function
void Visit(Graph G, List S, int u, int *time) {
	G->color[u] = 'g';
	G->discover[u] = ++(*time);
	moveFront(G->adjacent[u]);

	while (index(G->adjacent[u]) >= 0) {
		int v = get(G->adjacent[u]);
		if (G->color[v] == 'w') {
			G->parent[v] = u;
			Visit(G, S, v, time);
		}
		moveNext(G->adjacent[u]);
	}

	G->color[u] = 'b';
	G->finish[u] = ++(*time);
	prepend(S, u);
}

// DFS()
// runs the DFS algorithm on the Graph G with List S
// Pre: length(S)==getOrder(G)
void DFS(Graph G, List S) {
	if (length(S) != getOrder(G)) {
		printf("DFS() Error: calling DFS() on NULL graph\n");
		exit(1);
	}

	for (int i = 0; i <= getOrder(G); i++) {
		G->color[i] = 'w';
		G->parent[i] = NIL;
		G->discover[i] = UNDEF;
		G->finish[i] = UNDEF;
	}

	int time = 0;
	moveFront(S);

	while (index(S) >= 0) {
		if (G->color[get(S)] == 'w') {
			Visit(G, S, get(S), &time);
		}
		moveNext(S);
	}

	int size = (length(S)/2);

	while (size > 0) {
		deleteBack(S);
		size--;
	}
}

// Other methods ---------------------------------------------------------

// transpose()
// returns  a reference to  a  new  graph  object  representing  the  transpose  of G
Graph transpose (Graph G) {
	if (G == NULL) {
		printf("transpose() Error: calling transpose() on NULL graph\n");
		exit(1);
	}

	Graph temp = newGraph(getOrder(G));

	for (int i = 1; i<= getOrder(G); i++) {
		moveFront(G->adjacent[i]);
		while (index(G->adjacent[i]) >= 0) {
			addArc(temp, get(G->adjacent[i]), i);
			moveNext(G->adjacent[i]);
		}
	}
	return temp;
}

// copyGraph()
// returns a reference to a new graph which is a copy of G
Graph copyGraph (Graph G) {
	if (G == NULL) {
		printf("copyGraph() Error: calling copyGraph() on NULL graph\n");
		exit(1);
	}

	Graph temp = newGraph(getOrder(G));

	for (int i = 1; i<= getOrder(G); i++) {
		moveFront(G->adjacent[i]);
		while (index(G->adjacent[i]) >= 0) {
			addArc(temp, i, get(G->adjacent[i]));
			moveNext(G->adjacent[i]);
		}
	}
	return temp;
}

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
