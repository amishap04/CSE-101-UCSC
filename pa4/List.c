/**
 * * * * Amisha Prasad // First and Last Name
 * * * * aprasa14 // UCSC UserID
 * * * * 2024 Winter CSE101 PA4 // Assignment Number
 * * * * List.c // FileName
 * * * * Implementation for List ADT // Description
 * * * ***/


#include "List.h"


typedef struct NodeObj* Node;



typedef struct NodeObj{
   void* data;
   Node next;
   Node prev;
} NodeObj;


typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int length;
} ListObj;


Node newNode(void* data){
    Node N = malloc(sizeof(NodeObj));
    assert( N!=NULL );
    N->data = data;
    N->next = NULL;
    N->prev = NULL;
    return(N);
}

void freeNode(Node* pN) {
    if( pN!=NULL && *pN!=NULL ){
        free(*pN);
        *pN = NULL;
    }

}

List newList(void) {
    List L = malloc(sizeof(ListObj));
    assert( L!=NULL );
    L->front = NULL;
    L->back = NULL;
    L->length = 0;
    return(L);
}

void freeList(List* pL) {
    if (pL != NULL && *pL != NULL) {
        clear(*pL);
        free(*pL);
        *pL = NULL;
    }
}


int length(List L) {

    if( L==NULL ){
	printf("List Error: calling length() on NULL List reference\n");
	exit(EXIT_FAILURE);
    }
    return L->length;
}

int index(List L) {

	if (L == NULL || L->cursor == NULL) {
        	return -1;
    	}

	

	Node itr = L->front;
        int index = 0;

        while (itr != NULL) {
     	   if (itr == L->cursor) {
        	    return index;
           }
           itr = itr->next;
           index++;
        }	

      return -1;
     
}

void* front(List L) {
    if( L==NULL ){
	printf("List Error: calling front() on NULL List reference\n");
	exit(EXIT_FAILURE);
    }
    if( length(L)==0 ){
	printf("List Error: calling front() on empty List reference\n");
        exit(EXIT_FAILURE);
    }
    return(L->front->data);

}

void* back(List L) {
    if( L==NULL ){
        printf("List Error: calling back() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if( length(L)==0 ){
        printf("List Error: calling back() on empty List reference\n");
        exit(EXIT_FAILURE);
    }
    return(L->back->data);
}

void* get(List L) {
    if(L == NULL){
        printf("List Error: calling get() on empty List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->cursor == NULL){
        printf("List Error: calling get() on null cursor reference\n");
        exit(EXIT_FAILURE);
    }

    if(index(L) >= 0 && length(L) > 0){
        return L->cursor->data;
    }
    else{
	exit(EXIT_FAILURE);
    }
}


void clear(List L) {
    if(L == NULL){
        printf("List Error: calling clear() on empty List reference\n");
        exit(EXIT_FAILURE);
    }

    while (L->front != NULL) {
        deleteFront(L);
    }
}


void set(List L, void* x) {
    if(L == NULL){
        printf("List Error: calling set() on empty List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->cursor == NULL){
        printf("List Error: calling set() on null cursor reference\n");
        exit(EXIT_FAILURE);
    }

    if (length(L) > 0 && index(L) > -1) {
        L->cursor->data = x;
    }
}

void moveFront(List L) {
    if (L != NULL && length(L) > 0 && L->front != NULL) {
        L->cursor = L->front;
    }
}

void moveBack(List L) {

    if (L != NULL && length(L) > 0 && L->back != NULL) {
        L->cursor = L->back;
    }
}


void movePrev(List L) {
    if(L == NULL){
        printf("List Error: calling movePrev() on empty List reference\n");
        exit(EXIT_FAILURE);
    }

    if(L->cursor != NULL){

        if(L->cursor->prev != NULL){

                L->cursor = L->cursor->prev;
        }
        else if(L->cursor->prev == NULL){   
      
	        L->cursor = NULL;
        }

    }

    

  

}


void moveNext(List L) {

    if(L == NULL){
        printf("List Error: calling moveNext() on empty List reference\n");
        exit(EXIT_FAILURE);
    }

    if(L->cursor != NULL){
        if(L->cursor->next != NULL){
            L->cursor = L->cursor->next;
        }
        else{
            L->cursor = NULL;
        }

    }

 }

void prepend(List L, void* x) {

    if(L == NULL){
        printf("List Error: calling prepend() on empty List reference\n");
        exit(EXIT_FAILURE);
    }

    Node newNde = newNode(x);

    if(length(L) == 0){
	L->front = newNde;
	L->back = newNde;
    }

    else{
        
        L->front->prev = newNde;
        newNde->next = L->front;
        L->front = newNde;
	
    }

    L->length++;    

}


void append(List L, void* x){

    if(L == NULL){
        printf("List Error: calling append() on empty List reference\n");
        exit(EXIT_FAILURE);
    }

    Node newNde = newNode(x);
	if(length(L) == 0){
	   L->front = newNde;
	   L->back = newNde;		
	}
	else{
	   L->back->next = newNde;
	   newNde->prev = L->back;
           L->back = newNde;
	}
    L->length++;
}

void insertBefore(List L, void* x) {

    if(L == NULL){
        printf("List Error: calling insertBefore() on empty List reference\n");
        exit(EXIT_FAILURE);
    }

    if (length(L) > 0 && index(L) >= 0) {

        if (L->cursor == L->front) {
            prepend(L, x);
        } else {

	    Node newNde = newNode(x);
	    newNde->next = L->cursor;
	    newNde->prev = L->cursor->prev;
	    L->cursor->prev->next = newNde;
	    L->cursor->prev = newNde;
	    L->length++; 
        }
    }
}

void insertAfter(List L, void* x) {

    if(L == NULL){
        printf("List Error: calling insertAfter() on empty List reference\n");
        exit(EXIT_FAILURE);
    }

    if (length(L) > 0 && index(L) >= 0){
	Node newNde = newNode(x);

	if(L->cursor == L->back){
	   append(L, x);
	}
	else{
	   newNde->prev = L->cursor;
	   newNde->next = L->cursor->next;
	   L->cursor->next->prev = newNde;
	   L->cursor->next = newNde;
	   L->length++;
	}	
    }

}

void deleteFront(List L) {

    if(L == NULL){
        printf("List Error: calling deleteFront() on empty List reference\n");
        exit(EXIT_FAILURE);
    }

    if (length(L) > 0) {
	Node temp = L->front;
	L->front = L->front->next;
	freeNode(&temp);	
	L->length--;
   }

}


void deleteBack(List L) {

    if(L == NULL){
        printf("List Error: calling deleteBack() on empty List reference\n");
        exit(EXIT_FAILURE);
    }

    if (length(L) > 0) {
        Node temp = L->back;
        if (L->back->prev) {
            L->back = L->back->prev;
            L->back->next = NULL;
        } else {
            L->front = NULL;
            L->back = NULL;
        }
        if (L->cursor == temp) {
            L->cursor = NULL;
        }
        freeNode(&temp);
        L->length--;
    }
}




void delete(List L) {

    if(L == NULL){
        printf("List Error: calling delete() on empty List reference\n");
        exit(EXIT_FAILURE);
    }

    if (length(L) > 0 && index(L) >= 0) {
	if(L->cursor == L->front){
	    deleteFront(L);
	}
	else if(L->cursor == L->back){
	    deleteBack(L);
	}
	else{
	    Node* temp = &L->cursor;
            L->cursor->prev->next = L->cursor->next;
	    L->cursor->next->prev = L->cursor->prev;
	    L->cursor->next = NULL;
	    L->cursor->prev = NULL;
	    L->cursor = NULL;
	    freeNode(temp);
	    L->length--;
	}
    }
}


void printList(FILE* out, List L) {

    if(L == NULL){
        printf("List Error: calling printList() on empty List reference\n");
        exit(EXIT_FAILURE);
    }

    if (L->length > 0) {
        Node current = L->front;
        while (current != NULL) {
            fprintf(out, "%p ", current->data);
            current = current->next;
        }
    }
}


List concatList(List A, List B) {

    if(A == NULL){
        printf("List Error: calling concatList() on empty first List reference\n");
        exit(EXIT_FAILURE);
    }

    if(B == NULL){
        printf("List Error: calling concatList() on empty second List reference\n");
        exit(EXIT_FAILURE);
    }

    List newListConcat = newList();

    Node currentA = A->front;
    while (currentA != NULL) {
        append(newListConcat, currentA->data);
        currentA = currentA->next;
    }

    Node currentB = B->front;
    while (currentB != NULL) {
        append(newListConcat, currentB->data);
        currentB = currentB->next;
    }

    return newListConcat;
}





