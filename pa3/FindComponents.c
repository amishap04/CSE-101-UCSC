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

int main(int argc, char * argv[]){

	if( argc != 3 ){
		fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
      		return 1;
   	}	


	FILE *in = fopen(argv[1], "r");

    if( in==NULL ){
		printf("Unable to open file %s for reading\n", argv[1]);
        return 1;
    }

	FILE *out = fopen(argv[2], "w");

    if( out==NULL ){
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    int lngth;
    fscanf(in, "%d\n", &lngth);
    Graph G = newGraph(lngth);
    int source;
    int end;
    while (1){
        fscanf(in, "%d %d\n", &source, &end);
        if(source == 0 || end == 0){
            break;
        }
        addArc(G, source, end);

    }

    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
    fprintf(out, "\n");
    List L = newList();
    for(int i = 1; i <= lngth; i++){
        append(L, i);
    }
    DFS(G, L);
    Graph T = transpose(G);
    DFS(T, L);
    int compCount = 0;
    for(int i = 1; i <= getOrder(T); i++){
        if(getParent(T, i) == NIL){
            compCount++;
        }
    }
    List *components = calloc(compCount + 1, sizeof(List));
    for(int i = 1; i <= compCount; i++){
        components[i] = newList();
    }
    int strongComp = 1;
    int bottom = front(L);
    for(int i = 0; i < lngth - 1; i++){
        int top = back(L);
        deleteBack(L);
        prepend(components[strongComp], top);
        if(getParent(T, top) == NIL){
            strongComp++;
        }
    }
    prepend(components[strongComp], bottom);
    fprintf(out, "G contains %d strongly connected components:\n", compCount);
    for(int i = 1; i <= compCount; i++){
        fprintf(out, "Component %d: ", i);
        printList(out, components[i]);
        fprintf(out, "\n");
    }
    for(int i = 0; i <= compCount; i++){
        freeList(&components[i]);
    }

    free(components);
    freeList(&L);
    freeGraph(&G);
    freeGraph(&T);
    fclose(in);
    fclose(out);
    return 0;


}
