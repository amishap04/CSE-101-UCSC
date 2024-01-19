#include "List.h"

// structs

// private Node type
typedef struct NodeObj* Node;
typedef struct ListObj* List;

// private NodeObj type
typedef struct NodeObj{
   int data;
   struct NodeObj* next;
   struct NodeObj* prev;
} Node;

// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int length;
   int index;
} List;

// Constructors-Destructors

Node newNode(int data){
    Node N = malloc(sizeof(NodeObj));
    assert( N!=NULL );
    N->data = data;
    N->next = NULL;
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
    L->front = L->back = NULL;
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

// Access functions
int length(List L) {

    if( L==NULL ){
	printf("List Error: calling length() on NULL List reference\n");
	exit(EXIT_FAILURE);
    }
    return L->length;
}

int index(List L) {

    if( L==NULL ){
        printf("List Error: calling index() on NULL List reference\n");
        return -1;
	exit(EXIT_FAILURE)
    }
    return L->index;
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
    if(L->length > 0){
	 return(L->front->data);
    }

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
    if(L->length > 0){
         return(L->back->data);
    }
}

int get(List L) {
    if( L==NULL ){
        printf("List Error: calling get() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length > 0 && L->index >= 0) {
        return L->cursor->data;
    }
}

bool equals(List A, List B) {
   if( A==NULL || B==NULL ){
	printf("List Error: calling equals() on NULL List reference\n");
        exit(EXIT_FAILURE);
   }

   if (A->length != B->length) {
        return false;
    }

    Node nodeA = A->front;
    Node nodeB = B->front;

    while (nodeA != NULL) {
        if (nodeA->data != nodeB->data) {
            return false;
        }
        nodeA = nodeA->next;
        nodeB = nodeB->next;
    }

    return true;

}

// Manipulation procedures
void clear(List L) {
    while (L->length > 0) {
        deleteFront(L);
    }
}

void set(List L, int x) {
    if (L->length > 0 && L->index >= 0) {
        L->cursor->data = x;
    }
}

void moveFront(List L) {
    if (L->length > 0) {
        L->cursor = L->front;
        L->index = 0;
    }
}

void moveBack(List L) {
    if (L->length > 0) {
        L->cursor = L->back;
        L->index = L->length - 1;
    }
}

void movePrev(List L) {
    if (L->length > 0 && L->index > 0) {
        L->cursor->prev = L->cursor;
        L->index--;
    } else if (L->length > 0 && L->index == 0) {
        L->cursor = NULL;
        L->index = -1;
    }
}

void moveNext(List L) {
    if (L->length > 0 && L->index < L->length - 1) {
        L->cursor->next = L->cursor;
        L->index++;
    } else if (L->length > 0 && L->index == L->length - 1) {
        L->cursor = NULL;
        L->index = -1;
    }
}

void prepend(List L, int x) {
    Node newNode = malloc(sizeof(NodeObj));
    newNode->data = x;
    newNode->prev = NULL;
    newNode->next = NULL;

    if (L->length == 0) {
        L->front = newNode;
        L->back = newNode;
        L->cursor = newNode;
        L->index = 0;
    } else {
        newNode->next = L->front;
        L->front->prev = newNode;
        L->front = newNode;
        L->index++;
    }

    L->length++;
}

void append(List L, int x) {
    Node newNode = malloc(sizeof(NodeObj));
    newNode->data = x;
    newNode->prev = NULL;
    newNode->next = NULL;

    if (L->length == 0) {
        L->front = newNode;
        L->back = newNode;
        L->cursor = newNode;
        L->index = 0;
    } else {
        newNode->prev = L->back;
        L->back->next = newNode;
        L->back = newNode;
    }

    L->length++;
}

void insertBefore(List L, int x) {
    if (L->length > 0 && L->index >= 0) {
        Node newNode = malloc(sizeof(NodeObj));
        newNode->data = x;
        newNode->prev = NULL;
        newNode->next = NULL;

        if (L->index == 0) {
            prepend(L, x);
        } else {
            newNode->prev = L->cursor->prev;
            newNode->next = L->cursor;
            L->cursor->prev->next = newNode;
            L->cursor->prev = newNode;
            L->length++;
        }
    }
}

void insertAfter(List L, int x) {
    if (L->length > 0 && L->index >= 0) {
        Node newNode = malloc(sizeof(NodeObj));
        newNode->data = x;
        newNode->prev = NULL;
        newNode->next = NULL;

        if (L->index == L->length - 1) {
            append(L, x);
        } else {
            newNode->prev = L->cursor;
            newNode->next = L->cursor->next;
            L->cursor->next->prev = newNode;
            L->cursor->next = newNode;
            L->length++;
        }
    }
}

void deleteFront(List L) {
    if (L->length > 0) {
        Node* temp = L->front;
        if (L->length == 1) {
            L->front = NULL;
            L->back = NULL;
            L->cursor = NULL;
            L->index = -1;
        } else {
            if (L->cursor == L->front) {
                L->cursor = NULL;
                L->index = -1;
            }
            L->front = L->front->next;
            L->front->prev = NULL;
        }
        free(temp);
        L->length--;
    }
}

void deleteBack(List L) {
    if (L->length > 0) {
        Node* temp = L->back;
        if (L->length == 1) {
            L->front = NULL;
            L->back = NULL;
            L->cursor = NULL;
            L->index = -1;
        } else {
            if (L->cursor == L->back) {
                L->cursor = NULL;
                L->index = -1;
            }
            L->back = L->back->prev;
            L->back->next = NULL;
        }
        free(temp);
        L->length--;
    }
}

void delete(List L) {


    if (L->length > 0 && L->index >= 0) {

        Node N = L->cursor;

        if (L->length == 1) {
            L->front = NULL;
            L->back = NULL;
            L->cursor = NULL;
            L->index = -1;
        } else if (L->cursor == L->front) {
            deleteFront(L);
        } else if (L->cursor == L->back) {
            deleteBack(L);
        } else {
            N->prev->next = N->next;
            N->next->prev = N->prev;
            free(L->cursor);
            L->cursor = NULL;
            L->index = -1;
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

List copyList(List L) {
    List newListCopy = *newList();
    Node current = L->front;

    while (current != NULL) {
        append(&newListCopy, current->data);
        current = current->next;
    }

    return newListCopy;
}

List concatList(List A, List B) {
    List newListConcat = *newList();

    Node currentA = A->front;
    while (currentA != NULL) {
        append(&newListConcat, currentA->data);
        currentA = currentA->next;
    }

    Node currentB = B->front;
    while (currentB != NULL) {
        append(&newListConcat, currentB->data);
        currentB = currentB->next;
    }

    return newListConcat;
}



