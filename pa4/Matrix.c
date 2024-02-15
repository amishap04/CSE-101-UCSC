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
    int nnz;
    
} MatrixObj;



MatrixObj* newMatrix(int n){

    if(n < 1){
        printf("Matrix Error: calling newMatrix() on no rows reference\n");
	    exit(EXIT_FAILURE);
    }

    MatrixObj* mat = malloc(sizeof(MatrixObj));
    mat->size = n;
    mat->nnz = 0;
    mat->rows = malloc(n * sizeof(List));




/*
    for(int i = 0; i < n; i++){
        mat->rows[i] = newList();
    }
*/
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




void changeEntry(Matrix M, int i, int j, double x){

	if(M != NULL && 1 <= i && i <= M->size && 1 <= j && j <= M->size){


	List row = M->rows[i-1];

	if(row == NULL){
		//printf("%d row created\n", i-1);
		M->rows[i-1] = newList();
		row = M->rows[i-1];
		//printf("len is %d\n", length(row));	
	}


	if(x == 0){
		if(M != NULL && M->rows != NULL && row != NULL){

			if(length(row) > 0){

		
			for(moveFront(row); index(row) >= 0; moveNext(row)){

				if(((EntryObj*)get(row))->col == j){
					EntryObj* entry = (EntryObj*)get(row);
					delete(row);
					freeEntry(entry);
					M->nnz--;
					return;
				}
			}
			}
		}
		
	}
	else{
		//printf("changeentry else i is %d, j is %d,x is %f ROW LEN %d\n", i, j, x, length(row));
		if(M != NULL && M->rows != NULL && row != NULL){
			if(length(row) == 0){
				append(row, newEntry(j, x, size(M)));
				//printf("appended x: %d at col %d for empty list\n", i, j);
				M->nnz++;
				return;
			}
			else{

			//bool found = false;
			for(moveFront(row); index(row) >= 0; moveNext(row)){
				
                        	if(((EntryObj*)get(row))->col > j){
                                	insertBefore(row, newEntry(j, x, size(M)));
					M->nnz++;
					//found = true;
                                	return;
                        	}
				else if(((EntryObj*)get(row))->col == j){
					((EntryObj*)get(row))->val = x;
					//found = true;
					return;
				}
			
                	}
			//if(found == false){
				append(row, newEntry(j, x, size(M)));
				M->nnz++;
				return;
			//}
			}
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
	printf("size m %d\n", size(M));
        for(int row = 0; row < size(M); row++) {

	    List currL = M->rows[row];
	    if(currL == NULL){
		continue;
	    }

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
        if(currRow == NULL || length(currRow) == 0){
            continue;
        }
        EntryObj* entryA;
        //EntryObj* entry;
        for(moveFront(currRow); index(currRow) >= 0; moveNext(currRow)){
            entryA = get(currRow);
	    changeEntry(result, i+1, entryA->col, (entryA->val * x));
            //entry = newEntry(entryA->col, (entryA->val * x), size(A));
            //append(result->rows[i], entry);
	    //A->nnz++;
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
	
	if(row == NULL){
	   continue;
	}

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

	if(row == NULL){
           continue;
        }

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



/*
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
*/

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

    else{
        if(lenA >= lenB){

            //EntryObj* entA;
            EntryObj* entB;
            for(moveFront(B); index(B) >= 0; moveNext(B)){
                entB = ((EntryObj *)get(B));
               // entA = getColEnt(A, entB->col, size);

		for(moveFront(A); index(A) >= 0; moveNext(A)){
			if(entB->col == ((EntryObj *)get(A))->col){
				product += (entB->val * ((EntryObj *)get(A))->val);
				break;
			}
		}
	   }
	}

        else{
	    EntryObj* entA;
            //EntryObj* entB;
            for(moveFront(A); index(A) >= 0; moveNext(A)){
                entA = ((EntryObj *)get(A));
               

                for(moveFront(B); index(B) >= 0; moveNext(B)){
                        if(entA->col == ((EntryObj *)get(B))->col){
                                product += (entA->val * ((EntryObj *)get(B))->val);
                                break;
                        }
                }
           }


        } // this is not del


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
    int sizeA = size(A);
    for(int row = 0; row < sizeA; row++){
	 aL = A->rows[row];

	if(aL == NULL){
	  	continue;
	}


	if(length(aL) == 0){
		continue;
	}

        for(int col = 0; col < size(A); col++){
            bL = BT->rows[col];

	    if(bL == NULL){
		continue;
	    }

            if(length(aL) == 0 || length(bL) == 0){
                continue;
            }

	    else if(length(aL) == 0 && length(bL) == 0){
		continue;
	    }
            else{
		printf("PROD row is:  %d col is: %d\n", row, col);
                double prod = dotProduct(aL, bL, size(A));
                if(prod != 0){
                    changeEntry(result, row+1, col+1, prod);;
                }
                //else{
                   // changeEntry(result, row+1, col+1, prod);
		   // continue;
                //}
            }
        }
    }
    
    freeMatrix(&BT);
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

	if(aL == NULL && bL == NULL){
            continue;
        }
        if((aL != NULL && (length(aL) == 0)) && (bL != NULL && (length(bL) == 0))){
            continue;
        }


        EntryObj* currEntA = NULL;
        EntryObj* currEntB = NULL;
        for(int col = 0; col < size(A); col++){
            if(aL != NULL && length(aL) > 0){
                currEntA = getColEnt(aL, col+1, size(A));
            }
            if(bL != NULL && length(bL) > 0){
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

/*
    if(size(A) == 0 || size(B) == 0){
        printf("Matrix Error: calling sum() on empty Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    if(size(A) != size(B)){
        printf("Matrix Error: calling sum() on dif size Matrix reference\n");
        exit(EXIT_FAILURE);
    }
*/
	

    if(A == B){
	return scalarMult(2, A);
    }


	

    Matrix result = newMatrix(size(A));

    List aL, bL;
    for(int row = 0; row < size(A); row ++){
        aL = A->rows[row];
        bL = B->rows[row];

	if(aL == NULL && bL == NULL){
	    continue;
	}
        if((aL != NULL && (length(aL) == 0)) && (bL != NULL && (length(bL) == 0))){
            continue;
        }


        EntryObj* currEntA = NULL;
        EntryObj* currEntB = NULL;
        for(int col = 0; col < size(A); col++){
		
            if(aL != NULL && length(aL) > 0){
                currEntA = getColEnt(aL, col+1, size(A));
            }
            if(bL != NULL && length(bL) > 0){
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

/*
    int count = 0;
    for(int row = 0; row < size(M); row++){
        count += length(M->rows[row]);
    }

    return count;
*/
    return M->nnz;

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

	if(rowA == NULL && rowB == NULL){
		continue;
	}
	else if(rowA == NULL && rowB != NULL){
		return 0;
	}

	else if(rowB == NULL && rowA != NULL){
		return 0;
	}


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

	if(currList == NULL){
		continue;
	}

	if(length(currList) == 0){
		continue;
	}
	else{
		while(length(currList) > 0){
			moveFront(currList);
			EntryObj* temp = get(currList);
			deleteFront(currList);
			freeEntry(temp);
			M->nnz--;
		}
	}


    }

}




