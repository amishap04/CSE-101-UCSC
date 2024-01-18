Lex: Lex.o List.o
	gcc -std=c17 -Wall -o Lex Lex.o List.o ListTest.o

Lex.o : Lex.c List.h
	gcc -std=c17 -Wall -c Lex.c

ListTest: ListTest.o List.o
	gcc -std=c17 -Wall -o ListClient ListClient.o List.o

ListTest.o : ListTest.c List.h
	gcc -std=c17 -Wall -c ListClient.c

List.o : List.c List.h
	gcc -std=c17 -Wall -c List.c

clean :
	rm -f Lex ListTest Lex.o ListTest.o List.o

checkClient : 
	valgrind --leak-check=full ListTest

checkLex :
	valgrind --leak-check=full Lex in3 blah3

