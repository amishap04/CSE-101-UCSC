#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

typedef struct NodeObj* Node;
typedef struct ListObj* List;

// Constructors-Destructors
List newList(void); 
void freeList(List* pL);
Node newNode(int data);
void freeNode(Node* pN);


// Access functions
int length(List L);
int index(List L);
int front(List L);
int back(List L);
int get(List L);
bool equals(List A, List B);

// Manipulation procedures
void clear(List L);
void set(List L, int x);
void moveFront(List L); 
void moveBack(List L); 
void movePrev(List L);
void moveNext(List L);
void prepend(List L, int x); // Insert new element into L. If L is non-empty, // insertion takes place before front element.
void append(List L, int x); // Insert new element into L. If L is non-empty, // insertion takes place after back element.
void insertBefore(List L, int x); // Insert new element before cursor. // Pre: length()>0, index()>=0
void insertAfter(List L, int x); // Insert new element after cursor. // Pre: length()>0, index()>=0
void deleteFront(List L); 
void deleteBack(List L); 
void delete(List L);
//
// Other operations
void printList(FILE* out, List L);
void myPrintList(List L);
List copyList(List L);
List concatList(List A, List B);
