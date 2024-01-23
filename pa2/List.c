#include "List.h"




typedef struct NodeObj* Node;



typedef struct NodeObj{
   int data;
   Node next;
   Node prev;
} NodeObj;


typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int length;
} ListObj;



Node newNode(int data){
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

int listIndex(List L) {

    if( L==NULL){

	return -1;
    }

    else{

	if(L->cursor == NULL){
            
             return -1;

        }




	Node itr = L->front;
        int index = 0;

	
	

        while(itr->data != L->cursor->data && itr != NULL){
	    itr = itr->next;
	    index++;
        }  

	if(itr == NULL){

		return -1;
	}

      return index;
    } 
}

int front(List L) {
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

int back(List L) {
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

int get(List L) {

    if(listIndex(L) >= 0 && length(L) > 0){
        return L->cursor->data;
    }
    else{
	return -1000;
    }
}

bool equals(List A, List B) {
   if( A==NULL || B==NULL ){
	printf("List Error: calling equals() on NULL List reference\n");
        exit(EXIT_FAILURE);
   }
   bool equal;

   equal = (A->length == B->length);

   if(equal == false){
	return equal;
   }

   A->cursor = A->front;
   B->cursor = B->front;

   while(A->cursor != NULL){
	if(A->cursor->data != B->cursor->data){
		return false;
	}

	A->cursor = A->cursor->next;
	B->cursor = B->cursor->next;
   }
   return equal;

}


void clear(List L) {
	L->cursor = L->front;
	Node temp;

	while(L->cursor != NULL){
	     temp = L->cursor;
	     L->cursor = L->cursor->next;
	     free(temp);
	     L->length--;
	}
	L->front = NULL;
	L->back = NULL;
}

void set(List L, int x) {
    if (length(L) > 0 && listIndex(L) > -1) {
        L->cursor->data = x;
    }
}

void moveFront(List L) {
    if (length(L) > 0 && L->front != NULL) {
        L->cursor = L->front;
    }
}

void moveBack(List L) {
    if (length(L) > 0 && L->back != NULL) {
        L->cursor = L->back;
    }
}


void movePrev(List L) {

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

    if(L->cursor != NULL){
	if(L->cursor->next != NULL){
		L->cursor = L->cursor->next;
	}
	else{
		L->cursor = NULL;
	}

    }
    else{
	 
   }

 }

void prepend(List L, int x) {
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


void append(List L, int x){
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

void insertBefore(List L, int x) {
    if (length(L) > 0 && listIndex(L) >= 0) {
        Node newNde = newNode(x);

        if (L->cursor == L->front) {
            prepend(L, x);
        } else {
	    newNde->next = L->cursor;
	    newNde->prev = L->cursor->prev;
	    L->cursor->prev->next = newNde;
	    L->cursor->prev = newNde;
	    L->length++; 
        }
    }
}

void insertAfter(List L, int x) {
    if (length(L) > 0 && listIndex(L) >= 0){
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
    if (length(L) > 0) {
	Node* temp = &L->front;
	L->front = L->front->next;
	freeNode(temp);	
	L->length--;
   }

}

void deleteBack(List L) {
    if (length(L) > 0) {
        Node* temp = &L->back;
	L->back = L->back->prev;
	freeNode(temp);
	L->length--;
    }
}

void delete(List L) {
    if (length(L) > 0 && listIndex(L) >= 0) {
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
    if (L->length > 0) {
        Node current = L->front;
        while (current != NULL) {
            fprintf(out, "%d ", current->data);
            current = current->next;
        }
    }
}

void myPrintList(List L) {
    if (L->length > 0) {
	printf("length of list is: %d ", length(L));
	printf("front value is: %d ", front(L));
	printf("back value is: %d ", back(L));
	printf("\n");
	L->cursor = L->front;

	for(int i = 1; i<=L->length; i++){
		printf("%d-> ", L->cursor->data);
	
		L->cursor = L->cursor->next;
	}

	printf("\n");
    }
    else{
	printf("List is Empty.\n");
    }
}


List copyList(List L) {
    List newListCopy = newList();

    if(length(L) > 0){
    
	    L->cursor = L->front;

    	while (L->cursor != NULL) {
        	append(newListCopy, L->cursor->data);
        	L->cursor = L->cursor->next;
    	}
    }
    return newListCopy;
}

List concatList(List A, List B) {
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

