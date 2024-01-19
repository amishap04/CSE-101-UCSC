#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 300

// Function to populate the list with sorted indices
void populateListWithSortedIndices(List list, char** array, int arrayLength) {
    if (arrayLength <= 0) return;

    append(list, 0); // Add the first index to start the sorting process

    for (int i = 1; i < arrayLength; i++) {
        char *currentString = array[i];
        int j = i - 1;

        moveBack(list);
        while (j >= 0 && strcmp(currentString, array[get(list)]) < 0) {
            movePrev(list);
            j--;
        }

        if (index(list) >= 0) {
            insertAfter(list, i);
        } else {
            prepend(list, i);
        }
    }
}

int main(int argc, char *argv[]) {
    FILE *in, *out;
    char line[MAX_LEN];
    char **lines;
    int line_count = 0;
    List sortedIndices;

// Check command line for correct number of arguments
    if (argc != 3) {
	printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

// Open files for reading and writing 
    in = fopen(argv[1], "r");
    if (in == NULL) {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(EXIT_FAILURE);
    }


    out = fopen(argv[2], "w");
    if (out == NULL) {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(EXIT_FAILURE);
    }

// Read lines of input file and count them
    lines = malloc(MAX_LEN * sizeof(char *));
    while (fgets(line, MAX_LEN, in) != NULL) {
        lines[line_count] = strcmp(line);
        line_count++;
    }

// Populate the list with indices sorted by the lexicographic order of lines
    sortedIndices = newList();
    populateListWithSortedIndices(sortedIndices, lines, line_count);

// Write sorted lines to the output file
   for (moveFront(sortedIndices); index(sortedIndices) >= 0; moveNext(sortedIndices)) {
        fprintf(out, "%s", lines[get(sortedIndices)]);
    }

// Free memory and close files
for (int i = 0; i < line_count; i++) {
        free(lines[i]);
    }
    free(lines);
    freeList(&sortedIndices);
    fclose(in);
    fclose(out);

    return 0;
}






