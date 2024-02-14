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

void freeMatrixList(List* pL) {
    if (pL != NULL && *pL != NULL) {
        clear(*pL);
        free(*pL);
        *pL = NULL;
    }
}




void freeMatrix(Matrix* pM) {
    if (pM != NULL && *pM != NULL) {
        Matrix temp = *pM;

        for (int i = 0; i < temp->size; i++) {
            if (temp->rows[i] != NULL) {

		if(length(temp->rows[i]) > 0){
			for(moveFront(temp->rows[i]); index(temp->rows[i]) >= 0; moveNext(temp->rows[i])){
				freeEntry(get(temp->rows[i]));
			}
		}

                freeList(&(temp->rows[i]));
 
            }
        }

        free(temp->rows); 
        free(temp);       
        *pM = NULL;       
    }
}


/*
void changeEntry(Matrix M, int i, int j, double x) {
    if(M != NULL && 1 <= i && i <= M->size && 1 <= j && j <= M->size) {
        List row = M->rows[i-1];

	if(length(row) == 0){
		if(x != 0){
			EntryObj* entry = newEntry(j, x, M->size);
			prepend(M->rows[i-1], entry);
			return;
		}
		else{
			return;
		}
		
			
	}


        moveFront(row); 

        while(index(row) >= 0) { 
            EntryObj* entry = (EntryObj*)get(row);
            if(entry->col == j) {
                if(x == 0) {
                     
                    delete(row);
		    freeEntry(entry); 
                    return; 
                } else {
                    entry->val = x; 
                    return; 
                }
            } else if(entry->col > j) {
                break; 
            }
            moveNext(row);
        }

        
        if(x != 0) {
            EntryObj* newE = newEntry(j, x, M->size);
            if(index(row) >= 0) {
                insertBefore(row, newE); 
            } else {
                append(row, newE); 
            }
        }
    }
}
*/



void changeEntry(Matrix M, int i, int j, double x){

	List row = M->rows[i-1];

	if(x == 0){
		if(M != NULL && M->rows != NULL && row != NULL){
		// check if ij entry exists
			for(moveFront(row); index(row) >= 0; moveNext(row)){

				if(((EntryObj*)get(row))->col == j){
					delete(row);
					break;
				}
			}
		}
		
	}
	else{
		// check if ij exists
		// if exists then change val
		// else append
		if(M != NULL && M->rows != NULL && row != NULL){
			for(moveFront(row); index(row) >= 0; moveNext(row)){
                        	if(((EntryObj*)get(row))->col > j){
                                	insertBefore(row, newEntry(j, x, size(M)));
                                	break;
                        	}
			
                	}
			append(row, newEntry(j, x, size(M)));
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



    EntryObj* frontEtr = front(L);
    EntryObj* backEtr = back(L);

    int frontCol = frontEtr->col;
    int backCol = backEtr->col;

    int fdif = col - frontCol;
    int bdif = backCol- col;

    EntryObj* curEnt;
    if(fdif <= bdif){

        for(moveFront(L); index(L) >= 0; moveNext(L)){
            curEnt = get(L);
            if(curEnt->col == col){
                return curEnt;
            }
	        else if(curEnt->col >  col){
		        return NULL;
	        }
        }   


    }

    else{
        for(moveBack(L); index(L) >= 0; movePrev(L)){
            curEnt = get(L);
            if(curEnt->col == col){
                return curEnt;
            }
	        else if(curEnt->col <  col){
		        return NULL;
	        }
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
    
    freeMatrix(&BT);
    return result;

}



/*
Matrix product(Matrix A, Matrix B) {
          
    if (A == NULL) {
        printf("Matrix Error: calling product() on NULL Matrix reference\n");
        exit(1);
    }

           
    if (B == NULL) {
        printf("Matrix Error: calling product() on NULL Matrix reference\n");
        exit(1);
    }
    
    
    if (size(A) != size(B)) {
        printf("Matrix Error: calling product() on matrices of different sizes\n");
        exit(1);
    }
    
    
    B = transpose(B);
    
    Matrix product_matrix = newMatrix(A->size);
    
    int a = 0;
    
    while(a < product_matrix->size) {
        
        List product_L = product_matrix->rows[a];
        
        List product_A = A->rows[a];

      
        if (!(length(product_A) == 0)) {
            int b = 0;

            
            while(b < product_matrix->size) {
                
                List product_B = B->rows[b];
                
                double product = 0;

                
                moveFront(product_A);
                moveFront(product_B);
                
                
                while ((index(product_A) >=0) && (index(product_B) >= 0)) {
                    
                    Entry row_A = (Entry)get(product_A);
                    Entry row_B = (Entry)get(product_B);

                    
                    if (row_A->col > row_B->col){
                        moveNext(product_B);
                    }

                    
                    if(row_A->col == row_B->col) {
                        
                        product += row_A->val * row_B->val;
                        
                        moveNext(product_A);
                        moveNext(product_B);
                    }
                    
                    
                    if (row_B->col > row_A->col){
                        moveNext(product_A);
                    }
                }

                
                if (!(product == 0)) {
                    
                    append(product_L, newEntry((b + 1), product, size(B)));
                    
                    //product_matrix->nnz = product_matrix->nnz+ 1;
                }

                ++b;
            }
        }

        ++a;
    }
    
    
    freeMatrix(&B);
    return product_matrix;
}

*/


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

	

    if(A == B){
	return scalarMult(2, A);
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


int equals(Matrix A, Matrix B) {
    if(A == NULL || B == NULL){
        printf("Matrix Error: calling equals() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    if(size(A) == 0 || size(B) == 0){
        printf("Matrix Error: calling equals() on empty Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    if (size(A) != size(B)) return 0;  

    for (int i = 0; i < size(A); i++) {
        List rowA = A->rows[i];
        List rowB = B->rows[i];


	if(length(rowA) == 0 && length(rowB) == 0){
		continue;
	}

        if (length(rowA) != length(rowB)) return 0;  

        moveFront(rowA);
        moveFront(rowB);
        while (index(rowA) >= 0 && index(rowB) >= 0) {
            EntryObj* entryA = (EntryObj*)get(rowA);
            EntryObj* entryB = (EntryObj*)get(rowB);

            if (entryA->col != entryB->col || entryA->val != entryB->val) return 0;  

            moveNext(rowA);
            moveNext(rowB);
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
	List currList = M->rows[row];
	if(length(currList) == 0){
		continue;
	}
	else{
		while(length(currList) > 0){
			moveFront(currList);
			EntryObj* temp = get(currList);
			deleteFront(currList);
			freeEntry(temp);
		}
	}


    }

}


