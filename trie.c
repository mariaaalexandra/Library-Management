/*DRUGA MARIA-ALEXANDRA 313CB*/
#include "trie.h"

//lungime maxima 
#define SIZE 68

//initializeaza nod nou
Trie new_node()
{
    Trie new = NULL;
    new = (Trie)calloc(1, sizeof(tree));

    if (new == NULL) {
        printf("EROARE ALOCARE NOD\n");
        exit(-1);
    }

    new->kids = calloc(SIZE, sizeof(tree));
    if (new->kids == NULL) {
        printf("EROARE ALOCARE COPII\n");
        exit(-2);
    }

    new->is_end = 0;    

    return new; 
}

//afla pozitie
int poz(char c)
{
    int p;
    if (c >= 'a' && c <= 'z') {
        p = c - 'a'; 
    }
    else if (c >= 'A' && c <= 'Z') {
        p = 26 + c - 'A';
    }
    else if (c >= '0' && c <= '9') {
        p = 52 + c - '0';
    }
    else {
        if (c == '.') {
            p = 62;
        }
        else if (c == '-') {
            p = 63;
        }
        else if (c == '\'') {
            p = 64;
        }
        else if (c == '?') {
            p = 65;
        }
        else if (c == '!') {
            p = 66;
        }
        else {
            p = 67;
        }
    }
    return  p;
}

//afla caracter
char character(int poz)
{
    char c = 0;
    if (poz >= 0 && poz <= 25) {
        c = poz + 'a';
    }
    else if (poz >= 26 && poz <= 51) {
        c = poz + 'A' - 26;
    }
    else if (poz >= 52 && poz <= 61) {
        c =  poz + '0' - 52;
    }
    else {
        if (poz == 62) {
            c = '.';
        }
        else if (poz == 63) {
            c = '-';
        }
        else if (poz == 64) {
            c = '\'';
        }
        else if (poz == 65) {
            c = '?';
        }
        else if (poz == 66) {
            c = '!';
        }
        else {
            c = ' ';
        }
    }
    return c;
}

//insereaza
void insert(Trie t, char *key, void *info)
{
    if (strlen(key) == 0) {
        t->is_end = 1;
        t->info = info;
        return;
    }

    Trie next = t->kids[poz(key[0])];
    if (!next) {
        t->kids[poz(key[0])] = new_node();
        next = t->kids[poz(key[0])];
    }
    insert(next, key + 1, info);
}

//cauta 
void *search(Trie t, char *string)
{
    if (strlen(string) == 0) {
        if (t->is_end == 1) {
            return t->info;
        }
    }

    Trie next = t->kids[poz(*string)];
    if (!next) {
        return NULL;
    }
    return search(next, string + 1); 
}

/*verifica daca are copii sau nu
1 = nu are copii, 0 = are copii*/
int empty(Trie t)
{
    int i;
    for (i = 0; i < SIZE; i++) {
        if (t->kids[i]) {
            return 0;
        }
    }
    return 1;
}

//elibereaza copac T1
void free_tree(Trie t, TFree f)
{
    int i;
    for (i = 0; i < SIZE; i++) {
        if (t->kids[i]) free_tree(t->kids[i], f);
    }

    free(t->kids);
    if (f && t->info) f(t->info);
    free(t);
}

//elibereaza copac T2
void free_author(Trie t, TFree f)
{
    int i;
    for (i = 0; i < SIZE; i++) {
        if (t->kids[i]) free_author(t->kids[i], f);
    }
    if (t->info) {
        free_tree(t->info, f);
    }
    free(t->kids);
    free(t);
}

//functie stergere de carte (operatia delete)
int remove_book(Trie t, char *key, TFree f)
{
    //se verifica daca cheia s-a terminat
    if (strlen(key) == 0) {
        //daca exista inforamtia se elibereaza
        if (t->info) {
            if (f) {
                f(t->info);
            }
            t->info = NULL;
        }
        return empty(t);
    }

    Trie next = t->kids[poz(*key)];

    /*daca arborele urmator nu este NULL si functia returneaza 1, 
    se elibereaza copacul next, se seteaza NULL*/
    if (next != NULL && remove_book(next, key + 1, f) == 1) {
        free_tree(next, f);
        t->kids[poz(*key)] = NULL;
        if (t->info == NULL && empty(t) == 1) {
            return 1;
        }
    }

    return 0;
}