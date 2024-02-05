/**
 * * * * Amisha Prasad // First and Last Name
 * * * * aprasa14 // UCSC UserID
 * * * * 2024 Winter CSE101 PA3 // Assignment Number
 * * * * Graph.c // FileName
 * * * * Implementation for Graph ADT // Description
 * * * * ***/


#include "Graph.h"

typedef enum {
    WHITE, GRAY, BLACK
} Color;

typedef struct GraphObj {        
    int order;       
    int size; 
    List* neighbors;   
    Color* colors; 
    int* parents; 
    int* discover;          
    int* finish;   

} GraphObj;

GraphObj* newGraph(int n){

    GraphObj* G = malloc(sizeof(GraphObj));
    G->order = n;
    G->size = 0;
    
    G->neighbors = malloc((n+1) * sizeof(List));
    G->colors = malloc((n+1) * sizeof(Color));
    G->parents = malloc((n+1) * sizeof(int));
    G->discover = malloc((n+1) * sizeof(int));
    G->finish = malloc((n+1) * sizeof(int));


    for(int i = 1; i <= n; i++){
	G->neighbors[i] = newList(); 
        G->colors[i] = WHITE; 
        G->parents[i] = NIL; 
        G->discover[i] = UNDEF;
	G->finish[i] = UNDEF;

    }

    return G;

}

void freeGraph(Graph* pG){
    
    if(pG != NULL && *pG != NULL) {
        
        for(int i = 1; i <= (*pG)->order; i++) {
            freeList(&((*pG)->neighbors[i]));
        }
        
        free((*pG)->neighbors);
        
        
        free((*pG)->colors);
        
        
        free((*pG)->parents);

	free((*pG)->discover);

	free((*pG)->finish);

	free(*pG);
	*pG = NULL;
     }


}



int getOrder(Graph G) {
    if (G == NULL || G->order < 0) {
        fprintf(stderr, "Graph Error: calling getOrder() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    return G->order;
}

int getSize(Graph G) {
    if (G == NULL || getOrder(G) < 0) {
        fprintf(stderr, "Graph Error: calling getSize() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->size;
}

int getParent(Graph G, int u) {
    if(G == NULL) {
        fprintf(stderr, "Graph Error: calling getParent() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    if (1 <= u && u <= getOrder(G)) {
        return G->parents[u];
    } else {
        fprintf(stderr, "Graph Error: getParent() called with vertex %d out of bounds\n", u);
        exit(EXIT_FAILURE);
    }
}

int getDiscover(Graph G, int u){
    if(G == NULL) {
        fprintf(stderr, "Graph Error: calling getDiscover() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if(1 <= u && u <= getOrder(G)){
        return G->discover[u];
    } else {
        fprintf(stderr, "Graph Error: getDiscover() called with vertex %d out of bounds\n", u);
        exit(EXIT_FAILURE);
    }
}


int getFinish(Graph G, int u){
    if(G == NULL) {
        fprintf(stderr, "Graph Error: calling getFinish() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if(1 <= u && u <= getOrder(G)){
        return G->finish[u];
    } else {
        fprintf(stderr, "Graph Error: getFinish() called with vertex %d out of bounds\n", u);
        exit(EXIT_FAILURE);
    }
}


void addEdge(Graph G, int u, int v) {
    if(G == NULL){
	fprintf(stderr, "Graph Error: calling addEdge() on NULL Graph reference\n");
        exit(EXIT_FAILURE);	

    }

    if (1 <= u && u <= G->order && 1 <= v && v <= G->order) {
        
        if (length(G->neighbors[u]) == 0 || back(G->neighbors[u]) < v) {
            append(G->neighbors[u], v);


	    if(getSize(G) < 0){
                G->size = 1;
             }
             else{
                G->size++;
             }
	


        } else {
            moveFront(G->neighbors[u]);
            while (index(G->neighbors[u]) >= 0 && get(G->neighbors[u]) < v) {
                moveNext(G->neighbors[u]);
            }
            if (index(G->neighbors[u]) >= 0) {
                insertBefore(G->neighbors[u], v);
            } else {
                append(G->neighbors[u], v);

		if(getSize(G) < 0){
                	G->size = 1;
                }
                else{
                	G->size++;
                }



            }
        }

        
        if (length(G->neighbors[v]) == 0 || back(G->neighbors[v]) < u) {
            append(G->neighbors[v], u);


	    if(getSize(G) < 0){
                G->size = 1;
             }
             else{
                G->size++;
             }


        } else {
            moveFront(G->neighbors[v]);
            while (index(G->neighbors[v]) >= 0 && get(G->neighbors[v]) < u) {
                moveNext(G->neighbors[v]);
            }
            if (index(G->neighbors[v]) >= 0) {
                insertBefore(G->neighbors[v], u);
            } else {
                append(G->neighbors[v], u);



		if(getSize(G) < 0){
                	G->size = 1;
                }
                else{
                	G->size++;
                }

            }
        }

    }
}

void addArc(Graph G, int u, int v) {
    if(G == NULL){
        fprintf(stderr, "Graph Error: calling addArc() on NULL Graph reference\n");
        exit(EXIT_FAILURE);

    }

    if (1 <= u && u <= G->order && 1 <= v && v <= G->order) {

	
	List srcL = G->neighbors[u];
	for(moveFront(srcL); index(srcL) >= 0; moveNext(srcL)){
		if(get(srcL) == v){
			return;
		}

	}


	if (length(G->neighbors[u]) == 0 || back(G->neighbors[u]) < v) {
             append(G->neighbors[u], v);
		
	     if(getSize(G) < 0){
                G->size = 1;
             }
             else{
                G->size++;
             }
	     
         } else {
             moveFront(G->neighbors[u]);
             while (index(G->neighbors[u]) >= 0 && get(G->neighbors[u]) < v) {
                 moveNext(G->neighbors[u]);
             }
             if (index(G->neighbors[u]) >= 0) {
                 insertBefore(G->neighbors[u], v);
             } else {
                 append(G->neighbors[u], v);


		if(getSize(G) < 0){
                	G->size = 1;
                }
        	else{
                	G->size++;
        	}

             }
         }




    }
}


void DFS(Graph G, List S) {
    if(G == NULL || S == NULL || length(S) <= 0){
        fprintf(stderr, "Graph Error: calling addEdge() on NULL Graph reference\n");
        exit(EXIT_FAILURE);

    }


    for (int i = 1; i <= getOrder(G); i++) {
        G->colors[i] = WHITE;
        G->parents[i] = NIL;
    }

    int time = 0;
    List tempS = newList();
    for (moveFront(S); index(S) >= 0; moveNext(S)) {
        int u = get(S);
        if (G->colors[u] == WHITE) {
            time = visit(G, tempS, u, time + 1);
        }
    }

    clear(S);
    for (moveFront(tempS); index(tempS) >= 0; moveNext(tempS)) {
        append(S, get(tempS));
    }
    freeList(&tempS);
}

int visit(Graph G, List S, int u, int time) {
    G->colors[u] = GRAY;
    G->discover[u] = time;
    List adjList = G->neighbors[u];
    if (length(adjList) > 0) {
        moveFront(adjList);
        while (index(adjList) >= 0) {
            int v = get(adjList);
            if (G->colors[v] == WHITE) {
                G->parents[v] = u;
                time = visit(G, S, v, time + 1);
            }
            moveNext(adjList);
        }
    }
    G->colors[u] = BLACK;
    G->finish[u] = ++time;
    prepend(S, u);
    return time;
}










/**

void DFS(Graph G, List S){

	int sLenIni = length(S); 
	if(sLenIni != getOrder(G)){
		return;
	}

	for (int i = 1; i <= getOrder(G); i++) {
        	G->colors[i] = WHITE;
        	G->parents[i] = NIL;
        }


// step 1: run DFS over each node in the list S if color is white by calling visit(currNode)
// step 1 discovers and finishes all connected nodes of the currNode
	
	int vertex, time = 0;
	List tempS = newList();
	
	for(moveFront(S); index(S) >= 0; moveNext(S)){

		vertex = get(S);

		if(G->colors[vertex] == WHITE){
			time = visit(G, tempS, vertex, time++);
		}
		

	}


// step 2: continue DFS until all nodes are not white in order of list
// step 3: transform S to contain nodes in descending order of finish times


	for(int i = 0; i < sLenIni; i++){
		deleteFront(S);
	}

	clear(S);
	for (moveFront(tempS); index(tempS) >= 0; moveNext(tempS)) {
        	append(S, get(tempS));
    	}

    	freeList(&tempS);


	List copyS = copyList(S);
	
	while(length(S) > 0){
		deleteFront(S);
	}





	for(moveFront(copyS); index(copyS) >= 0; moveNext(copyS)){
		prepend(S, get(copyS));
	}

	freeList(&copyS);

}


int visit(Graph G, List S, int vertex, int time){



	G->colors[vertex] = GRAY;
	G->discover[vertex] = time;
	List conns = G->neighbors[vertex];

	if(length(conns) == 0){
		G->finish[vertex] = time++;
		G->colors[vertex] = BLACK;
		append(S, vertex);
	}

else{

	for(moveFront(conns); index(conns) >= 0; moveNext(conns)) {
		int child = get(conns);
		if(G->colors[child] == WHITE){
			G->parents[child] = vertex;
			time = visit(G, S, child, time++);
		}
	}

	G->finish[vertex] = time++;
	G->colors[vertex] = BLACK;
	prepend(S, vertex);

}


	return time++;

}


**/












Graph transpose(Graph G){

   if(G == NULL){
        fprintf(stderr, "Graph Error: calling transpose() on NULL Graph reference\n");
        exit(EXIT_FAILURE);

    }


   GraphObj* tGraph = newGraph(getOrder(G));
   
   //tGraph->size = getSize(G);

   int src, dest;

   for(int i = 1; i <= getOrder(G); i++ ){

	dest = i;
	List currNeighbors = G->neighbors[i];
	
	for(moveFront(currNeighbors); index(currNeighbors) >= 0; moveNext(currNeighbors)){
	

		if(length(currNeighbors) == 0){
			break;
		}
	
		//printf("index is: %d\n", index(currNeighbors));
		src = get(currNeighbors);
		//printf("src is: %d\n", src);
		addArc(tGraph, src, dest);
		//printf("src is: %d\n", src);
	}

    //printf("dest is: %d\n", dest);

   }      

   return tGraph;
}


Graph copyGraph(Graph G){

     if(G == NULL){
        fprintf(stderr, "Graph Error: calling copyGraph() on NULL Graph reference\n");
        exit(EXIT_FAILURE);

     }


     GraphObj* copy = newGraph(getOrder(G));

     copy->size = getSize(G);


     // copying parents
     int src, dest;


     for(int i = 1; i <= getOrder(G); i++){


	  src = i;
	  copy->parents[i] = getParent(G, i);
	  copy->discover[i] = getDiscover(G, i);
	  copy->finish[i] = getFinish(G, i);
	  
          List currL = G->neighbors[i];	  
	  if(currL != NULL && length(currL) == 0){
	      continue;
	  }
          else{
		for(moveFront(currL); index(currL) >= 0; moveNext(currL)){
			dest = get(currL);
		        addArc(copy, src, dest);
		}
	  }

     }

   return copy;

}


void printGraph(FILE* out, Graph G) {

   if(G == NULL || out == NULL){
        fprintf(stderr, "Graph Error: calling printGraph() on NULL Graph reference\n");
        exit(EXIT_FAILURE);

    }

    for (int i = 1; i <= G->order; i++) {
        fprintf(out, "%d: ", i);
        moveFront(G->neighbors[i]);
        while (index(G->neighbors[i]) >= 0) {
            fprintf(out, "%d ", get(G->neighbors[i]));
            moveNext(G->neighbors[i]);
        }
        fprintf(out, "\n");
    }

}


void myPrintGraph(Graph G, char* valueType){

	if(G == NULL){
        	fprintf(stderr, "Graph Error: calling myPrintGraph() on NULL Graph reference\n");
        	exit(EXIT_FAILURE);

        }



	for(int i = 1; i <= getOrder(G); i++){
		if(strcmp(valueType, "P") == 0){
			printf("%d: %d\n",i, getParent(G, i));
		}
		else if(strcmp(valueType, "D") == 0){
			printf("%d: %d\n", i, getDiscover(G, i));
		}
		else if(strcmp(valueType, "F") == 0){
			printf("%d: %d\n", i, getFinish(G, i));
		}
		else if(strcmp(valueType, "C") == 0){
			printf("%d: %d\n", i, G->colors[i]);
		}

	}	


}


void printBusData(Graph G){

	if(G == NULL){
        	fprintf(stderr, "Graph Error: calling printBusData() on NULL Graph reference\n");
        	exit(EXIT_FAILURE);

        }



	printf("Printing Discover:\n");
	myPrintGraph(G, "D");

	printf("Printing Parent:\n");
        myPrintGraph(G, "P");

	printf("Printing Finish:\n");
        myPrintGraph(G, "F");

	printf("Printing Color:\n");
        myPrintGraph(G, "C");


}


