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
} GraphObj;



