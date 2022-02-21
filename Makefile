build: 
	gcc -g -Wall -o tema3 tema3.c trie.c function.c

.PHONY : clean
clean :
	rm -f tema3 *~