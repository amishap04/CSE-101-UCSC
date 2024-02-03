/**
 * * * * Amisha Prasad // First and Last Name
 * * * * aprasa14 // UCSC UserID
 * * * * 2024 Winter CSE101 PA3 // Assignment Number
 * * * * List.h // FileName
 * * * * Header for List ADT // Description
 * * * * ***/



#ifndef QUEUE_H_INCLUDE_
#define QUEUE_H_INCLUDE_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#define FORMAT "%d"

typedef struct NodeObj* Node;
typedef struct ListObj* List;
typedef struct QueueObj* Queue; 


// Constructors-Destructors
List newList(void); 
void freeList(List* pL);
Node newNode(int data);
void freeNode(Node* pN);
Queue newQueue();
void freeQueue(Queue* pQ);


// Access functions
int length(List L);
int index(List L);
int front(List L);
int back(List L);
int get(List L);
bool equals(List A, List B);
int getQFront(Queue Q);
int getQLength(Queue Q);
bool isQEmpty(Queue Q);


// Manipulation procedures
void clear(List L);
void set(List L, int x);
void moveFront(List L); 
void moveBack(List L); 
void movePrev(List L);
void moveNext(List L);
void prepend(List L, int x); 
void append(List L, int x); 
void insertBefore(List L, int x); 
void insertAfter(List L, int x); 
void deleteFront(List L); 
void deleteBack(List L); 
void delete(List L);
void Enqueue(Queue Q, int data);
void Dequeue(Queue Q);


// Other operations
void printList(FILE* out, List L);
void myPrintList(List L);
List copyList(List L);
List concatList(List A, List B);


#endif

