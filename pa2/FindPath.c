#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "List.h"
#include "Graph.h"

#define MAX_LEN 300

// defining structs

typedef struct InputData{

	int numNodes;
	int numConnections;
	int** connections;

}InputData;

// defining functions

void getGraphFileData(char* inputFile, InputData* inputData);
void freeInputData(InputData* inputData);
void printOutputFile(char* outputFile, char** outputDataArray, int arraySize);
void freeOutputArray(char** outputArray, int arraySize);
char** createStringArray(int* size);
char** addString(char** array, int* size, const char* string);



// start of main

int main(int argc, char * argv[]){

   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   FILE *out;
   out = fopen(argv[2], "w");

   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }


   InputData* inputData = malloc(sizeof(InputData));

   int outputArraySize = 0;
   char** outputArray = createStringArray(&outputArraySize);

   outputArray = addString(outputArray, &outputArraySize, "123\n");
   outputArray = addString(outputArray, &outputArraySize, "456\n");



   getGraphFileData(argv[1], inputData);

   Graph G = newGraph(inputData->numNodes);

   for(int i = 0; i < inputData->numConnections; i++){
       addEdge(G, inputData->connections[i][0], inputData->connections[i][1]);

   }

   printGraph(out, G);

/*   
   for(int i = 0; i < inputData->numConnections; i++){
	for(int j = 0; j < 2; j++){
		printf("%d ", inputData->connections[i][j]);
	}
	printf("\n");

   }
*/


 //  printOutputFile(argv[2], outputArray, outputArraySize);
   

   freeInputData(inputData);
   freeOutputArray(outputArray, outputArraySize);
   


  return(0);
}



// start of helper functions

void getGraphFileData(char* inputFile, InputData* inputData){
   
   int  line_count, row;
   FILE *in;
   char line[MAX_LEN];
   char* token;


   in = fopen(inputFile, "r");
      if( in==NULL ){
      printf("Unable to open file %s for reading\n", inputFile);
      exit(1);
   }

   inputData->numConnections = 0;


   line_count = 0;



   while( fgets(line, MAX_LEN, in) != NULL)  {

      line_count++;

      if(line_count == 1){

		row = -1;

      }
      else{
	row++;

      }

      
      if(line_count == 1){
	// processing for numNodes
	
	token = strtok(line, " \n");
	inputData->numNodes = atoi(token);	 	
	
      }
      else{
	// getting connections
        
	// 15 found in line 76-82
	// 1 7
	// 0 0
	
	int firstValue = atoi(strtok(line, " \n"));
	int secondValue = atoi(strtok(NULL, " \n")); 



	if(firstValue == 0 && secondValue == 0){
		break;
	}

	else{

		if(inputData->connections == NULL){
			inputData->connections = malloc(sizeof(int*)); // creates row
			
		}

		else{
		
			int ** temp = realloc(inputData->connections, (row + 1) * sizeof(int*));
			inputData->connections = temp;

		}

		inputData->connections[row] = malloc(2 * sizeof(int)); // creates 2 col
		inputData->connections[row][0] = firstValue;
		inputData->connections[row][1] = secondValue;
		inputData->numConnections++;


	}



      }




  } 

  
  //fclose(in);


}

void freeInputData(InputData* inputData){

	for(int i = 0; i < inputData->numConnections; i++){


		free(inputData->connections[i]);

	}

	free(inputData->connections);

	free(inputData);

}


void printOutputFile(char* outputFile, char** outputDataArray, int arraySize){


   FILE *out;
   out = fopen(outputFile, "w");

   if( out==NULL ){
      printf("Unable to open file %s for writing\n", outputFile);
      exit(1);
   }	

   if(arraySize > 0){

        for(int i = 0; i < arraySize; i++){
		fprintf(out, outputDataArray[i]);
        }   
   }
   fclose(out);
}


char** createStringArray(int* size) {
    
    char** array = malloc(sizeof(char*));

    
    *size = 0;

    return array;
}


char** addString(char** array, int* size, const char* string) {
    
    char** temp = realloc(array, (*size + 1) * sizeof(char*));
    array = temp;

    
    array[*size] = malloc(strlen(string) + 1); 

    
    strcpy(array[*size], string);

    
    (*size)++;

    return array;
}


void freeOutputArray(char** outputArray, int arraySize){

	for (int i = 0; i < arraySize; i++) {
		free(outputArray[i]);
        }

	free(outputArray);

}











