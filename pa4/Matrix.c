/**
 * * * * Amisha Prasad // First and Last Name
 * * * * aprasa14 // UCSC UserID
 * * * * 2024 Winter CSE101 PA4 // Assignment Number
 * * * * Matrix.c // FileName
 * * * * Implementation of Matrix ADT // Description
 * * * ***/



#include "List.h"
#include "Matrix.h"

typedef struct EntryObj{
    int col;
    double val;

} EntryObj;

typedef struct MatrixObj{
    int size;
    List* rows;
    
} MatrixObj;



MatrixObj* newMatrix(int n){

    if(n < 1){
        printf("Matrix Error: calling newMatrix() on no rows reference\n");
	    exit(EXIT_FAILURE);
    }

    MatrixObj* mat = malloc(sizeof(MatrixObj));
    mat->size = n;
    mat->rows = malloc(n * sizeof(List));

    for(int i = 0; i < n; i++){
        mat->rows[i] = newList();
    }

    return mat;
}

EntryObj* newEntry(int col, double val, int mSize){

    if(1 <= col  && col <= mSize){
        EntryObj* entry = malloc(sizeof(EntryObj));
        entry->col = col;
        entry->val = val;
        return entry;
    }

    else{
        printf("Matrix Error: calling newEntry() on no col reference\n");
	    exit(EXIT_FAILURE);
    }
}

void freeEntry(EntryObj* pE){
    if( pE!=NULL){
        free(pE);
    }

}


void freeMatrix(Matrix* pM){
    if(pM != NULL && *pM != NULL){
        Matrix temp = *pM;

        for(int i = 0; i < temp->size; i++){
            if(temp->rows[i] != NULL){
                freeList(&(temp->rows[i]));
                temp->rows[i] = NULL;
            }
        }

        free(temp->rows);
        free(temp);
        *pM = NULL;
    }
}


void changeEntry(Matrix M, int i, int j, double x){

  if(M != NULL && 1 <= i && i <= M->size && 1 <= j && j <= M->size){
        List row = M->rows[i-1]; 

        if(row == NULL){
            return;
        }

        EntryObj* newE = newEntry(j, x, M->size); 
        bool found = false;
        for(moveFront(row); index(row) >= 0; moveNext(row)){
            EntryObj* entry = (EntryObj*)get(row);
            if(j < entry->col){
                insertBefore(row, newE);
                found = true;
                break; 
            }
            else if(j == entry->col){
                entry->val = x; 
                free(newE); 
                found = true;
                break; 
            }
        }

        if(!found){
            append(row, newE); 
        }


  }
}


int size(Matrix M){
    if(M == NULL){
        printf("Matrix Error: calling size() on NULL matrix reference\n");
        exit(EXIT_FAILURE);
    }

    return M->size;
}


void printMatrix(FILE* out, Matrix M) {

    if(M == NULL) {
        printf("Matrix Error: calling printMatrix() on NULL matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if(out == NULL) {
        printf("Matrix Error: calling printMatrix() on NULL file reference\n");
        exit(EXIT_FAILURE);
    }

    if(size(M) > 0) {
        for(int row = 0; row < size(M); row++) {

            if(length(M->rows[row]) > 0) {
                fprintf(out, "%d:", row+1);
                EntryObj* curEnt;
                for(moveFront(M->rows[row]); index(M->rows[row]) >= 0; moveNext(M->rows[row])) {
                    curEnt = get(M->rows[row]);
                    fprintf(out, " (%d, %.1f)", curEnt->col, curEnt->val);
                }
                fprintf(out, "\n");
            }
        }
    } else {
        printf("Matrix has no entries");
    }
}


EntryObj* getColEnt(List L, int col, int size){

    if(L == NULL){
        printf("List Error: calling getColEnt() on NULL List reference\n");
            exit(EXIT_FAILURE);
    }

    if(col < 1 || col > size){
        printf("Matrix Error: calling getColEnt() on NULL Matrix reference\n");
            exit(EXIT_FAILURE);
    }

    if(length(L) == 0){
        return NULL;
    }


    EntryObj* curEnt;
    for(moveFront(L); index(L) >= 0; moveNext(L)){
        curEnt = get(L);
        if(curEnt->col == col){
            return curEnt;
        }
    }

    return NULL;


}

Matrix scalarMult(double x, Matrix A){

    if(A == NULL){
        printf("Matrix Error: calling scalarMult() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    if(size(A) < 1){
        printf("Matrix Error: calling scalarMult() on Empty Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    Matrix result = newMatrix(size(A));
    List currRow;

    for(int i = 0; i < size(A); i++){
        currRow = A->rows[i];
        if(length(currRow) == 0){
            continue;
        }
        EntryObj* entryA;
        EntryObj* entry;
        for(moveFront(currRow); index(currRow) >= 0; moveNext(currRow)){
            entryA = get(currRow);
            entry = newEntry(entryA->col, (entryA->val * x), size(A));
            append(result->rows[i], entry);
        }
    } 

    return result;
}



Matrix transpose(Matrix A){

    if(A == NULL){
        printf("Matrix Error: calling transpose() on NULL Matrix reference\n");
	    exit(EXIT_FAILURE);
    }
    if(size(A) == 0){
        printf("Matrix Error: calling transpose() on empty Matrix reference\n");
	    exit(EXIT_FAILURE);
    }

    Matrix result = newMatrix(size(A));
    
    for(int i = 0; i < size(A); i ++){
        List row = A->rows[i];

        if(length(row) == 0){
            continue;
        }
        else{
            for(moveFront(row); index(row) >= 0; moveNext(row)){
                    changeEntry(result, ((EntryObj*)get(row))->col, i+1, ((EntryObj*)get(row))->val);
            }
        }
    }

    return result;

}

Matrix copy(Matrix A){

    if(A == NULL){
        printf("Matrix Error: calling transpose() on NULL Matrix reference\n");
            exit(EXIT_FAILURE);
    }
    if(size(A) == 0){
        printf("Matrix Error: calling transpose() on empty Matrix reference\n");
            exit(EXIT_FAILURE);
    }

    Matrix result = newMatrix(size(A));

    for(int i = 0; i < size(A); i ++){
        List row = A->rows[i];

        if(length(row) == 0){
            continue;
        }
        else{
            for(moveFront(row); index(row) >= 0; moveNext(row)){
                    changeEntry(result, i+1, ((EntryObj*)get(row))->col, ((EntryObj*)get(row))->val);
            }
        }
    }

    return result;
}





