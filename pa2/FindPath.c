#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "List.h"
#include "Graph.h"

#define MAX_LEN 300

typedef struct inputData{

	int numConnections;
	int** connections;

}inputData;


inputData* getGraphFileData(char* inputFile);
void freeInputData(inputData* inputData);



int main(int argc, char * argv[]){

   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   inputData* inputD = getGraphFileData(argv[1]);

   
   for(int i = 0; i < inputD->numConnections; i++){
	for(int j = 0; j < 2; j++){
		printf("value at %d %d is: %d", i, j, inputD->connections[i][j]);
	}
	printf("\n");

   }


   freeInputData(inputD);
   return(0);
}





inputData* getGraphFileData(char* inputFile){
   
   inputData* inputData1 = malloc(sizeof(inputData));
   int** connections;
   

   int token_count, line_count;
   FILE *in;
   char line[MAX_LEN];
   char tokenBuffer[MAX_LEN];
   char* token;


   in = fopen(inputFile, "r");
      if( in==NULL ){
      printf("Unable to open file %s for reading\n", inputFile);
      exit(1);
   }


   line_count = 0;
   while( fgets(line, MAX_LEN, in) != NULL)  {
      line_count++;


      token_count = 0;
      tokenBuffer[0] = '\0';


      token = strtok(line, " \n");

      if(line_count == 1){

	inputData1->numConnections = atoi(token);
	connections = malloc((inputData1->numConnections) * sizeof(int*));


      }

      if(line_count > inputData1->numConnections + 1){
	  break;
      }

      int row = line_count - 2;
      int col = 0;

      while( token!=NULL ){

         strcat(tokenBuffer, "   ");
         strcat(tokenBuffer, token);
         strcat(tokenBuffer, "\n");
         token_count++;
	 token = strtok(NULL, " \n");

//	printf("token is: %s\n", token);
	printf("row  %d col %d line %d\n", row, col, line_count);

	 if(line_count >= 2){
//	 	connections[row][col] = atoi(token);
		col++;
		if(col == 2){ 
		
			col = 0;
		}
	 }

        // token = strtok(NULL, " \n");
      }

   }


inputData1->connections = connections;

fclose(in);
return inputData1;

}

void freeInputData(inputData* inputData){



}

















