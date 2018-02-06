//-----------------------------------------------------------------------------
//  FindComponents.c
//  Ameer Khan
//  ammukhan
//  CS101 PA5
//  Takes two command line arguments giving the names of an input file and an output file.
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

int main(int argc, char * argv[]) {
   int u;
   int v;
   int size;
   int cc = 0;
   List S = newList();
   List scc = newList();
   FILE *in, *out;

   // check command line for correct number of arguments
   if (argc != 3) {
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");

   if (in == NULL) {
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if (out == NULL) {
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   // size
   fscanf(in, "%d", &size);
   Graph G = newGraph(size);

   // edges
   while (fscanf(in, "%d %d", &u, &v) == 2) {
   		if (u == 0 && v == 0) {
   			break;
   		}
   		addArc(G, u, v);
   }

   fprintf(out, "Adjacency list representation of G:\n");
   printGraph(out, G);

   for (int i = 1; i <= getOrder(G); i++) {
   		append(S, i);
   }

   DFS(G, S);
   Graph T = transpose(G);
   DFS(T, S);

   // connected components
   for (int i = 1; i <= getOrder(G); i++) {
   		if (getParent(T, i) == NIL) {
   			cc++;
   		}
   }

   fprintf(out, "\nG contains %d strongly connected components:\n", cc);

   for (int i = 1; i <= cc; i++) {
        fprintf(out, "Component %d:", i);
        while (getParent(T, back(S)) != NIL) {
            prepend(scc, back(S));
            deleteBack(S);
        }
        prepend(scc, back(S));
        deleteBack(S);
        printList(out, scc);
        fprintf(out, "\n");
        clear(scc);
    }
   
   freeGraph(&G); // free graph
   freeGraph(&T); // free graph
   freeList(&S); // free list
   freeList(&scc); // free list
   fclose(in); // close input file
   fclose(out); // close output file
}