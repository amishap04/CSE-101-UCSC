#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define MAX_LEN 300

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

    
      fprintf(out, "line %d contains %d ", line_count, token_count);
      fprintf(out, "token%s: \n", token_count==1?"":"s" );
      fprintf(out, "%s\n", tokenBuffer);

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
        printf("%s\n", stringArray[i]);
    }



   for (int i = 0; i < array_length; i++) {
        free(stringArray[i]);
    }
    free(stringArray);   


   fclose(in);
   fclose(out);


   return(0);
}
