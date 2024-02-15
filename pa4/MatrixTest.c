/**
 * * * * Amisha Prasad // First and Last Name
 * * * * aprasa14 // UCSC UserID
 * * * * 2024 Winter CSE101 PA4 // Assignment Number
 * * * * MatrixTest.c // FileName
 * * * * Testing for Matrix ADT // Description
 * * * ***/

#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"
     
int main(){
   int n=100000;
   Matrix A = newMatrix(n);
   Matrix B = newMatrix(n);
   Matrix C, D, E, F, G, H;

   changeEntry(A, 1,1,1); changeEntry(B, 1,1,1);
   changeEntry(A, 1,2,2); changeEntry(B, 1,2,0);
   changeEntry(A, 1,3,3); changeEntry(B, 1,3,1);
   changeEntry(A, 2,1,4); changeEntry(B, 2,1,0);
   changeEntry(A, 2,2,5); changeEntry(B, 2,2,1);
   changeEntry(A, 2,3,6); changeEntry(B, 2,3,0);
   changeEntry(A, 3,1,7); changeEntry(B, 3,1,1);
   changeEntry(A, 3,2,8); changeEntry(B, 3,2,1);
   changeEntry(A, 3,3,9); changeEntry(B, 3,3,1);

   printf("%d\n", NNZ(A));
   printMatrix(stdout, A);
   
   printf("\n");


   printf("%d\n", NNZ(B));
   printMatrix(stdout, B);
   printf("\n");

   C = scalarMult(1.5, A);
   printf("%d\n", NNZ(C));
   printMatrix(stdout, C);
   printf("\n");

   D = sum(A, B);
   printf("%d\n", NNZ(D));
   printMatrix(stdout, D);
   printf("\n");

   E = diff(A, A);
   printf("%d\n", NNZ(E));
   printMatrix(stdout, E);
   printf("\n");

   F = transpose(B);
   printf("%d\n", NNZ(F));
   printMatrix(stdout, F);
   printf("\n");

   G = product(B, B);
   printf("%d\n", NNZ(G));
   printMatrix(stdout, G);
   printf("\n");

   H = copy(A);
   printf("%d\n", NNZ(H));
   printMatrix(stdout, H);
   printf("\n");

   printf("%s\n", equals(A, H)?"true":"false" );
   printf("%s\n", equals(A, B)?"true":"false" );
   printf("%s\n", equals(A, A)?"true":"false" );

   makeZero(A);
   printf("%d\n", NNZ(A));
   printMatrix(stdout, A);







// test here
/*
Matrix Amisha = newMatrix(100);
    changeEntry(Amisha, 2, 1, 2);
    changeEntry(Amisha, 3, 1, 5);
    changeEntry(Amisha, 1, 2, 2);
    changeEntry(Amisha, 1, 3, 5);
    changeEntry(Amisha, 1, 1, 4);
    changeEntry(Amisha, 2, 2, 2);
    changeEntry(Amisha, 2, 5, 0);
    changeEntry(Amisha, 2, 3, 0);
    changeEntry(Amisha, 3, 3, 5);
    printf("Amisha NNZ is %d\n", NNZ(Amisha));
    printMatrix(stdout, Amisha);
    printf("\n");





Matrix Am = newMatrix(100);
Matrix Bm = newMatrix(100);
    changeEntry(Am, 1, 1, 1);
    changeEntry(Am, 1, 1, 1);
    changeEntry(Am, 1, 3, 1);
    changeEntry(Bm, 1, 1, 1);
    changeEntry(Bm, 1, 3, 1);

    printMatrix(stdout, Am);
    printMatrix(stdout, Bm);
    printf("Am and Bm %s\n", equals(Am, Bm)?"true":"false" );


*/

Matrix Am = newMatrix(100);
Matrix Bm = newMatrix(100);

    changeEntry(Am, 1, 1, 4);
    changeEntry(Am, 1, 2, 2);
    changeEntry(Am, 1, 3, 0);
    changeEntry(Am, 2, 1, 2);
    changeEntry(Am, 3, 1, 0);
    changeEntry(Am, 2, 2, 2);
    changeEntry(Am, 3, 3, 0);
   // Bm = sum(Am, Am);



    changeEntry(Bm, 1, 1, -4);
    changeEntry(Bm, 1, 2, 0);
    changeEntry(Bm, 2, 1, 0);
    changeEntry(Bm, 2, 2, -2);
    changeEntry(Bm, 2, 4, 2);
    changeEntry(Bm, 3, 1, 0);
    changeEntry(Bm, 3, 2, 2);
    changeEntry(Bm, 7, 8, 5);
	

Matrix result = newMatrix(100);
    
    result = sum(Am, Bm);
    printMatrix(stdout, Am);
    printMatrix(stdout, Bm);
    printf("AM %d\n", NNZ(Am));
    printf("BM %d\n", NNZ(Bm));


    printMatrix(stdout, result);



    Matrix pC = newMatrix(15);
    Matrix Aaa = newMatrix(15);
    Matrix Bbb = newMatrix(15);


    if (!equals(Aaa, Bbb))
	printf("returning 1\n");
    if (equals(Aaa, pC))
    	printf("returning 2\n");
    Matrix MMM = newMatrix(10);
    changeEntry(MMM, 5, 5, 5);
    makeZero(MMM);
    if (!equals(Aaa, MMM))
      printf("returning 3\n");


















   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&C);
   freeMatrix(&D);
   freeMatrix(&E);
   freeMatrix(&F);
   freeMatrix(&G);
   freeMatrix(&H);

   return EXIT_SUCCESS;
}





