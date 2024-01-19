Lex: Lex.o List.o
	gcc -std=c17 -g -Wall -o Lex Lex.o List.o

Lex.o : Lex.c List.h
	gcc -std=c17 -g -Wall -c Lex.c

ListClient : ListClient.o List.o
	gcc -std=c17 -g -Wall -o ListClient ListClient.o List.o

ListClient.o : ListClient.o List.h
	gcc -std=c17 -g -Wall -c ListClient.c

ListTest : ListTest.o List.o
	gcc -std=c17 -Wall -o ListTest ListTest.o List.o

ListTest.o : ListTest.c List.h
	gcc -std=c17 -Wall -c ListTest.c

List.o : List.c List.h
	gcc -std=c17 -g -Wall -c List.c

clean :
	rm -f Lex ListClient Lex.o ListClient.o List.o *.txt ListTest.o ListTest ListTest

checkClient : 
	valgrind --leak-check=full ListTest

checkLex :
	valgrind --leak-check=full Lex in3 blah3

