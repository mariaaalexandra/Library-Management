/*DRUGA MARIA-ALEXANDRA 313CB*/
#include "trie.h"

//structura carte
typedef struct b
{
    char *title;
    char *author;
    int rating;
    int nr_pg;
}book;

//functie afisare
typedef void (*TAfi)(void *, FILE *);
