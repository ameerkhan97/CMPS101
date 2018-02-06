//-----------------------------------------------------------------------------
//  Lex.c
//  Ameer Khan
//  ammukhan
//  CS101 PA2
//  Takes two command line arguments giving the names of an 
//  input file and an output file.
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#define MAX_LEN 160

int main(int argc, char * argv[]){

   int i;
   int count = 0;
   FILE *in, *out;
   char line[MAX_LEN];

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

   //read each line of input file, then count and print tokens 
   while (fgets(line, MAX_LEN, in) != NULL)  {
      count++;
   }

   //reset file to start
   rewind(in);
   char number[count - 1][MAX_LEN];
   int k = 0;

   while (fgets(line, MAX_LEN, in) != NULL)  {
      strcpy(number[k++], line);
   }


   List list = newList(); //create new list
   append(list, 0); //append 0 to new list

   //insertion sort algorithm
   for (int j = 1; j < count; j++) {
   		i = (j - 1);
   		char *temp = number[j];
   		moveBack(list);
   		while (i >= 0 && strcmp(temp, number[get(list)]) <= 0) {
   			movePrev(list);
   			i--;
   		}
   		if (index(list) >= 0){
   			insertAfter(list, j);
   		} else {
   			prepend(list, j);
   		}
   	}

   	//writes and prints to output file
   	moveFront(list);
   	while (index(list) >= 0) {
   		fprintf(out, "%s", number[get(list)]);
   		moveNext(list);
   	}

   	//closes file and frees list
    fclose(in);
    fclose(out);
    freeList(&list);

    return 0;
}


