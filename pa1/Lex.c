#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "List.h"

#define MAX_LEN 300
void insertionSortList(List L, char** stringArray, FILE *out);
void insertionSortString(List L, char** stringArray);


int main(int argc, char * argv[]){

   int token_count, line_count;
   FILE *in, *out;
   char line[MAX_LEN];
   char tokenBuffer[MAX_LEN];
   char* token;

   
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

    
   in = fopen(argv[1], "r");
      if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }

   out = fopen(argv[2], "w");
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   int size = 1;
   char** stringArray = malloc(size * sizeof(char*));

   line_count = 0;
   while( fgets(line, MAX_LEN, in) != NULL)  {
      line_count++;

      
      token_count = 0;
      tokenBuffer[0] = '\0';

      
      token = strtok(line, " \n");
      
      while( token!=NULL ){ 
         
         strcat(tokenBuffer, "   ");
         strcat(tokenBuffer, token);
         strcat(tokenBuffer, "\n");
         token_count++;

        
         token = strtok(NULL, " \n");
      }

    
     // fprintf(out, "line %d contains %d ", line_count, token_count);
     // fprintf(out, "token%s: \n", token_count==1?"":"s" );
     // fprintf(out, "%s\n", tokenBuffer);

      if(size == 1){
      	stringArray[size-1] = strdup(tokenBuffer);
        size++;
      }

      else{

      char** temp = realloc(stringArray, size * sizeof(char*));

      if (temp == NULL) {
        fprintf(stderr, "Memory reallocation failed\n");
        free(stringArray[0]);
        free(stringArray);
        return 1;
    }
    stringArray = temp;	

    stringArray[size-1] = strdup(tokenBuffer);
    size++;

    }
 
   }



   int array_length = size-1;

   
   for (int i = 0; i < array_length; i++) {
//        printf("stringArray[i] is %s\n", stringArray[i]);
    }


   List indexList = newList();


   for (int i = 0; i < array_length; i++) {
       append(indexList, i);
   }

  // printList(stdout, indexList);
  // printf("\n");

   insertionSortList(indexList, stringArray, out);
   // insertionSortString(indexList, stringArray);

   for (int i = 0; i < array_length; i++) {
    }

/*
   moveFront(indexList);
   printf("cursor val is: %d\n", get(indexList));
   for(int i=0; i<length(indexList); i++){
//	fprintf(out, "%s\n", stringArray[get(indexList)]);
        moveNext(indexList);
   }
*/

   //printf("sorted list print\n");
   //printList(stdout, indexList);
   //printf("\n");



   for (int i = 0; i < array_length; i++) {
        free(stringArray[i]);
    }
    free(stringArray);   


   fclose(in);
   fclose(out);


   return(0);
}




void insertionSortList(List L, char** stringArray, FILE *out){


        int indexArray[length(L)];

        moveFront(L);

	
        for(int i=0; i < length(L); i++){
                indexArray[i] = get(L);
		indexArray[i] = i;
//		printf("cool  %d\n", get(L));

		if (i < length(L) - 1){
			moveNext(L);
		}

//		printf("hello  %d\n", get(L));
        }

        int tempIndx;
	char* tempVal;
	int j;
	
        for(int i=1; i< length(L); i++){

                tempIndx = i;
		tempVal = stringArray[i];
                j = i-1;


                while(j>=0 && strcmp(stringArray[j], tempVal) > 0){

                        stringArray[j+1] = stringArray[j];
                        j--;
                }       

                stringArray[j+1] = tempVal;

        }


        for(int i=0; i < length(L); i++){
                //printf("index array at %d is %d\n", i, indexArray[i]);
		//printf("string array at %d is %s\n", i, stringArray[i]);
		fprintf(out, "%s\n", stringArray[indexArray[i]]);

        }



}



void insertionSortString(List L, char** stringArray) {
    if (length(L) <= 1) return; // No need to sort if the list is empty or has only one element

    moveFront(L);
    moveNext(L); // Start from the second element

    while (index(L) >= 0) {
        int temp = get(L);
        char* tempString = stringArray[temp];
        movePrev(L);

        while (index(L) >= 0 && strcmp(stringArray[get(L)], tempString) > 0) {
            moveNext(L); // Move the cursor back to where it was
            insertBefore(L, temp); // Insert the index before its current position
            delete(L); // Delete the index at its original position
            movePrev(L); // Move back to continue the sort
        }

        moveNext(L); // Move to the next element to be sorted
    }
}









