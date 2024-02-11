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
#include "Matrix.h"

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
   Matrix A, B;

   while( fgets(line, MAX_LEN, in) != NULL)  {
      line_count++;
      if(line_count == 1){
        token = strtok(line, " \n");
        n = atoi(token);
        token = strtok(NULL, " \n");
        a_nn = atoi(token);
        token = strtok(NULL, " \n");
        b_nn = atoi(token);
        A = newMatrix(n);
        B = newMatrix(n);
      }
      
      else if(line_count == 2){
        continue;
      }
      else if(line_count <= (a_nn + 2)){
        token = strtok(line, " \n");
        row = atoi(token);
        token = strtok(NULL, " \n");
        col = atoi(token);
        token = strtok(NULL, " \n");
        val = atof(token);
        changeEntry(A, row, col, val);
      }
      else if(line_count == (a_nn + 3)){
        continue;
      }
      else{
        token = strtok(line, " \n");
        row = atoi(token);
        token = strtok(NULL, " \n");
        col = atoi(token);
        token = strtok(NULL, " \n");
        val = atof(token);
        changeEntry(B, row, col, val); 
      }

   }

   fprintf(out, "A has %d non-zero entries:\n", a_nn);
   printMatrix(out, A);

   fprintf(out, "\n");

   fprintf(out, "B has %d non-zero entries:\n", b_nn);
   printMatrix(out, B);


   double mult = 1.5;
   Matrix SM = scalarMult(mult, A);
   fprintf(out, "\n");
   fprintf(out, "(%.1f)*A =\n", mult);
   printMatrix(out, SM);

 
   






   Matrix TA = transpose(A);
   fprintf(out, "\n");
   fprintf(out, "Transpose(A) =\n");
   printMatrix(out, TA);
   
   Matrix PA = product(A, B);
   fprintf(out, "\n");
   fprintf(out, "A*B =\n");
   printMatrix(out, PA);

   Matrix PA2 = product(B, B);
   fprintf(out, "\n");
   fprintf(out, "B*B =\n");
   printMatrix(out, PA2);






 
   fclose(in);
   fclose(out);
   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&SM);
   freeMatrix(&TA);
   freeMatrix(&PA);
   freeMatrix(&PA2);

   return(0);



}



