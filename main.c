/*NECULAU SANDA-ELENA GRUBA 313CB */
#include "tema3.h"

int main(int argc, char *argv[]) {

    TGL *G;
    char **lista_nume;  /*vectorul care retine numele nodurilor*/
    int *greutate;  /*vectorul ce va retine greutatile nodurilor*/
    int greutate_comoara = 0; 
    int i = 0;

    FILE *in;
    in = fopen("tema3.in", "rt");
    if(!in) {
        fprintf(stderr,"Unable to upen file %s\n", "tema3.in");
        return 0;
    }

    FILE *out;
    out = fopen("tema3.out", "wt");
    if (!out){
        fprintf(stderr, "ERROR: Nu se poate deschide fisierul %s\n", "tema3.out");
        return 0;
    }

    if(strcmp(argv[1], "1") == 0)
    {
        
        G = CitireG(in, &lista_nume);

        int nr_comp = 0;
        nr_comp = Nr_componente_conexe(G, lista_nume);

        /*vectorul cu distantele minime pe componenta*/
        int *dis_min;

        dis_min = lunigime_min(G, lista_nume, nr_comp);

        /*afisam numarul de componente*/
        fprintf(out,"%d\n", nr_comp);

        /*Afisare in fisier a distanta minime pe componenta*/
        for (i = 0; i < nr_comp; i++) {
            fprintf(out,"%d\n", dis_min[i]);
        }

        /*DISTRUGERE LISTA NUME*/
        for (i = 0; i <= G->n; i++) {
            free(lista_nume[i]);
        }
        free(dis_min);
        free(lista_nume);
        DistrugereGraf(&G);
        

    } else if(strcmp(argv[1], "2") == 0) {

        G = CitireG_2(in, &lista_nume, &greutate , &greutate_comoara);
        
        task2(G, lista_nume, greutate_comoara, greutate, out);

        /*DISTRUGERE LISTA NUME*/
        for (i = 0; i <= G->n; i++) {
            free(lista_nume[i]);
        }
        /*eliberare*/
        free(greutate);
        free(lista_nume);
        DistrugereGraf(&G);
    }
    
    fclose(out);
    return 0;
}