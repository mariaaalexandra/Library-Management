DRUGA MARIA-ALEXANDRA
313 CB

TEMA 3 SD

Fisier trie.c - functii:
    ->new_node:
        -creeaza un nou nod
        -aloca vectorul de copii
        -seteaza sfarsitul cu 0
        -functia returneaza nodul creat
    ->poz:
        -determina pozitia caracterului dat ca parametru
        -verifica in ce interval se afla caracterul si astfel
        returneaza pozitia
    ->character:
        -determina caracterul de pe o pozitie data ca parametru
        -verifica in ce interval numeric se afla pozitia si astfel
        returneaza caracterul
    ->insert:
        -insereaza key in arbore
        -conditia de iesire din recursivitate este ca key sa se ter-
        mine, caz in care se seteaza sfarsitul cu 1 si se seteaza si 
        informatia
        -variabila, de tip Trie, next retine nodul copilului din arbore, 
        daca acesta este NULL, se creeaza un nou nod
        -se reapeleaza functia cu parametrul key + 1
    ->search:
        -cauta string in arbore
        -conditia de iesire din arbore este ca string sa ajunga la final
        si sa fie setat cu 1 campul is_end
        -varibila, de tip Trie, next retine nodul copilului din arbore, daca
        acesta este NULL, se returneaza NULL
        -se reapeleaza functia cu parametrul string + 1
    ->empty:
        -verifica daca arborele are copii sau nu
        -intoarce 1, daca nu are copii si 0, altfel
    ->free_tree:
        -elibereaza arbore T1
        -se parcurg copii si se elibereaza, apoi se da free si la vectorul de
        copii
        -se elibereaza informatia cu functia specificata ca parametru
        -se elibereaza copacul
    ->free_author:
        -elibereaza arbore T2
        -se parcurg copii si se elibereaza, apoi se da free si la vectorul de
        copii
        -se elibereaza informatia cu functia specificata ca parametru
        -se elibereaza copacul
    ->remove_book:
        -functie de stergere
        -se verifica daca cheia s-a terminat
        -daca exista inforamtia se elibereaza
        -se reapeleaza functia recursivitate
        -daca arborele urmator nu este NULL si functia returneaza 1, se elibereaza
        copacul next, se seteaza NULL
        -daca informatia nu exista si rezultatul functiei empty este 1, se va returna 1

Fisier tema3.c - functii:
    ->main:
        -deschid fisierele de citire si afisare
        -verific la ce tip de comanda ma aflu si apelez functiile corespunzatoare
        -eliberez memoria
        -inchid fisierele de citire si afisare

Fisier function.c - functii:
    ->functia aloc_book:
        -aloca o structura de tip book si fiecare camp din  aceasta
        -seteaza campurile structurii cu informatiile citite
        -returneaza structura de tip carte alocata
    ->functia free_struct:
        -elibereaza structura de tip carte
        -apelez functia free pentru campurile titlu si autor, apoi
        pentru structura
    ->add_book1:
        -insereaza in arborele de tip T1
    ->add_book2:
        -insereaza in arborele de tip T2
        -se verifica daca autorul exista deja in arbore, daca nu exista se aloca
        un nou nod si se insereaza in el titlul, apoi in arborele de tip T2 inserez 
        autorul; daca autorul exista deja, atunci inserez titlul in arborele returnat
        de functia search.
    ->functia auxiliara af_struct:
        -afiseaza titlul cartii in fisierul specificat ca parametru
    ->functia print:
        -printeaza titluri de carte in fisierul specificat ca parametru
    ->functia book_prefix:
        -returneaza o variabila de tip Trie
        -cauta daca prefix se gaseste in arbore si returneaza arborele de prefix
    ->functia af_book_prefix:
        -afiseaza in ordine lexicografica primele 3 carti din arborele cu prefix
        -cand variabila contor depaseste 3 atunci functia se incheie
        -daca exista informatie, atunci se va afisa titlul si contorul se incrementeaza
        -sunt parcursi toti copii si se reapeleaza functia pentru fiecare
    ->funcita af_author_prefix:
        -afiseaza in ordine lexicografica primii 3 autori din arborele cu prefix
        -cand variabila contor depaseste 3 atunci functia se inchie 
        -daca exista informatie, atunci se va afisa autorul si contorul se incrementeaza
        -sunt parcursi toti copii si se reapeleaza functia pentru fiecare

~CODURI DE EROARE~
    ->(-1) = EROARE ALOCARE NOD
    ->(-2) = EROARE ALOCARE COPII
    ->(-3) = EROARE DESCHIDERE FISIER
    ->(-4) = EROARE ALOCARE