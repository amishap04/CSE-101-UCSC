#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "List.h"

#define MAX_LEN 300
void insertionSortList(List L, char** stringArray, FILE *out);



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

   for (int i = 0; i < array_length; i++) {
    //    printf(" after sort stringArray[i] is %s\n", stringArray[i]);
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
//		printf("cool  %d\n", get(L));

		if (i < length(L) - 1){
			moveNext(L);
		}

//		printf("hello  %d\n", get(L));
        }

  //      printf("length is %d\n", length(L));
//	printf("last value is: %d\n", indexArray[length(L) - 1]);
/*
        for(int i=0; i < length(L); i++){
                printf("index array at %d is %d\n", i, indexArray[i]);
        }
*/

/*
	for(int i=0; i < length(L); i++){
                printf("APPP string array at %d is %s\n", i, stringArray[i]);
        }
*/

        //printf("duck");
        for(int i=1; i< length(L); i++){

                int temp = indexArray[i];
                int j = i-1;


        

               // printf("befire comp\n");
		//printf("stringArray[j] is %s\n", stringArray[j]);
		//printf("stringArray[i] is %s\n", stringArray[i]);
                int comp = strcmp(stringArray[j], stringArray[temp]);
  //              printf("after comp %d\n", comp);
                while(j>=0 && comp > 0){

                        indexArray[j+1] = indexArray[j];
                        j--;
                }       

                indexArray[j+1] = temp;

        }


        for(int i=0; i < length(L); i++){
                printf("NEW index array at %d is %d\n", i, indexArray[i]);
		printf("NEW string array at %d is %s\n", i, stringArray[indexArray[i]]);
		fprintf(out, "%s\n", stringArray[indexArray[i]]);

        }



}















