JerryBoree:JerryBoreeMain.o MultiValueHashTable.o KeyValuePair.o HashTable.o LinkedList.o Jerry.o
	gcc JerryBoreeMain.o MultiValueHashTable.o KeyValuePair.o HashTable.o LinkedList.o Jerry.o -o JerryBoree

MultiValueHashTable.o:MultiValueHashTable.c MultiValueHashTable.h Defs.h HashTable.h LinkedList.h KeyValuePair.h
	gcc -c MultiValueHashTable.c

KeyValuePair.o:KeyValuePair.c KeyValuePair.h Defs.h 
	gcc -c KeyValuePair.c

HashTable.o:HashTable.c HashTable.h Defs.h LinkedList.h KeyValuePair.h
	gcc -c HashTable.c

LinkedList.o:LinkedList.c LinkedList.h Defs.h
	gcc -c LinkedList.c

Jerry.o:Jerry.c Jerry.h Defs.h
	gcc -c Jerry.c
	
JerryBoreeMain.o:JerryBoreeMain.c Jerry.h Defs.h LinkedList.h HashTable.h MultiValueHashTable.h KeyValuePair.h
	gcc -c JerryBoreeMain.c
	
clean:
	rm -f *.o 
