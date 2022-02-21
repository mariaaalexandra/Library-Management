/*DRUGA MARIA-ALEXANDRA 313CB*/
#include "function.h"

int main(int argc, char *argv[])
{
    FILE *fp, *gp;

    //deschid fisierele de citire si afisare
    fp = fopen(argv[1], "rt");
    if (fp == NULL) {
        printf("EROARE DESCHIDERE FISIER\n");
        exit(-3);
    }
    
    gp = fopen(argv[2], "wt");
    if (gp == NULL) {
        printf("EROARE DESCHIDERE FISIER\n");
        exit(-3);
    }

    char *line = calloc(150, sizeof(char));
    if (line == NULL) {
        printf("EROARE ALOCARE\n");
        exit(-4);
    }
    
    //cele doua tipuri de arbori
    Trie T1, T2;
    T1 = new_node();
    T2 = new_node();
    char *command = calloc(30, sizeof(char));
    while (fgets(line, 150, fp) != NULL) {
        sscanf(line, "%s", command);
        int read_ch = strlen(command) + 1;
        
        //verific comanda la care ma aflu
        if (!command) {
            break;
        }

        if (strcmp(command, "add_book") == 0) {
            book *b = aloc_book(line + read_ch);
            if (search(T1, b->title)) {
                free_struct(b);
                continue;
            }
            add_book1(T1, (void *)b);
            add_book2(T2, (void *)b);
        }

        else if (strcmp(command, "search_book") == 0) {
            char *title = (char *)calloc(51, sizeof(char));
            if (title == NULL) {
                printf("EROARE ALOCARE\n");
                exit(-3);
            }
            strcpy(title, strtok(line + read_ch, "\n"));
        
            //search fara prefix
            if (strchr(title, '~') == NULL) {
                title = strtok(title, "~\n");
                
                //cauta titlu in arborele T1
                void *p = search(T1, title);
                if (p == NULL) {
                    fprintf(gp, 
                    "Cartea %s nu exista in recomandarile tale.\n", 
                    title);
                }
                else {
                    fprintf(gp, "Informatii recomandare: %s, %s, %d, %d\n", 
                    ((book *)p)->title, ((book *)p)->author, 
                    ((book *)p)->rating, ((book *)p)->nr_pg);
                }
            }

            //search cu prefix
            else {
                char *prefix = (char *)calloc(51, sizeof(char));
                if (title == NULL) {
                    printf("EROARE ALOCARE\n");
                    exit(-3);
                }

                strcpy(prefix, strtok(title, "~"));

                //cauta prefix in arborele T1
                Trie pref = book_prefix(T1, prefix);

                //contorizez numarul cartilor
                int contor = 0;
                if (pref == NULL) {
                    fprintf(gp, "Nicio carte gasita.\n");
                }
                else {
                    /*apelez functia de afisare a primelor
                    3 carti cu prefixul specificat*/
                    af_book_prefix(pref, &contor, af_struct, gp);
                }
                free(prefix);
            }
            free(title);
        }

        else if (strcmp(command, "list_author") == 0) {
            char *author = (char *)calloc(41, sizeof(char));
            if (author == NULL) {
                printf("EROARE ALOCARE\n");
                exit(-3);
            }
            strcpy(author, strtok(line + read_ch, "\n"));

            //caut autor in arborele T2
            void *p = search(T2, author);
            
            //list fara prefix 
            if (strchr(author, '~') == NULL) {
                if (p == NULL) {
                    fprintf(gp,
                    "Autorul %s nu face parte din recomandarile tale.\n",
                    author);
                }
                else {
                    //printeaza titluri de carte in fisierul specificat ca parametru
                    print((Trie)p, gp);
                }
            }

            //list cu prefix
            else {
                char *prefix = (char *)calloc(41, sizeof(char));
                if (prefix == NULL) {
                    printf("EROARE ALOCARE\n");
                    exit(-3);
                }
                strcpy(prefix, strtok(author, "~"));

                //caut autor in arborele T2
                Trie tree = book_prefix(T2, author);
                int contor = 0;
                if (tree == NULL) {
                    fprintf(gp, "Niciun autor gasit.\n");
                }
                else {
                    /*apelez functia de afisare a primelor
                    3 carti cu prefixul specificat*/
                    af_author_prefix(tree, prefix, &contor, gp);
                }
                free(prefix);
            }
            free(author);
        }

        else if (strcmp(command, "search_by_author") == 0) {

            //e prefix a:t~ sau a~
            if (strchr(line + read_ch, '~') != NULL) {
                char *author = (char *)calloc(41, sizeof(char));
                if (author == NULL) {
                    printf("EROARE ALOCARE\n");
                    exit(-3);
                }
                 
                if (strchr(line + read_ch, ':') != NULL) {
                    strcpy(author, strtok(line + read_ch, ":\n"));
                    read_ch = read_ch + strlen(author) + 1;
                    char *title = (char *)calloc(51, sizeof(char));
                    if (author == NULL) {
                        printf("EROARE ALOCARE\n");
                        exit(-3);
                    }
                    strcpy(title, strtok(line + read_ch, "~\n"));
                    
                    //caut autor in T2
                    Trie tree = search(T2, author);
                    
                    if (tree == NULL) {
                        fprintf(gp, 
                        "Autorul %s nu face parte din recomandarile tale.\n",
                        author);
                    }

                    else {
                        //caut titlu in arborele returnat
                        Trie p = book_prefix(tree, title);
                        if (p == NULL) {
                            fprintf(gp, "Nicio carte gasita.\n");
                        }

                        else {
                             /*apelez functia de afisare a primelor
                            3 carti cu prefixul specificat*/
                            int contor = 0;
                            af_book_prefix(p, &contor, af_struct, gp);
                        }

                    }
                    free(title);
                }
                else {
                    strcpy(author, strtok(line + read_ch, "~\n"));

                    //caut autor in T2
                    Trie tree = book_prefix(T2, author);
                    int contor = 0;
                    if (tree == NULL) {
                        fprintf(gp, "Niciun autor gasit.\n");
                    }
                    else {
                         /*apelez functia de afisare a primelor
                        3 autori cu prefixul specificat*/
                        af_author_prefix(tree, author, &contor, gp);
                    }
                }
                free(author);
            }
            //e a:t
            else {
                char *author = (char *)calloc(41, sizeof(char));
                if (author == NULL) {
                    printf("EROARE ALOCARE\n");
                    exit(-3);
                }
                strcpy(author, strtok(line + read_ch, ":\n"));
                read_ch = read_ch + strlen(author) + 1;

                char *title = (char *)calloc(51, sizeof(char));
                if (title == NULL) {
                    printf("EROARE ALOCARE\n");
                    exit(-3);
                }
                strcpy(title, strtok(line + read_ch, "\n"));

                //caut autor in T2
                void *p = search(T2, author);
                if (p == NULL) {
                    fprintf(gp, 
                    "Autorul %s nu face parte din recomandarile tale.\n", 
                    author);
                }
                else {
                    //caut titlu in arborele returnat
                    void *b = search(p, title);
                    if (b == NULL) {
                        fprintf(gp, 
                        "Cartea %s nu exista in recomandarile tale.\n", 
                        title);
                    }
                    else {
                        fprintf(gp, "Informatii recomandare: %s, %s, %d, %d\n",
                        ((book *)b)->title, ((book *)b)->author, 
                        ((book *)b)->rating, ((book *)b)->nr_pg);
                    }
                }
                free(author);
                free(title);
            }
        }

        else {
            char *title;
            title = strtok(line + read_ch, "\n");
            char *author;
            //cautat carte dupa titlu in T1 => autorul
            void *info = search(T1, title);
            if (info == NULL) {
                fprintf(gp,
                "Cartea %s nu exista in recomandarile tale.\n",
                title);
            }
            else {
                author = ((book *)info)->author;

                //cautat arborele de autor in T2
                Trie tree = search(T2, author);

                //din acel arbore, se da remove pe titlu
                remove_book(tree, title, NULL);

                //daca ramane NULL (isEmpty) , se va sterge si autorul din T2
                if (empty(tree) == 1) {
                    free_tree(tree, NULL);
                    remove_book(T2, author, NULL);
                }
                remove_book(T1, title, free_struct);
            }
        }
        
    }

    free_tree(T1, free_struct);
    free_author(T2, NULL);
    free(line);
    free(command);
    fclose(fp);
    fclose(gp);

    return 0;
}