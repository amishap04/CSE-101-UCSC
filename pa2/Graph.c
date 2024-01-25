#include "Graph.h"

typedef enum {
    WHITE, GRAY, BLACK
} Color;

typedef struct GraphObj {
    List* neighbors;   
    Color* colors;     
    int* parents;   
    int* distances;    
    int order;       
    int size;          
    int source;       
} GraphObj;


GraphObj* newGraph(int n) {
    GraphObj* G = malloc(sizeof(GraphObj));
    G->order = n;
    G->size = 0; 
    G->source = NIL; 
    
    
    G->neighbors = malloc((n+1) * sizeof(List));
    G->colors = malloc((n+1) * sizeof(Color));
    G->parents = malloc((n+1) * sizeof(int));
    G->distances = malloc((n+1) * sizeof(int));
    
    for (int i = 1; i <= n; i++) {
        G->neighbors[i] = newList(); 
        G->colors[i] = WHITE; 
        G->parents[i] = NIL; 
        G->distances[i] = INF; 
    }
    
    return G;
}

void freeGraph(Graph* pG) {
    if(pG != NULL && *pG != NULL) {
        
        for(int i = 1; i <= (*pG)->order; i++) {
            freeList(&((*pG)->neighbors[i]));
        }
        
        free((*pG)->neighbors);
        
        
        free((*pG)->colors);
        
        
        free((*pG)->parents);
        
       
        free((*pG)->distances);
        
        
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

int getSource(Graph G) {
    return G->source;
}

int getParent(Graph G, int u) {
    if (1 <= u && u <= getOrder(G)) {
        return G->parents[u];
    } else {
        return NIL;
    }
}

int getDist(Graph G, int u) {
    if (1 <= u && u <= getOrder(G)) {
        return G->distances[u];
    } else {
        return INF;
    }
}

void getPath(List L, Graph G, int u) {
    if (getSource(G) != NIL && 1 <= u && u <= getOrder(G)) {
        if (G->distances[u] != INF) {
            if (u == getSource(G)) {
                append(L, u);
            } else {
                getPath(L, G, getParent(G, u));
                append(L, u);
            }
        } else {
            append(L, NIL);
        }
    }
}


void makeNull(Graph G) {
    for (int i = 1; i <= G->order; i++) {
        clear(G->neighbors[i]);
    }
    G->size = 0;
}

void addEdge(Graph G, int u, int v) {
    if (1 <= u && u <= G->order && 1 <= v && v <= G->order) {
        
        if (length(G->neighbors[u]) == 0 || back(G->neighbors[u]) < v) {
            append(G->neighbors[u], v);
        } else {
            moveFront(G->neighbors[u]);
            while (listIndex(G->neighbors[u]) >= 0 && get(G->neighbors[u]) < v) {
                moveNext(G->neighbors[u]);
            }
            if (listIndex(G->neighbors[u]) >= 0) {
                insertBefore(G->neighbors[u], v);
            } else {
                append(G->neighbors[u], v);
            }
        }

        
        if (length(G->neighbors[v]) == 0 || back(G->neighbors[v]) < u) {
            append(G->neighbors[v], u);
        } else {
            moveFront(G->neighbors[v]);
            while (listIndex(G->neighbors[v]) >= 0 && get(G->neighbors[v]) < u) {
                moveNext(G->neighbors[v]);
            }
            if (listIndex(G->neighbors[v]) >= 0) {
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
        
        moveFront(G->neighbors[u]);
        while (listIndex(G->neighbors[u]) >= 0 && get(G->neighbors[u]) < v) {
            moveNext(G->neighbors[u]);
        }
        if (listIndex(G->neighbors[u]) == -1) {
            append(G->neighbors[u], v);
        } else if (get(G->neighbors[u]) != v) {
            insertBefore(G->neighbors[u], v);
        }
        
        G->size++;
    }
}



void BFS(Graph G, int s) {

	G->source = s;
	
	for (int i = 1; i <= G->order; i++){
		G->colors[i] = WHITE;
		G->parents[i] = NIL;
		G->distances[i] = INF;
	}

	Queue Q = newQueue();

	Enqueue(Q, s);
	G->colors[s] = GRAY;
	G->parents[s] = NIL;
	G->distances[s] = 0;


	//printf("Dequeue Sequence is: ");

	int currentNeighbor;
	int neighborsListLength;
	int temp;

	while(isQEmpty(Q) != true){

		
		temp = getQFront(Q);
		neighborsListLength = length(G->neighbors[temp]);

		Dequeue(Q);
		//printf("%d ", temp);


		moveFront(G->neighbors[temp]);

		if(neighborsListLength > 0){
			

			for(int i = 0; i < neighborsListLength; i++){

				currentNeighbor = get(G->neighbors[temp]);

				if(G->colors[currentNeighbor] == WHITE){
					Enqueue(Q, currentNeighbor);
					G->colors[currentNeighbor] = GRAY;
					G->parents[currentNeighbor] = temp;
					G->distances[currentNeighbor] = G->distances[temp] + 1;
				
				}
				moveNext(G->neighbors[temp]);

			} // for end


		}

		G->colors[temp]= BLACK;

	}

	//printf("\n");

	for(int i = 1; i <= G->order; i++){

		//printf("Color at %d is: %d\n", i, G->colors[i]);
		//printf("Parent at %d is: %d\n", i, G->parents[i]);
		//printf("Distance at %d is: %d\n", i, G->distances[i]);
	}

	//printf("\n");
	//printf("\n");
	//printf("\n");

	freeQueue(&Q);

}



void printGraph(FILE* out, Graph G) {
    for (int i = 1; i <= G->order; i++) {
        fprintf(out, "%d: ", i);
        moveFront(G->neighbors[i]);
        while (listIndex(G->neighbors[i]) >= 0) {
            fprintf(out, "%d ", get(G->neighbors[i]));
            moveNext(G->neighbors[i]);
        }
        fprintf(out, "\n");
    }



}


void printShortestDistance(FILE* out, Graph G, int destination){


	if(getDist(G, destination) == INF){
		fprintf(out, "The distance from %d to %d is infinity\n", getSource(G), destination);

	}
	else{
		fprintf(out, "The distance from %d to %d is %d\n", getSource(G), destination, getDist(G, destination));
	}




	//fprintf(out, "\n");
	//fprintf(out, "The distance from %d to %d is %d\n", getSource(G), destination, getDist(G, destination));
	

	List parentPath;

	if(getSource(G) == destination){
                fprintf(out, "A shortest %d-%d path is: %d\n", destination, destination, destination);
        }

	else if(getParent(G, destination) == NIL){
		fprintf(out, "No %d-%d path exists\n",getSource(G), destination);

	}

	else{
	
		fprintf(out, "A shortest %d-%d path is: ", getSource(G), destination);

        	parentPath = newList();

        	getPath(parentPath, G, destination);

        	moveFront(parentPath);

        	int nextParent;

		for(int i = 0; i < length(parentPath); i++){
                	nextParent = get(parentPath);
                	fprintf(out, "%d ", nextParent);


                	moveNext(parentPath);
		}
            }


	fprintf(out, "\n");
	freeList(&parentPath);
}


























