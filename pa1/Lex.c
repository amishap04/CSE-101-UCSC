#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define MAX_LEN 300

char** getArray();
// void addArrayElement(char** array, char* value, int* size);
void printArray(char** array, int size);



int main(int argc, char * argv[]){

   int token_count, line_count;
   FILE *in, *out;
   char line[MAX_LEN];
   char tokenBuffer[MAX_LEN];
   char* token;

// check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }


 // open files for reading and writing 
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


   // Initial size of the array
        int size = 1;
   // Create an array of character pointers, initially to hold 2 elements
/*
	char **stringArray = malloc(size * sizeof(char*));

	if (stringArray == NULL) {
       		 fprintf(stderr, "Memory allocation failed!\n");
                 return 1;
        }
*/

	char** stringArray = getArray(size);
	// char * value = "One";
	// void addArrayElement(stringArray, value, size);


/*
	stringArray[size-1] = malloc(strlen("One") + 1);
	if (stringArray[size-1] != NULL) {
        	strcpy(stringArray[size-1], "One");
		size++;
        } else {  
	         free(stringArray);
                 fprintf(stderr, "Memory allocation for string failed!\n");
		 return 1;
	  }

	stringArray[size-1] = malloc(strlen("Two") + 1);
        if (stringArray[size-1] != NULL) {
                strcpy(stringArray[size-1], "Two");
		size++;
        } else {
              // Handle memory allocation failure for the string
	      free(stringArray);
              fprintf(stderr, "Memory allocation for string failed!\n");
	      return 1;
          }


	for(int i = 0; i < size-1; i++){
		printf("Value at i is: %s\n", stringArray[i]);
	}
	free(stringArray);
*/	




// read each line of input file, then count and print tokens 
   line_count = 0;
   while( fgets(line, MAX_LEN, in) != NULL)  {
      line_count++;

      // get tokens in this line
      token_count = 0;
      tokenBuffer[0] = '\0';

      // get first token
      token = strtok(line, " \n");

      printf("hello %d\n", line_count);

      while( token!=NULL ){ // we have a token


	printf("Amisha\n");
         // update token buffer

	 strcat(tokenBuffer, "   ");
         strcat(tokenBuffer, token);
         strcat(tokenBuffer, "\n");
         token_count++;

         // get next token
         token = strtok(NULL, " \n");
	 printf("tokenBuffer: %s\n", tokenBuffer);

	 if(tokenBuffer != NULL || strlen(tokenBuffer) > 0){
                stringArray[line_count-1] = malloc(strlen(tokenBuffer) + 1);
         if (stringArray[line_count-1] != NULL) {
                strcpy(stringArray[line_count-1], tokenBuffer);
		printf("line count %d array element value %s\n", line_count, stringArray[line_count-1]);
        }

        }
  }

      }

      // print tokens in this line
      fprintf(out, "line %d contains %d ", line_count, token_count);
      fprintf(out, "token%s: \n", token_count==1?"":"s" );
      fprintf(out, "ancd %s\n", tokenBuffer);
/*
    if(tokenBuffer != NULL || strlen(tokenBuffer) > 0){
      stringArray[line_count-1] = malloc(strlen(tokenBuffer) + 1);
        if (stringArray[line_count-1] != NULL) {
                strcpy(stringArray[line_count-1], tokenBuffer);
        } else {
                 free(stringArray);
                 fprintf(stderr, "Memory allocation for string failed!\n");
                 return 1;
        	  }

   	}
  }

   printf("%d\n", line_count);
   for(int i = 0; i < line_count; i++){
                printf("Value at %d is: %s\n", i, stringArray[i]);
   }
   //free(stringArray);
*/

	char * comp = "Three";
	printf("compare %d\n", strcmp(comp, stringArray[2]));
	printArray(stringArray, line_count);

   // close files 
   fclose(in);
   fclose(out);

   return(0);
}





  char** getArray(int size){
	char **stringArray = malloc(size * sizeof(char*));

        if (stringArray == NULL) {
                 fprintf(stderr, "Memory allocation failed!\n");
                //  return 1;
        }
  return stringArray;

  }


  void printArray(char** array, int size){
	for(int i=0; i<size; i++){
		printf("element at %d is %s\n", i, array[i]);
	}

  }







/*
  void addArrayElement(char** stringArray, char* value, int* size){
        

	stringArray[*size-1] = malloc(strlen(value) + 1);
        if (stringArray[*size-1] != NULL) {
                strcpy(stringArray[*size-1], *value);
                *size++;
		printf("%d\n", *size);
        } else {
	// Handle memory allocation failure for the string
		free(stringArray);
                fprintf(stderr, "Memory allocation for string failed!\n");
//                 return 1;
          }
	

  }
*/










