all: trie.o tnine.o t9
trie.o: trie.c trienode.h
	gcc -Wall -std=c11 -c trie.c -o trie.o
tnine.o: tnine.c trienode.h
	gcc -Wall -std=c11 -c tnine.c -o tnine.o
t9: tnine.c trie.c 
	gcc -Wall -std=c11 trie.o tnine.o -o t9
clean:
	rm -f *.o t9
