/**
 * * * * Amisha Prasad // First and Last Name
 * * * * aprasa14 // UCSC UserID
 * * * * 2024 Winter CSE101 PA4 // Assignment Number
 * * * * List.h // FileName
 * * * * Header file for List ADT // Description
 * * * ***/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>


#define FORMAT "%d"

typedef struct NodeObj* Node;
typedef struct ListObj* List;


// Constructor-Destructor
List newList(void); 
void freeList(List* pL);
Node newNode(void* data);
void freeNode(Node* pN);

// Access Functions
int length(List L);
int index(List L);
void* front(List L);
void* back(List L);
void* get(List L);

// Manipulation functions
void clear(List L);
void set(List L, void* x);
void moveFront(List L); 
void moveBack(List L); 
void movePrev(List L);
void moveNext(List L);
void prepend(List L, void* x); 
void append(List L, void* x); 
void insertBefore(List L, void* x); 
void insertAfter(List L, void* x); 
void deleteFront(List L); 
void deleteBack(List L); 
void delete(List L);

// Other functions
void printList(FILE* out, List L);
List concatList(List A, List B);




