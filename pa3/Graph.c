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
    return G->order;
}

int getSize(Graph G) {
    return G->size;
}

int getParent(Graph G, int u) {
    if (1 <= u && u <= getOrder(G)) {
        return G->parents[u];
    } else {
        return NIL;
    }
}

int getDiscover(Graph G, int u){
    if(1 <= u && u <= getOrder(G)){
	return G->discover[u];
    } else {
	return UNDEF;
    }

}

int getFinish(Graph G, int u){
    if(1 <= u && u <= getOrder(G)){
        return G->finish[u];
    } else {
        return UNDEF;
    }

}


void addEdge(Graph G, int u, int v) {
    if (1 <= u && u <= G->order && 1 <= v && v <= G->order) {
        
        if (length(G->neighbors[u]) == 0 || back(G->neighbors[u]) < v) {
            append(G->neighbors[u], v);
        } else {
            moveFront(G->neighbors[u]);
            while (index(G->neighbors[u]) >= 0 && get(G->neighbors[u]) < v) {
                moveNext(G->neighbors[u]);
            }
            if (index(G->neighbors[u]) >= 0) {
                insertBefore(G->neighbors[u], v);
            } else {
                append(G->neighbors[u], v);
            }
        }

        
        if (length(G->neighbors[v]) == 0 || back(G->neighbors[v]) < u) {
            append(G->neighbors[v], u);
        } else {
            moveFront(G->neighbors[v]);
            while (index(G->neighbors[v]) >= 0 && get(G->neighbors[v]) < u) {
                moveNext(G->neighbors[v]);
            }
            if (index(G->neighbors[v]) >= 0) {
                insertBefore(G->neighbors[v], u);
            } else {
                append(G->neighbors[v], u);
            }
        }

        G->size++;
    }
}

void addArc(Graph G, int u, int v) {
    if (1 <= u && u <= G->order && 1 <= v && v <= G->order) {

	if (length(G->neighbors[u]) == 0 || back(G->neighbors[u]) < v) {
             append(G->neighbors[u], v);
         } else {
             moveFront(G->neighbors[u]);
             while (index(G->neighbors[u]) >= 0 && get(G->neighbors[u]) < v) {
                 moveNext(G->neighbors[u]);
             }
             if (index(G->neighbors[u]) >= 0) {
                 insertBefore(G->neighbors[u], v);
             } else {
                 append(G->neighbors[u], v);
             }
         }



        G->size++;
    }
}

void DFS(Graph G, List S){



}



Graph transpose(Graph G){


return NULL; // REMOVE
}


Graph copyGraph(Graph G){


return NULL; // REMOVE
}


void printGraph(FILE* out, Graph G) {
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



