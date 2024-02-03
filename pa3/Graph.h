/**
 * * * * Amisha Prasad // First and Last Name
 * * * * aprasa14 // UCSC UserID
 * * * * 2024 Winter CSE101 PA3 // Assignment Number
 * * * * Graph.h // FileName
 * * * * Header for Graph ADT // Description
 * * * * ***/


#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "List.h"

typedef struct GraphObj* Graph;

#define INF -1
#define NIL 0

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);

/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);


/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List S);

/*** Other operations ***/
void printGraph(FILE* out, Graph G);
Graph transpose(Graph G);
Graph copyGraph(Graph G);


#endif 
