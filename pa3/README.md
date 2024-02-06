 * * * * Amisha Prasad // First and Last Name
 * * * * aprasa14 // UCSC UserID
 * * * * 2024 Winter CSE101 PA3 // Assignment Number
 * * * * README.md // FileName
 * * * * Description of every file submitted // Description
 

The files I used in this assignment and what they're usage was:

List.c: Contains all of the list functions that I used to create queue and otherlist objects in Graph.c and FindComponents.c\


List.h: This is the header file containing everything like function defintions for List.c


Graph.c: Contains all of the graph functions that I used to create the graph struct. I decided to remake all of Graph.c rather than reuse the one from PA2 but I reused some of the funcitons. I used these functions in FindComponents.c. I also used time as a local variable being passed into the visit() function as an input.


Graph.h: This is the header file that I used to create all the function definitions for the functions in Graph.c


GraphTest.c: Contains all the tests I ran on Graph.c to make sure it works


FindComponents.c: Contains my main function where I did file parsing, creation of the graph, transposing of the graph, DFS call on both graphs, printing of strongly connected components, and printing all of this to the output file.


Makefile: Correctly compiles my program and creates the binary executable file


README.md: Contains all of the information around each of the files I am submiting for PA3


