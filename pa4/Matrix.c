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

EntryObj* newEntry(int col, int val, int mSize){

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

        for(int i = 0; i < (*pM)->size; i++){
            freeList(&((*pM)->rows[i]));
        }

        free((*pM)->rows);
        free(pM);
        *pM = NULL;

    }

}

void changeEntry(Matrix M, int i, int j, double x){

    if(M != NULL && 1 <= i && i <= M->size && 1 <= j && j <= M->size){
        List row = M->rows[i-1];


        if(row == NULL){
            return;
        }

        Entry newE = newEntry(j, x, M->size);
        if(length(row) == 0){
            append(row, newE);
            return;
        }

        for(moveFront(row); index(row) >= 0; moveNext(row)){
            EntryObj* entry = (EntryObj*)get(row);
            if(j < entry->col){
                insertBefore(row, newE);
            }
            else if(j == entry->col){
                entry->val = x;
            }
            else{
                append(row, newE);
            }
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


void printMatrix(FILE* out, Matrix M){

    if(M == NULL){
        printf("Matrix Error: calling printMatrix() on NULL matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if(out == NULL){
        printf("Matrix Error: calling printMatrix() on NULL file reference\n");
        exit(EXIT_FAILURE);
    }

    fprintf(out, "size is: %d\n", size(M));

    if(size(M) > 0){
        for(int row = 0; row < size(M); row++){
            fprintf(out, "%d:", row+1);
            
            if(length(M->rows[row]) > 0){
                EntryObj* curEnt;
                for(moveFront(M->rows[row]); index(M->rows[row]) >= 0; moveNext(M->rows[row])){
                    curEnt = get(M->rows[row]);
                    fprintf(out, " (%d %.1f)", curEnt->col, curEnt->val);
                }
                fprintf(out, "\n");
            }
        }
    }
    else{
        fprintf(out, "Matrix has no entries");
    }


}







