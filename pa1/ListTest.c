#include "List.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
/*
  List Amisha = newList();
  myPrintList(Amisha);

  append(Amisha, 4);
  myPrintList(Amisha);



  append(Amisha, 5);
  myPrintList(Amisha);

  append(Amisha, 6);
  myPrintList(Amisha);
  
  prepend(Amisha, 3);
  myPrintList(Amisha);

  prepend(Amisha, 2);
  myPrintList(Amisha);

  prepend(Amisha, 1);
  myPrintList(Amisha);
*/

  List A = newList();
  List B = newList();
  List C = NULL;
  int i;

  for (i = 1; i <= 20; i++) {
    append(A, i);
    prepend(B, i);
  }

  //printf("back of List A %d\n", back(A));
  //printf("front of List A %d\n", front(A));
  //printf("back of List B %d\n", back(B));
  //printf("front of List B %d\n", front(B));

  printList(stdout, A);
  printf("\n");
  printList(stdout, B);
  printf("\n");

  for (moveFront(A); index(A) >= 0; moveNext(A)) {
    printf("%d ", get(A));
  }
  printf("\n");

  for (moveBack(B); index(B) >= 0; movePrev(B)) {

   // printf("index value at back %d\n", index(B));
    printf("%d ", get(B));
  }
  printf("\n");

  C = copyList(A);
  printf("%s\n", equals(A, B) ? "true" : "false");
  printf("%s\n", equals(B, C) ? "true" : "false");
  printf("%s\n", equals(C, A) ? "true" : "false");

  moveFront(A);
  for (i = 0; i < 5; i++)
    moveNext(A);       // at index 5
  insertBefore(A, -1); // at index 6
  for (i = 0; i < 9; i++)
    moveNext(A); // at index 15
  insertAfter(A, -2);
  for (i = 0; i < 5; i++)
    movePrev(A); // at index 10
  printf("before: %d\n", get(A));
  delete (A);
  //printf("after: %d\n", get(A));
  printList(stdout, A);
  printf("\n");
  printf("%d\n", length(A));
  clear(A);
  printf("%d\n", length(A));

  freeList(&A);
  freeList(&B);
  freeList(&C);

  return (0);



}

