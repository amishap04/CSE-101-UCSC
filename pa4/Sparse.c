/**
 * * * * Amisha Prasad // First and Last Name
 * * * * aprasa14 // UCSC UserID
 * * * * 2024 Winter CSE101 PA4 // Assignment Number
 * * * * Sparse.c // FileName
 * * * * Implementation of Sparse Matrix // Description
 * * * ***/

#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "List.h"

#define MAX_LEN 300


int main(int argc, char * argv[]){


   int line_count;
   FILE *in, *out;
   char line[MAX_LEN];
   char* token;

	if( argc != 3 ){
		fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
      		return 1;
   	}	

	in = fopen(argv[1], "r");

    if( in==NULL ){
		printf("Unable to open file %s for reading\n", argv[1]);
        return 1;
    }

	out = fopen(argv[2], "w");

    if( out==NULL ){
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    
   line_count = 0;
   int n;
   int a_nn;
   int b_nn;
   int row, col;
   double val;
   while( fgets(line, MAX_LEN, in) != NULL)  {
      line_count++;
      if(line_count == 1){
        token = strtok(line, " \n");
        n = atoi(token);
        token = strtok(NULL, " \n");
        a_nn = atoi(token);
        token = strtok(NULL, " \n");
        b_nn = atoi(token);
        printf("%d %d %d\n", n, a_nn, b_nn);
      }
      
      else if(line_count == 2){
        printf("first continues\n");
        continue;
      }
      else if(line_count <= (a_nn + 2)){
        token = strtok(line, " \n");
        row = atoi(token);
        token = strtok(NULL, " \n");
        col = atoi(token);
        token = strtok(NULL, " \n");
        val = atof(token);
        printf("matrix a: %d %d %.1f\n", row, col, val); 
      }
      else if(line_count == (a_nn + 3)){
        printf("second continues\n");
        continue;
      }
      else{
        token = strtok(line, " \n");
        row = atoi(token);
        token = strtok(NULL, " \n");
        col = atoi(token);
        token = strtok(NULL, " \n");
        val = atof(token);
        printf("matrix b: %d %d %.1f\n", row, col, val); 
      }

   }

  
   fclose(in);
   fclose(out);

   return(0);



}



