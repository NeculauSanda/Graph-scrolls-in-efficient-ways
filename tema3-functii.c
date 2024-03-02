/*NECULAU SANDA-ELENA GRUPA 313CB*/
#include "tema3.h"

TGL* AlocG(int nr) 
{
    TGL* g = (TGL*)malloc(sizeof(TGL));
    if (!g) {
        return NULL;
    }
     /*nu folosim nodul de pe pozitia 0*/
    g->x = (AArc*)calloc((nr+1), sizeof(AArc));
    if(!g->x) { 
        free(g); return NULL; 
    }
    g->n = nr;
    return g;
}

TGL* CitireG(FILE *in, char ***tlista_nume) {
    TGL *G;
    AArc *p, *p1, aux, aux2;
    int nr_nod = 0, nr_arce = 0, cost = 0, i = 0, j =0,k =0, crt = 0;
    char nume1[50] = {0}, nume2[50] = {0};

    fscanf(in, "%d %d\n", &nr_nod, &nr_arce);
    printf("%d %d\n", nr_nod, nr_arce);   ///-----------

    /*alocam memorie pentru vectorul de nume acesta va retine 
    numele nodurilor*/
    *tlista_nume = (char **) calloc((nr_nod +1), sizeof(char*));
    if(!(*tlista_nume)) {
        return 0;
    }

    for (i = 0; i < nr_nod + 1; i++) {
        (*tlista_nume)[i] = (char*) calloc(50, sizeof(char));
        /*eliberare*/
        if(!((*tlista_nume)[i])) {
            for (j = 0; j <= i; j++) {
                free((*tlista_nume)[i]);
            }
            free(*tlista_nume);
            return 0;
        }
    }

    /*initializam vectorul de nume cu un indice pentru a stii
    daca a fost actualizat sau nu*/
    for (i = 0; i < nr_nod + 1; i++) {
        strcpy((*tlista_nume)[i], "gol");
    }
    /* Alocam graful + lista de adiacenta pt fiecare nod*/
    G = AlocG(nr_nod);
    if (!G) {
        return 0;
    }

    /*citim fiecare pereche de arce*/
    for(i = 1 ;i <= nr_arce + 1; i++)   {
        fscanf(in, "%s %s %d\n", nume1, nume2, &cost);
        /*ne folosim de lista de nume pt a afla la ce idex este numele
        sursei pentru a pute adauga nod in lista lui de adiacenta*/
        for (j = 1; j <= nr_nod; j++) {
            if((strcmp((*tlista_nume)[j], "gol") == 0)) {
                strcpy((*tlista_nume)[j], nume1);
                crt = j;
                break;
            } else if (strcmp((*tlista_nume)[j], nume1) == 0) {
                crt = j;
                break;
            }
        }

        /*primeste lista de adiacenta*/
        p = G->x + crt;
        
        /*parcurgem lista pana la final*/
        while(*p ) {
            p = &(*p)->urm;
        }
        /*alocam nodul*/
        aux = (TCelArc*) calloc(1,sizeof(TCelArc));
        if(!aux) {
            DistrugereGraf(&G);
            return 0;
        }
        aux->urm = *p;
        *p = aux;
        strcpy(aux->d,nume2);
        aux->c = cost;

        /*creeam/actualizam lista de adiacenta si pentru cel de al 
        doilea nod ca sa avem graf neorientat*/
        for(k = 1; k <= nr_nod ; k++ )
        {            
            if (strcmp((*tlista_nume)[k], nume2) == 0)
            {
                break;
            } else if((strcmp((*tlista_nume)[k], "gol") == 0)) {
                strcpy((*tlista_nume)[k], nume2);
                break;
            }
        }

        p1 = G->x + k;
        while(*p1) {
            p1 = &(*p1)->urm;
        }
            aux2 = (TCelArc*) calloc(1,sizeof(TCelArc));
            if(!aux2) {
                DistrugereGraf(&G);
                return 0;
            }
            aux2->urm = *p1;
            *p1 = aux2;
            strcpy(aux2->d, (*tlista_nume)[crt]);
            aux2->c = cost;
    }

    fclose(in);
    return G;
}

/*citire cerinta 2
tlista_nume = vectorul cu denumirile nodurilor, greutate = vectorul 
cu greutati pentru fiecare nod*/
TGL* CitireG_2(FILE *in, char ***tlista_nume, int **greutate, int *greutate_comoara) {
    TGL *G;
    AArc *p, aux;

    /*nr_nod = numar de noduri, nr_arce = numar arce, crt = indexul pozitiei
     nodului in vectorul de nume, kg = numarul de kilograme*/
    int nr_nod = 0, nr_arce = 0, cost = 0, i = 0, j = 0, k = 0, crt = 0, kg = 0;
    char nume1[50] = {0}, nume2[50] = {0};

    /*citire prima linie*/
    fscanf(in, "%d %d\n", &nr_nod, &nr_arce);

    /*alocam memorie pentru vectorul de nume acesta va retine 
    numele nodurilor in ordinea in care se citesc*/
    *tlista_nume = (char **) calloc((nr_nod +1), sizeof(char*));
    if(!(*tlista_nume)) {
        return 0;
    }
    for (i = 0; i < nr_nod + 1; i++) {
        (*tlista_nume)[i] = (char*) calloc(50, sizeof(char));
        /*eliberare*/
        if(!((*tlista_nume)[i])) {
            for (j = 0; j <= i; j++) {
                free((*tlista_nume)[i]);
            }
            free(*tlista_nume);
            return 0;
        }
    }

    /*initializam vectorul de nume cu un indice pentru a stii
    daca a fost actualizat sau nu*/
    for (i = 0; i < nr_nod + 1; i++) {
        strcpy((*tlista_nume)[i], "gol");
    }

    G = AlocG(nr_nod); /* Alocam graful + lista de adiacenta pt fiecare nod*/
    if (!G) {
        return 0;
    }

    /*alocam vectorul de greutate*/
    *greutate = (int *) calloc(nr_nod + 1, sizeof(int));

    /*pentru fiecare pereche de arce*/
    for(i = 1 ;i <= nr_arce; i++)   {
        fscanf(in, "%s %s %d\n", nume1, nume2, &cost);
        /*ne folosim de lista de nume pt a afla la ce idex este respectivul 
        nume pentru a adauga urmatorul nod in lista de adiacenta a sursei*/
        for (j = 1; j <= nr_nod; j++) {

            if(strcmp((*tlista_nume)[j], "gol") == 0) {
                /*adaugam numele nodului din care pleaca arcul*/
                strcpy((*tlista_nume)[j], nume1);
                crt = j;
                /*adaugam si numele nodurile in care intra arcul*/
                for (k = 1; k <= nr_nod; k++) {
                    if(strcmp((*tlista_nume)[k], nume2) != 0 && 
                            strcmp((*tlista_nume)[k], "gol") == 0) 
                    {
                        strcpy((*tlista_nume)[k], nume2);
                        break;

                    } else if(strcmp((*tlista_nume)[k], nume2) == 0) {
                        break;
                    }
                }
                break;

            } else if (strcmp((*tlista_nume)[j], nume1) == 0) {

                crt = j;
                for (k = 1; k <= nr_nod; k++) {
                    if(strcmp((*tlista_nume)[k], nume2) != 0 &&  
                            strcmp((*tlista_nume)[k], "gol") == 0) 
                    {
                        strcpy((*tlista_nume)[k], nume2);
                        break;

                    } else if(strcmp((*tlista_nume)[k], nume2) == 0) {
                        break;
                    }
                }
                break;
            }
        }

        /*luam lista de adiacenta pentru nodul de unde plecam*/
        p = G->x + crt;
        
        /*parcurgem lista pana la final*/
        while(*p ) {
            p = &(*p)->urm;
        }
        /*alocam nodul*/
        aux = (TCelArc*) calloc(1,sizeof(TCelArc));
        if(!aux) {
            DistrugereGraf(&G);
            return 0;
        }
        // va primi NULL
        aux->urm = *p;
        *p = aux;
        strcpy(aux->d,nume2);
        aux->c = cost;
    }

    /*citim greutatea pentru fiecare nod*/ 
    for(i = 1; i <= nr_nod ; i++) {

        fscanf(in, "%s %d\n", nume1, &kg);
        for(j = 1; j <= nr_nod; j++) {

            if(strcmp((*tlista_nume)[j], nume1) == 0) {
                break;
            }
        }

        (*greutate)[j] = kg;
    }
    
    /*citim greutate comoara*/
    fscanf(in, "%d", &(*greutate_comoara));

    fclose(in);
    return G;
}

void DistrugereGraf(TGL **G) {
    int i = 0;
    AArc p, aux;
    for (i = 1; i <= (*G)->n; i++) {
        p = (*G)->x[i];
        while(p) {
            aux = p;
            p = p->urm;
            free(aux);
        }
    }
    free((*G)->x);
    free(*G);
    *G=NULL;
}

/*folosita pentru verificare citire*/
void AfisareGraf(TGL *G) {
    AArc L ;
    int i = 0;

    for(i = 1; i <= G->n; i++) {
        L = G->x[i];
        if(!L) {
            printf("%d: - \n", i);
        } else {
            printf("%d: ", i);
        }
        for( ; L != NULL; L = L->urm)
            printf("%s (%d)", L->d, L->c);
        printf("\n");
    }
}

/*G = graful, index = nodul de la care parcurgem, visited = vectorul 
de noduri vizitate, tlista_nume = vectorul de nume*/ 
void DFS(TGL *G, int index, int * visited, char **tlista_nume) {

    
    AArc p;
    int i = 0;

    p = G->x[index];
    /*marcam nodul vizitat*/
    visited[index] = 1;
    for ( ; p != NULL; p = p->urm) {

        int index_aux = 0;
        /*cautam in vectorul de nume destinatia si intoarcem idexul*/ 
        for(i = 1; i <= G->n; i++) {
            if(strcmp(tlista_nume[i],p->d) == 0) {
                break;
            }
        }
        index_aux = i;
        if(visited[index_aux] == 0) {

            DFS(G, index_aux, visited, tlista_nume);

        }
    }
}

int Nr_componente_conexe(TGL *G, char **tlista_nume) {
    int *visited = (int *) calloc((G->n + 1), sizeof(int));
    int nr_comp = 0, i = 0;

    /*parcurgem vectorul vizitat pana cand marcam toate nodurile*/
    for(i = 1; i <= G->n; i++) {

        /*daca s-a gasit un nod nevizitat atunci am gasit o compoenta
        conexa si parcurgem graful folosind DFS pt a marca restul 
        nodurilor in vectorul vizitat*/
        if(visited[i] == 0) {
            DFS(G, i, visited, tlista_nume);
            nr_comp++;
        }

    }
    free(visited);
    return nr_comp;
}

/*functia va returna nodul care are scorul minim,
visited = vectorul in care vedem daca nodul e vizitat
n = numarul de noduri, scor = vectorul cu scorurile minime */
int scor_min(int *visited, int n, float *scor) {
    float min = FLT_MAX;
    int i_nod = 0, i = 0;
    for(i = 1; i <= n ; i ++) {
        if(visited[i] == 0 && scor[i] < min) {
            min = scor[i];
            i_nod = i;
        }
    }
    return i_nod;
}

/*returneaza distanta minima, dar este modificat
special pentru cerinta 1*/
int MIN(int *visited, int n, int *distance) {
    int min = INT_MAX;
    int i_nod = 0, i = 0;
    for(i = 1; i <= n ; i ++) {
        if(visited[i] == 1 && distance[i] < min) {
            min = distance[i];
            i_nod = i;
        }
    }
    return i_nod;
}

/*sursa = nodul de plecare, tlista_nume = vectorul cu denumirile nodului,
distanta = vectorul de distante ce va fi actualizat, greutate = vectorul cu 
greutatile nodurilor path = vector ce va retine drumul, scor = vector care 
retine scorul minim*/
void DIJKSTRA(TGL *G, int sursa, char **tlista_nume, int **distanta, 
                            int*greutate, char ***path, float **scor) {
    /*alocam vectorul de vizite si de distanta*/
    int *visited = (int *)calloc((*G).n + 1, sizeof(int));

    int i = 0, j = 0;
    /*initializam vectorul de scor cu valori mari*/
    for (i = 0; i <= G->n; i++) {
        (*scor)[i] = FLT_MAX;
    }

    int nod = 0;
    AArc p;  /*va primi lista de adiacenta pentru fiecare nod*/
    (*scor)[sursa] = 0;  /*marcam distanta nodului de pornire cu 0*/
    for (i = 1; i <= G->n; i++) {
        /*primi nodul cu distanta minima*/
        nod = scor_min(visited, G->n, *scor);
        visited[nod] = 1;
        p = G->x[nod];

        for ( ; p != NULL; p = p->urm) {
            /*determinam indexul destinatiei*/
            int i_destinatie = 0; 
            for(j = 1; j <= G->n; j++) {
                if(strcmp(tlista_nume[j],p->d) == 0) {
                    break;
                }
            }

            i_destinatie = j;
            /*determinam scorul pe arcul respectiv*/
            float scor_deter = 0;
            scor_deter = (float)p->c/greutate[j];  
            if(visited[i_destinatie] == 0 && 
                    (*scor)[nod] + scor_deter < (*scor)[i_destinatie]) 
            {
                /*actualizam vectorul de scor*/
                (*scor)[i_destinatie] = scor_deter + (*scor)[nod];
                /*calculam vectorul de distante minime de la insula la celelalte noduri*/
                (*distanta)[i_destinatie] = p->c + (*distanta)[nod];
                /*copiem in vectorul care contine traseul nodul*/
                strcpy((*path)[i_destinatie], tlista_nume[nod]);
            }
        }
    }
    free(visited);
}

/* functia va afisa in fisier drumul si va determina greutatea minima
greutate_min = va retine greutatea minima pe parcusul drumui, */
int print_calea(TGL *G, char *start, char *end, char **path, 
                char**tlista_nume, FILE *out, int *greutate_min, int *greutate) 
{
    /*determinam indexul pentru nodul final = "CORABIE"*/
    int i = 0;
    for( i = 0 ; i <= G->n; i++) {
        if(strcmp(end,tlista_nume[i])== 0){
            break;
        }
    }

    if(strcmp(start, end) == 0) {

        fprintf(out,"%s ", start);

    } else if(strcmp(path[i],"gol") ==0) 
    {
        /*daca in drumul dinspre nodul de pornire spre cel final exista un gol
        atunci nu exista drum de la insula la corabie*/
        fprintf(out,"Echipajul nu poate transporta comoara inapoi la corabie\n");
        return 0;

    } else {

        print_calea(G,start,path[i],path, tlista_nume, out, greutate_min, greutate);
        /*afisam drumul in fisier*/
        fprintf(out, "%s ", tlista_nume[i]);
        /*cautam printre nodurile care fac parte din drum
        pe cel cu greutatea cea mai mica*/
        if(strcmp(tlista_nume[i], "Corabie") != 0 &&
            strcmp(tlista_nume[i], "Insula") != 0 && greutate[i] < *greutate_min)
        {
            *greutate_min = greutate[i];
        }
    }
    return 1;
    
}

/*greutate = vectorul care retine greutatile*/
void task2(TGL *G, char **tlista_nume, int grutate_comoara, int *greutate, FILE *out) {
    /*vectorul care retine scorul min*/
    float *scor = (float *)malloc(((*G).n + 1)* sizeof(float));
    int *distanta = (int*) calloc(G->n + 1, sizeof(int));
    /*path va arata calea pe unde trebuie sa mearga*/
    char **path = (char**) calloc((G->n + 1), sizeof(char*));

    /*ok va primi 1 daca nu exita drum de la corabie la insula
    ok2 va primi 0 daca nu exista drum de la insula la corabie
    sau 1 daca exista drumul de la insula la corabie*/
    int ok = 0, ok2 = 0;
    int i = 0, j = 0, k = 0, t = 0;

    /*retine greutatea minima pe parcusul drumului*/
    int greutate_minima = INT_MAX;

    /*initializam vectorul path*/
    for(i = 0; i <= G->n; i++) {
        path[i] = (char*)calloc(50, sizeof(char));
        if(!path[i]) {
            for(j = 0; j <= i; j++) {
                free(path[j]);
            }
            free(path);
            return ;
        }
        strcpy(path[i],"gol");
    }

    /*verificam mai intai daca exista drum de la corabie la insula*/
    for(t = 1; t <= G->n; t++) {
        if(strcmp(tlista_nume[t], "Corabie") == 0) {
            break;
        }
    }
    /*aplicam mai intai DIJKSTRA pentru drumul CORABIE - INSULA
    pentru a vedea daca exista drumul*/
    DIJKSTRA(G, t, tlista_nume, &distanta, greutate, &path, &scor);

    /*determinam indexul insulei*/
    for(i = 1; i <= G->n; i++) {
        if(strcmp(tlista_nume[i], "Insula") == 0) {
            break;
        }
    }

    /*nu exista drum la corabie la insula*/
    if(distanta[i] == 0) {
        fprintf(out, "Echipajul nu poate ajunge la insula\n");
        ok = 1;
    }

    /*reinitializam valorile pentru a determina valorile cerute*/
    greutate_minima = INT_MAX;
    for(j = 0; j <= G->n; j++) {
        strcpy(path[j], "gol");
        distanta[j] = 0;
    }

    /*exista drum de la CORABIE -> INSULA*/
    if(!ok) {

        DIJKSTRA(G, i, tlista_nume, &distanta, greutate, &path, &scor);
        /*afisam drumul si determinam greutatea minima daca ok2
        este 1 atunci putem continua de afisat valorile in fisier*/
        ok2 = print_calea(G,tlista_nume[i],tlista_nume[t], path,
                        tlista_nume, out, &greutate_minima, greutate);

        if (ok2 != 0) {
            
            int nr_drumuri = 0;
            nr_drumuri = grutate_comoara/greutate_minima;
            fprintf(out,"\n%d\n", distanta[t]);
            fprintf(out,"%d\n", greutate_minima);
            fprintf(out,"%d\n", nr_drumuri);
        }
    }
    
    /*eliberam memoria*/
    for (i = 0; i <= G->n; i++) {
        free(path[i]);
    }
    free(path);
    free(distanta);
    free(scor);
}


int *lunigime_min(TGL *G, char **tlista_nume, int comp) {
    int *visited = (int *) calloc((G->n + 1), sizeof(int));
    /*dis_min = vectorul care retine valoarea drumului min*/
    int *dis_min = (int*) calloc(comp, sizeof(int)); 
    /*distance = vectorul care retine cost min de la 
    un nod i la celelalte*/
    int *distance = (int*)malloc((G->n + 1) * sizeof(int)); 
    int i = 0, j = 0, k = 0, t = 0;
    int comp_aux = 0; /*indexul curent a componentei conexe*/
    int suma_comp = 0; /*valoare drumului min pe componenta*/

    int nod = 0;
    AArc p;
    
    for(i = 1; i <= G->n; i++) {
        /*cautam o componenta conexa folosindu-ne de DFS*/
        if(visited[i] == 0) {

            DFS(G, i, visited, tlista_nume);

            /*pentru a determina drumul minim ce trece prin toate 
            nodurile componentei conexe utilizam algoritmul PRIM*/
            for( j= 0; j <= G->n; j++) {
                distance[j] = INT_MAX;
            } 

            /* setam distanta de la nodul de la care pornim*/
            distance[i] = 0;
            suma_comp = 0;

            /*ALGORITM PRIM*/
            for(j = 1; j <= G->n; j ++) {

                nod = MIN(visited, G->n, distance);
                visited[nod] = 2; //il marcam
                p = G->x[nod];
                for( ; p != NULL; p = p->urm) {
                    // cautam denumirea
                    for(t = 1; t <= G->n; t++) {
                        if(strcmp(tlista_nume[t], p->d) == 0) {
                            break;
                        }
                    }
                    if(visited[t] == 1 && p->c < distance[t]) {
                        distance[t] = p->c;
                    }
                }
            }
            
            /*adunam costurile determinate*/
            for (k = 1 ; k <= G->n ; k ++) {
                if(distance[k] != INT_MAX) {
                    suma_comp = suma_comp + distance[k];
                }
            }
            /*introducem suma in vectorul de distante a componentelor*/
            dis_min[comp_aux] = suma_comp;
            comp_aux ++;  // incrementam componenta
            
        }
        
    }
    /*eliberam memoria*/
    free(distance);
    free(visited);

    /*ordonam crescatorul vectorul cu lungimile
     minime ale componentelor*/
    qsort(dis_min, comp, sizeof(int), cmp);

    return dis_min;
}

int cmp(const void *a , const void *b) {
    return ( *(int*)a - *(int*)b ); /*facem cast la int */ 
}
