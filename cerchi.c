#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFSIZE 1024

#define NESSUNA 0
#define INTERSECA 1
#define CONTIENE 2
#define COINCIDE 3
#define SQR(x) ((x)*(x))

struct cerchio {
    char *nome;
    int x, y;
    unsigned int r;
};

char *nome_relazione[] = {"", "INTERSECA", "CONTIENE", "COINCIDE"};

/* Prototipi delle funzioni */
struct cerchio *carica_elenco(FILE *file, int *n);
void stampa_cerchi(struct cerchio *c, int n);
// void ordina(struct cerchio *c, int n);
int cmp_cerchi(const void *p1, const void *p2);
int relazione(struct cerchio *c1, struct cerchio *c2);
void stampa_relazioni(struct cerchio *c, int n);

int main(int argc, char *argv[]) {
    FILE *f;
    struct cerchio *cerchi;
    int n;

    f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("[ERRORE]\n");
        printf("Lettura del file non riuscita!");
        exit(1);
    }

    cerchi = carica_elenco(f, &n);
    fclose(f);

    if (cerchi == NULL && n == -1) {
        printf("[ERRORE]\n");
        printf("Il file e' vuoto!");
        exit(1);
    }

    printf("[CERCHI]\n");
    stampa_cerchi(cerchi, n);

    // ordina(cerchi, n);
    qsort(cerchi, n, sizeof(*cerchi), cmp_cerchi);
    printf("[ORDINAMENTO]\n");
    stampa_cerchi(cerchi, n);

    printf("[RELAZIONI]\n");
    stampa_relazioni(cerchi, n);
    
    return 0;
}


/* Funzione per la lettura del file */
struct cerchio *carica_elenco(FILE *file, int *n) {
    char buff[BUFFSIZE];
    char nome_cerchio[128];
    struct cerchio *c;
    int dim = 128;

    if (!(c = malloc(dim * sizeof(struct cerchio)))) {
        *n = -1;
        return NULL;
    }

    *n = 0;
    while(fgets(buff, sizeof(buff), file)) {
        sscanf(buff, "%127s %d %d %d", nome_cerchio, &(c + *n)->x, &(c + *n)->y,
               &(c + *n)->r);
        (c + *n)->nome = strdup(nome_cerchio);
        (*n)++;
        if(*n >= dim) {
            dim *= 2;
            if (!(c = realloc(c, dim * sizeof(struct cerchio)))) {
                *n = -1;
                return NULL;
            }
        }
    }

    c = realloc(c, (*n) * sizeof(struct cerchio));
    return c;
}

/* Funzione per la stampa dei cerchi */
void stampa_cerchi(struct cerchio *c, int n) {
    int i;

    for (i = 0; i < n; i++) 
        printf("%s %d %d %d\n", (c + i)->nome, (c + i)->x, (c + i)->y, 
               (c + i)->r);
}

/* Funzione per l'ordinamento */
// void ordina(struct cerchio *c, int n) {
//     int i, j;
//     struct cerchio temp;

//     for ( i = 0; i < n; i++) {
//         for (j = i + 1; j < n; j++) {
//             if (c[i].r > c[j].r) {
//                 temp = c[i];
//                 c[i] = c[j];
//                 c[j] = temp;
//             }
//         }
//     }
// }

/* Funzione per il confronto di due cerchi */
int cmp_cerchi(const void *p1, const void *p2) {
    const struct cerchio *c1 = p1, *c2 = p2;

    if (c1->r < c2->r) return -1;
    if (c1->r > c2->r) return 1;

    return 0;
}


/* Funzione per il calcolo della distanza tra due punti */ 
double dist(int x1, int y1, int x2, int y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}


/* Funzione per determinare il tipo di relazione tra due cerchi  */
int relazione(struct cerchio *c1, struct cerchio *c2) {
    int rel = NESSUNA;
    int sd;

    sd = sqrt(SQR(c1->x - c2->x) + SQR(c1->y - c2->y));
    if(sd <= (c1->r + c2->r)) {
        if (c1->x == c2->x && c1->y == c2->y && c1-> r == c2->r)
            rel = COINCIDE;
        else if (sd >= abs(c1->r - c2->r))
            rel = INTERSECA;
        else if (c1->r > c2->r)
            rel = CONTIENE;
    }

    return rel;
}

void stampa_relazioni(struct cerchio *c, int n) {
    int i, j, rel;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i != j) {
                rel = relazione(c+i, c+j);
                if (rel != NESSUNA)
                    printf("%s %s %s\n", (c + i)->nome, nome_relazione[rel], (c + j)->nome);
            }
        }
    }
} 
