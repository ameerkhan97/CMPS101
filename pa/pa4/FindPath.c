//-----------------------------------------------------------------------------
//  FindPath.c
//  Ameer Khan
//  ammukhan
//  CS101 PA4
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
   int source;
   int destination;
   List L;
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
   		addEdge(G, u, v);
   }

   printGraph(out, G);
   L = newList();

   // scans input file and prints desired output
   while (fscanf(in, "%d %d", &source, &destination)) {
   		if (source == 0 && destination == 0) {
   			break;
   		}
   		BFS(G, source);
   		getPath(L, G, destination);
   		if (getDist(G, destination) != -1) {
   			fprintf(out, "\nThe distance from %d to %d is %d \n", source, destination, getDist(G, destination));
   			fprintf(out, "A shortest %d-%d path is: ", source, destination);
   			printList(out, L);
   			fprintf(out, "\n");
   		} else {
   			fprintf(out, "\nThe distance from %d to %d is infinity \n", source, destination);
   			fprintf(out, "No %d-%d path exists\n", source, destination);
   		}
   		clear(L);
   	}

   	freeGraph(&G); // free graph
   	freeList(&L); // free list
   	fclose(in); // close input file
   	fclose(out); // close output file
}