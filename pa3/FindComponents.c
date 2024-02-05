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
void populateOutputData(OutputData* output, Graph tGraph, List L);
void printOutputFile(char* outputFile, Graph graph, OutputData* output);
void freeOutput(OutputData* output);


// start of main
int main(int argc, char * argv[]){

// step 1 check if arguments are given properly
	if( argc != 3 ){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
      		exit(1);
   	}	


	FILE *in;
	in = fopen(argv[1], "r");

        if( in==NULL ){
		printf("Unable to open file %s for reading\n", argv[1]);
                exit(1);
        }




	FILE *out;
	out = fopen(argv[2], "wb");

        if( out==NULL ){
                printf("Unable to open file %s for writing\n", argv[2]);
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

//myPrintList(sGraphList);
//printf("LAST LINE\n");

// step 5 create new graph by trasposing graph above

Graph tGraph = transpose(graph);



// step 6 run DFS on transposed graph in order of the stack from step 4

DFS(tGraph, sGraphList);


//printBusData(tGraph);
//myPrintList(sGraphList);

// step 7 find strongly connected components using DFS results from step 6

OutputData* output = malloc(sizeof(OutputData));
populateOutputData(output, tGraph, sGraphList);


// step 8 print list and component data to output file

printOutputFile(argv[2], graph, output);

//printOutputFile(argv[2], tGraph, output);


fclose(out);
fclose(in);



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




fclose(in);


}

void freeInput(InputData *input){

	for(int i = 0; i < input->edgesArrLen; i++){
		free(input->edgesArr[i]);
	}

	free(input);

}

void populateGraph(Graph graph, InputData* input){
	for(int i = 0; i< input->edgesArrLen; i++){
		addArc(graph, input->edgesArr[i][0], input->edgesArr[i][1]);
	}
	

}

 
void populateOutputData(OutputData* output, Graph tGraph, List L){


	if(getOrder(tGraph) != length(L)){
		return;
	}



	output->componentsLength = 0;
	for(int i = 1; i <= getOrder(tGraph); i++){
		if(getParent(tGraph, i) == NIL){
			output->componentsLength++;
		}
	}

	output->components = malloc(output->componentsLength * sizeof(List));
	for(int i = 0; i < output->componentsLength; i++){

		output->components[i] = newList();

	}


	// 8-> 7-> 6-> 3-> 4-> 1-> 5-> 2-> 
	// -1 -1      -1     -1

	int arrInd = output->componentsLength;
	for(moveFront(L); index(L) >= 0; moveNext(L)){

		if(getParent(tGraph, get(L)) == NIL){
			arrInd--;
                	append(output->components[arrInd], get(L));
                }
                else{
			append(output->components[arrInd], get(L));
                }
         }




}
 

void printOutputFile(char* outputFile, Graph graph, OutputData* output){

	FILE *out1;
   	out1 = fopen(outputFile, "wb");

   	if( out1==NULL ){
		printf("Unable to open file %s for writing\n", outputFile);
      		exit(1);
   	}



	fprintf(out1, "Adjacency list representation of G:\012");
	printGraph(out1, graph);
	fprintf(out1, "\n");

	fprintf(out1, "G contains %d strongly connected components:\n", output->componentsLength);
	
	for(int i = 0; i < output->componentsLength; i++){
		fprintf(out1, "Component %d: ", i+1);
		for(moveFront(output->components[i]); index(output->components[i]) >= 0; moveNext(output->components[i])){
			fprintf(out1, "%d ", get(output->components[i]));
		}
	
		fprintf(out1, "\n");	
	}

	
	fprintf(out1, "\n");
	fclose(out1);

}
 

void freeOutput(OutputData* output){

	for(int i = 0; i < output->componentsLength; i++){
		freeList(&output->components[i]);
	}
	
	free(output->components);

	free(output);

}         
