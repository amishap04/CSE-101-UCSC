/**
 * * * * Amisha Prasad // First and Last Name
 * * * * aprasa14 // UCSC UserID
 * * * * 2024 Winter CSE101 PA4 // Assignment Number
 * * * * Matrix.h// FileName
 * * * * Header for Matrix ADT // Description
 * * * ***/



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "List.h"

typedef struct EntryObj* Entry;
typedef struct MatrixObj* Matrix;

Matrix newMatrix(int n);
void freeMatrix(Matrix* pM);
void changeEntry(Matrix M, int i, int j, double x);
Entry newEntry(int col, double val, int mSize);
void freeEntry(Entry pE);
int size(Matrix M);
void printMatrix(FILE* out, Matrix M);
Entry getColEnt(List L, int col, int size);
Matrix scalarMult(double x, Matrix A);
Matrix transpose(Matrix A);
Matrix copy(Matrix A);
double dotProduct(List A, List B, int size);
Matrix product(Matrix A, Matrix B);
Matrix diff(Matrix A, Matrix B);
Matrix sum(Matrix A, Matrix B);



