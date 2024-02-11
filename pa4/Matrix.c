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
    if(x == 0){
        return;
    }

    if(M != NULL && 1 <= i && i <= M->size && 1 <= j && j <= M->size){
        List row = M->rows[i-1];

        if(row == NULL){
            return;
        }

        EntryObj* entry;
        bool found = false;

	if(length(row) == 0){
		EntryObj* newE = newEntry(j, x, M->size);
		prepend(M->rows[i-1], newE);
	}

	else{

        	for(moveFront(row); index(row) >= 0; moveNext(row)){
            		entry = (EntryObj*)get(row);
            		if(j < entry->col){
                		EntryObj* newE = newEntry(j, x, M->size);
                		insertBefore(row, newE);
                		found = true;
                		break;
            		} else if(j == entry->col){
                		entry->val = x;
                		found = true;
                		break;
            		}
        	}
	

        	if(!found){
            		EntryObj* newE = newEntry(j, x, M->size);
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



double dotProduct(List A, List B, int size){

    if(A == NULL || B == NULL){
        printf("List Error: calling dotProduct() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    double product = 0.0;

    int lenA = length(A);
    int lenB = length(B);

    if(lenA == 0 || lenB == 0){
        return product;
    }

    else if(lenA == 0 && lenB == 0){
	return product;
    }

    else{
        if(lenA >= lenB){

            EntryObj* entA;
            EntryObj* entB;
            for(moveFront(B); index(B) >= 0; moveNext(B)){
                entB = ((EntryObj *)get(B));
                entA = getColEnt(A, entB->col, size);

                if(entA == NULL){
                    continue;
                }
                else{
                    product += (entB->val * entA->val);
                }
            }
        }
        else{
            EntryObj* entA;
            EntryObj* entB;
            for(moveFront(A); index(A) >= 0; moveNext(A)){
                entA = ((EntryObj *)get(A));
                entB = getColEnt(B, entA->col, size);

                if(entB == NULL){
                    continue;
                }
                else{
                    product += (entB->val * entA->val);
                }
            }

        }
            

    }




    return product;

}



Matrix product(Matrix A, Matrix B){

    if(A == NULL || B == NULL){
        printf("Matrix Error: calling product() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    if(size(A) == 0 || size(B) == 0){
        printf("Matrix Error: calling product() on empty Matrix reference\n");
        exit(EXIT_FAILURE);
    }


    if(size(A) != size(B)){
        printf("Matrix Error: calling product() on dif size Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    Matrix result = newMatrix(size(A));
    Matrix BT = transpose(B);
    
    List aL, bL;
    for(int row = 0; row < size(A); row++){
	 aL = A->rows[row];

	if(length(aL) == 0){
		continue;
	}

        for(int col = 0; col < size(A); col++){
            bL = BT->rows[col];

            if(length(aL) == 0 || length(bL) == 0){
                continue;
            }

	    else if(length(aL) == 0 && length(bL) == 0){
		continue;
	    }
            else{
                double prod = dotProduct(aL, bL, size(A));
                if(prod == 0){
                    continue;
                }
                else{
                    changeEntry(result, row+1, col+1, prod);
                }
            }
        }
    }
    

    return result;

}



Matrix diff(Matrix A, Matrix B){

    if(A == NULL || B == NULL){
        printf("Matrix Error: calling diff() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    if(size(A) == 0 || size(B) == 0){
        printf("Matrix Error: calling diff() on empty Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    if(size(A) != size(B)){
        printf("Matrix Error: calling diff() on dif size Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    Matrix result = newMatrix(size(A));

    List aL, bL;
    for(int row = 0; row < size(A); row ++){
        aL = A->rows[row];
        bL = B->rows[row];

        if(length(aL) == 0 && length(bL) == 0){
            continue;
        }

        EntryObj* currEntA = NULL;
        EntryObj* currEntB = NULL;
        for(int col = 0; col < size(A); col++){
            if(length(aL) > 0){
                currEntA = getColEnt(aL, col+1, size(A));
            }
            if(length(bL) > 0){
                currEntB = getColEnt(bL, col+1, size(B));
            }


            if(currEntA == NULL && currEntB == NULL){
                continue;
            }
            else if(currEntB == NULL){
                changeEntry(result, row+1, col+1, currEntA->val);
            }
            else if(currEntA == NULL){
                changeEntry(result, row+1, col+1, (-1 * currEntB->val));
            }
            else{

		if((currEntA->val - currEntB->val) != 0){
			changeEntry(result, row+1, col+1, (currEntA->val - currEntB->val));
		}
            }

            
        }
        
    
    }



    return result;


}



Matrix sum(Matrix A, Matrix B){

    if(A == NULL || B == NULL){
        printf("Matrix Error: calling sum() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    if(size(A) == 0 || size(B) == 0){
        printf("Matrix Error: calling sum() on empty Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    if(size(A) != size(B)){
        printf("Matrix Error: calling sum() on dif size Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    Matrix result = newMatrix(size(A));

    List aL, bL;
    for(int row = 0; row < size(A); row ++){
        aL = A->rows[row];
        bL = B->rows[row];

        if(length(aL) == 0 && length(bL) == 0){
            continue;
        }

        EntryObj* currEntA = NULL;
        EntryObj* currEntB = NULL;
        for(int col = 0; col < size(A); col++){
            if(length(aL) > 0){
                currEntA = getColEnt(aL, col+1, size(A));
            }
            if(length(bL) > 0){
                currEntB = getColEnt(bL, col+1, size(B));
            }


            if(currEntA == NULL && currEntB == NULL){
                continue;
            }
            else if(currEntB == NULL){
                changeEntry(result, row+1, col+1, currEntA->val);
            }
            else if(currEntA == NULL){
                changeEntry(result, row+1, col+1, (currEntB->val));
            }
            else{

                if((currEntA->val + currEntB->val) != 0){
                        changeEntry(result, row+1, col+1, (currEntA->val + currEntB->val));
                }
            }


        }


    }



    return result;


}


int NNZ(Matrix M){

    if(M == NULL){
        printf("Matrix Error: calling NNZ() on NULL matrix reference\n");
        exit(EXIT_FAILURE);
    }

    if(size(M) <= 0){
        printf("Matrix Error: calling NNZ() on empty matrix reference\n");
        exit(EXIT_FAILURE);
    }

    int count = 0;
    for(int row = 0; row < size(M); row++){
        count += length(M->rows[row]);
    }

    return count;


}


int equals(Matrix A, Matrix B){

    if(A == NULL || B == NULL){
        printf("Matrix Error: calling equals() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    if(size(A) == 0 || size(B) == 0){
        printf("Matrix Error: calling equals() on empty Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    if(size(A) != size(B)){
        return 0;
    }

    for(int row = 0; row < size(A); row++){
        if(length(A->rows[row]) != length(B->rows[row])){
            return 0;
        }
    }

    EntryObj* entrA;
    EntryObj* entrB;
    for(int row = 0; row < size(A); row++){

	if(length(A->rows[row]) == 0 && length(B->rows[row]) == 0){
		continue;
	}

        for(int col = 0; col < size(A); col++){

            entrA = getColEnt(A->rows[row], col+1, size(A));

            entrB = getColEnt(B->rows[row], col+1, size(B));

	
	    if(entrA == NULL && entrB == NULL){
		continue;
	    }

            if(entrA == NULL && entrB != NULL){
                return 0;
            }
            else if(entrB == NULL && entrA != NULL){
                return 0;
            }
            else if(entrA->val != entrB->val){
                return 0;
            }

        }
    }


    return 1;    

}



void makeZero(Matrix M){
    if(M == NULL){
        printf("Matrix Error: calling makeZero() on NULL matrix reference\n");
        exit(EXIT_FAILURE);
    }

    if(size(M) <= 0){
        printf("Matrix Error: calling makeZero() on empty matrix reference\n");
        exit(EXIT_FAILURE);
    }

    for(int row = 0; row < size(M); row++){
        clear(M->rows[row]);
    }

}
