/*NECULAU SANDA-ELENA GRUPA 313CB*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <float.h>
#include <string.h>


typedef struct celarc { 
  char d[50];           /* destinatie arc */
  int c;            /* cost arc */
  struct celarc *urm; /* adresa urmatorului adiacent */
} TCelArc, *AArc;

typedef struct 
{ int n;
  AArc* x;
} TGL;

TGL* AlocG(int nr);
TGL * CitireG(FILE *in, char ***tlista_nume);
void DistrugereGraf(TGL **G);
void AfisareGraf(TGL *G);
TGL* CitireG_2(FILE *in, char ***tlista_nume, int **greutate, int *greutate_comoara);
void DFS(TGL *G, int index, int * visited, char **tlista_nume);
int Nr_componente_conexe(TGL *G, char **tlista_nume);
void DIJKSTRA(TGL *G, int sursa, char **tlista_nume,
        int **distanta, int*greutate, char ***path, float **scor);
int scor_min(int *visited, int n, float *scor);
void task2(TGL *G, char **tlista_nume, int grutate_comoara, int *greutate, FILE *out);
int *lm(TGL *G, char **tlista_nume, int comp);
int cmp(const void *a , const void *b);
int * lunigime_min(TGL *G, char **tlista_nume, int comp);
int MIN(int *visited, int n, int *distance);
int print_calea(TGL *G, char *start, char *end, char **path, 
                char**tlista_nume, FILE *out, int *greutate_min, int *greutate);