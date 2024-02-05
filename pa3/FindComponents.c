/**
 * * * * Amisha Prasad // First and Last Name
 * * * * aprasa14 // UCSC UserID
 * * * * 2024 Winter CSE101 PA3 // Assignment Number
 * * * * FindComponent.c // FileName
 * * * * Implementation for FindComponent // Description
 * * * ***/


#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "List.h"
#include "Graph.h"

#define MAX_LEN 300

// definition of structs
typedef struct InputData { // contains input file info
    int numVertices; // data from first line of input file
    int** edgesArr; // each row will contain and edge represented in file line 2 to 00
    int edgesArrLen; // length of edges array


} InputData;


typedef struct OutputData {
    List* components;
    int componentsLength;

} OutputData;


// definition of helpers
void createInputData(char* inputFile, InputData* input);
void freeInput(InputData *input);
void populateGraph(Graph graph, InputData* input);
void populateOutputData(OutputData* output, Graph tGraph);
void printOutputFile(char* outputFile, Graph graph, OutputData* output);
void freeOutput(OutputData* output);


// start of main
int main(int argc, char * argv[]){

// step 1 check if arguments are given properly
	if( argc != 3 ){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
      		exit(1);
   	}	

// step 2 read input file and populate inputData struct

InputData* input = malloc(sizeof(InputData));
createInputData(argv[1], input);

//printf("edgesArrLen is %d\n", input->edgesArrLen);
//for(int i = 0; i < input->numVertices; i++){
	

//}

	
// step 3 create and populate non business items of graph given by inputData struct 

Graph graph = newGraph(input->numVertices);

populateGraph(graph, input); // this populates adj list

//myPrintGraph(graph, "P");

//Graph cGraph = copyGraph(graph);

// step 4 call DFS on created Graph and populates all fields including finish and stack of finish times

List sGraphList = newList();


for(int i = 1; i <= getOrder(graph); i++){

	append(sGraphList, i);

}


DFS(graph, sGraphList); // make sure sGraphList is in descending finish order at end of DFS

myPrintList(sGraphList);
printf("LAST LINE\n");

// step 5 create new graph by trasposing graph above

Graph tGraph = transpose(graph);



// step 6 run DFS on transposed graph in order of the stack from step 4

//DFS(tGraph, sGraphList);


// step 7 find strongly connected components using DFS results from step 6

OutputData* output = malloc(sizeof(OutputData));
populateOutputData(output, tGraph);


// step 8 print list and component data to output file

printOutputFile(argv[2],graph, output);

//printOutputFile(argv[2], tGraph, output);

// free section
// free InputData input
freeInput(input);
freeList(&sGraphList);
freeGraph(&tGraph);
freeGraph(&graph);
freeOutput(output);

}



// helper function section

void createInputData(char* inputFile, InputData* input){

	int line_count;
	int rowADJ;
	int rowDFS;
	FILE *in;
	char line[MAX_LEN];
	char* token;

	int found00 = 0;


	in = fopen(inputFile, "r");
		if( in==NULL ){
			printf("Unable to open file %s for reading\n", inputFile);
			exit(1);
		}

	input->numVertices = 0;
	line_count = 0;

	while( fgets(line, MAX_LEN, in) != NULL ){

		line_count++;

		if(line_count == 1){
			rowADJ = -1;

		}

		else{
	
			rowADJ++;
		}


		if(line_count == 1){
			
			token = strtok(line, " \n");
			input->numVertices = atoi(token);

			//printf("numVertices is %d\n", input->numVertices);
		}

		else{

			int firstVal = atoi(strtok(line, " \n"));
			int secondVal = atoi(strtok(NULL, " \n"));

			if(firstVal == 0 && secondVal == 0){
				if(found00 == 1){
					break;
				}

				if(found00 == 0){
					found00 = 1;
					rowDFS = 0;
				}


			}


			if(found00 == 0){

				if(input->edgesArr == NULL){
					input->edgesArr = malloc(sizeof(int*));

				}

				else{
					int** temp = realloc(input->edgesArr, (rowADJ + 1) * sizeof(int*));
					input->edgesArr = temp;
				}

				input->edgesArr[rowDFS] = malloc(2 * sizeof(int));
				input->edgesArr[rowDFS][0] = firstVal;
				input->edgesArr[rowDFS][1] = secondVal;
				input->edgesArrLen++;
				rowDFS++;



			}



		}
		



	}







}

void freeInput(InputData *input){
	// TO DO
	// TO DO
	// TO DO

}

void populateGraph(Graph graph, InputData* input){
	for(int i = 0; i< input->edgesArrLen; i++){
		addArc(graph, input->edgesArr[i][0], input->edgesArr[i][1]);
	}
	

}

 
void populateOutputData(OutputData* output, Graph tGraph){

	// TO DO
	//         // TO DO
	//                 // TO DO

}
 

void printOutputFile(char* outputFile, Graph graph, OutputData* output){

	FILE *out;
   	out = fopen(outputFile, "w");

   	if( out==NULL ){
		printf("Unable to open file %s for writing\n", outputFile);
      		exit(1);
   	}



	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, graph);


	


}
 

void freeOutput(OutputData* output){

	// TO DO 
	// TO DO
	// TO DO

}         
