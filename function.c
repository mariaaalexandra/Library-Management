/*DRUGA MARIA-ALEXANDRA 313CB*/
#include "function.h"

//seteaza campurile lui el cu cele din info
book* aloc_book(char *line)
{
    /*aloc structura si fiecare camp din aceasta
    setez campurile cu datele citite */
    book *element = (book *)calloc(1, sizeof(book));
    if (element == NULL) {
        printf("EROARE DE ALOCARE\n");
        exit(-4);
    }

    element->title = (char *)calloc(51, sizeof(char));
    if (element->title == NULL) {
        printf("EROARE DE ALOCARE\n");
        exit(-4);
    }
    strcpy(element->title, strtok(line, ":\n"));

    element->author = (char *)calloc(41, sizeof(char));
    if (element->author == NULL) {
        printf("EROARE DE ALOCARE\n");
        exit(-4);
    }
    strcpy(element->author, strtok(NULL, ":\n"));

    element->rating = atoi(strtok(NULL, ":\n"));
    element->nr_pg = atoi(strtok(NULL, ":\n"));
    
    return element;
}

//elibereaza structura
void free_struct(void * el)
{
    book *element = (book *)el;
    free(element->title);
    free(element->author);
    free(element);
}

//insereaza in arborele T1
void add_book1(Trie T1, void *info)
{
    insert(T1, ((book *)info)->title, info);
}

//insereaza in arborele T2
void add_book2(Trie T2, void *info)
{
    //verific daca autorul exista deja in arbore
    Trie tree = search(T2, ((book *)info)->author);

    //daca nu exista deja, se creeaza 
    if (tree == NULL) {
        Trie new = new_node();
        //introduc titlul cartii si autorul
        insert(new, ((book *)info)->title, info);
        insert(T2, ((book *)info)->author, (void *)new);
    }
    else {
        insert(tree, ((book *)info)->title, info);
    }

}

//afiseaza titlu carte
void af_struct(void *info, FILE *fi)
{
    book *element = (book *)info;
    fprintf(fi, "%s\n", element->title);
}

//afiseaza lista cartilor
void print(Trie T, FILE *fi)
{
    //sunt printate titlurile de carte in fisierul fi
    if (T == NULL) {
        return;
    }

    if (T->info) {
        af_struct(T->info, fi);
    }

    int i;
    for (i = 0; i < SIZE; i++) {
        print(T->kids[i], fi);
    }
}

//returneaza arbore cu prefix
Trie book_prefix(Trie T, char *prefix)
{
    //daca prefixul se termina, este returnat arborele
    if (strlen(prefix) == 0) {
        return T;
    }

    Trie next = T->kids[poz(*prefix)];
    if (!next) {
        return NULL;
    }
    return book_prefix(next, prefix + 1);
}

//afiseaza cartile cu prefix
void af_book_prefix(Trie T, int *contor, TAfi f, FILE *fi)
{
    if (*contor == 3) {
        return;
    } 
   
   //daca exista informatia, este afisata si creste contor
    if (T->info) {
        f(T->info, fi);
        (*contor)++;
    }
   
    int i;
    //se reapeleaza functia pentru fiecare dintre copii
    for (i = 0; i < SIZE; i++) {
        if (T->kids[i]) {
            af_book_prefix(T->kids[i], contor, f, fi);
        }
    }
}

//afiseaza autorii cu prefix
void af_author_prefix(Trie T, char *str, int *contor, FILE *fi)
{
    if (*contor == 3) {
        return;
    }
    
    //daca exista informatia, se afiseaza string, iar contor creste
    if (T->info) {
        fprintf(fi, "%s\n", str);
        (*contor)++;
    }
    
    int i;

    //se reapeleaza functia pentru fiecare din copii
    for (i = 0; i < SIZE; i++) {
        if (T->kids[i]) {
            int len = strlen(str);
            str[len] = character(i);
            af_author_prefix(T->kids[i], str, contor, fi);
            str[len] = '\0';
        }
    }
}
