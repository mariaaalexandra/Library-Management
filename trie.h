/*DRUGA MARIA-ALEXANDRA 313CB*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SIZE 68

//structura arbore
typedef struct t {
    struct t **kids;
    int is_end;
    void *info;
} *Trie, tree;

//inserare
void insert(Trie t, char *key, void *info);

//afla pozitie
int poz(char c);

//afla caracter
char character(int poz);

//cauta 
void *search(Trie t, char *string);

//aloca nod
Trie new_node();

//functie eliberare
typedef void (*TFree)(void *);

//functie stergere
int remove_book(Trie t, char *key, TFree f);

//verifica daca mai are copii
int empty(Trie t);

void free_tree(Trie t, TFree f);

void free_author(Trie t, TFree f);