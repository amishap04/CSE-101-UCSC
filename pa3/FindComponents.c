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


// doing everything in main like prof's example fileio rather than using my helper functions because it threw errors

int main(int argc, char * argv[]){

	if( argc != 3 ){
		fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
      		return 1;
   	}	
	
	// opens input file
	FILE *in = fopen(argv[1], "r");

    	if( in==NULL ){
		printf("Unable to open file %s for reading\n", argv[1]);
       		return 1;
    	}

    	// opens output file
	FILE *out = fopen(argv[2], "w");

    	if( out==NULL ){
        	printf("Unable to open file %s for writing\n", argv[2]);
        	exit(1);
    	}

    	// gets total number of nodes
	int numNodes;
    	fscanf(in, "%d\n", &numNodes);

	// creates new Graph
	Graph graph = newGraph(numNodes);
    	int src;
    	int dest;
    	while (1){
        	fscanf(in, "%d %d\n", &src, &dest);
        	if(src == 0 || dest == 0){
            		break;
        	}
        	addArc(graph, src, dest);

    	}

    	fprintf(out, "Adjacency list representation of G:\n");
    	printGraph(out, graph);
    	fprintf(out, "\n");

    	List sGraphList = newList();
    	for(int i = 1; i <= numNodes; i++){
        	append(sGraphList, i);
    	}

    	// call DFS on original graph
	DFS(graph, sGraphList);
    	// transpose graph
	Graph tGraph = transpose(graph);
    	// call DFS on transpose graph
	DFS(tGraph, sGraphList);

    	// total strongly connected component
	int sccCount = 0;
    	for(int i = 1; i <= getOrder(tGraph); i++){
        	if(getParent(tGraph, i) == NIL){
            	sccCount++;
        	}
    	}

    	List *compL = calloc(sccCount + 1, sizeof(List));
    	for(int i = 1; i <= sccCount; i++){
        	compL[i] = newList();
    	}

    	int scc = 1;
    	int botS = front(sGraphList);
    	for(int i = 0; i < numNodes - 1; i++){
        	int topS = back(sGraphList);
        	deleteBack(sGraphList);
        	prepend(compL[scc], topS);
        	if(getParent(tGraph, topS) == NIL){
            		scc++;
        	}
    	}
    	prepend(compL[scc], botS);
    	// prints total number of SCC and the list containing that SCC
	fprintf(out, "G contains %d strongly connected components:\n", sccCount);
    	for(int i = 1; i <= sccCount; i++){
        	fprintf(out, "Component %d: ", i);
        	printList(out, compL[i]);
        	fprintf(out, "\n");
    	}

    	// frees everything and closes files
	for(int i = 0; i <= sccCount; i++){
        	freeList(&compL[i]);
    	}

    	free(compL);
    	freeList(&sGraphList);
    	freeGraph(&graph);
    	freeGraph(&tGraph);
    	fclose(in);
    	fclose(out);
    	return 0;


}


// helper function section which I am no longer using
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








