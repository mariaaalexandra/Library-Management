/*DRUGA MARIA-ALEXANDRA 313CB*/
#include "header.h"

//seteaza campurile lui el cu cele din info
book* aloc_book(char *line);

//elibereaza structura
void free_struct(void * el);

//insereaza in arborele T1
void add_book1(Trie T1, void *info);

//insereaza in arborele T2
void add_book2(Trie T2, void *info);

//afiseaza structura carte
void af_struct(void *info, FILE *fi);

//afiseaza lista cartilor
void print(Trie T, FILE *fi);

//returneaza arbore cu prefix
Trie book_prefix(Trie T, char *prefix);

//afiseaza cartile cu prefix
void af_book_prefix(Trie T, int *contor, TAfi f, FILE *fi);

//afiseaza autorii cu prefix
void af_author_prefix(Trie T, char *str, int *contor, FILE *fi);