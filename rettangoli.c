#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXN 10
#define BUFFSIZE 1024

/* Definizione delle strutture */
struct punto_t {
    double x;
    double y;
};

struct rettangolo_t {
    struct punto_t A;
    struct punto_t B;
};

/* Prototipi delle funzioni */
struct punto_t leggi_punto(void);
void stampa_punto(struct punto_t p);
double distanza(struct punto_t p1, struct punto_t p2);
int interno(struct punto_t p, struct rettangolo_t r);
double area_rettangolo(struct rettangolo_t t);
void indici_max_dist(struct punto_t vett[], int len, int *max_i, int *max_j);

/* Main */
int main() {
    int n, 
        i, 
        index1,
        index2;
    char buff[BUFFSIZE]; 
    struct punto_t punti[MAXN];
    struct punto_t origine = {0 ,0};
    struct rettangolo_t rettangolo;

    fgets(buff, sizeof(buff), stdin);
    n = atoi(buff);

    if (n > MAXN)
        n = MAXN;

    /* Lettura dei punti da  tastiera */
    for (i = 0; i < n; i++) {
        punti[i] = leggi_punto();
    }

    /* Stampa dei punti */
    printf("[PUNTI]\n");
    for (i = 0; i < n; i++) {
        stampa_punto(punti[i]);
    }

    /* Calcolo delle distanze */
    printf("[DISTANZE]\n");
    for (i = 0; i < n; i++) {
        printf("%.3lf\n", distanza(origine, punti[i]));
    }

    /* Lettura dei punti del rettangolo */
    rettangolo.A = leggi_punto();
    rettangolo.B = leggi_punto();

    /* Calcolo dei punti interni */
    printf("[INTERNI]\n");
    for (i = 0; i < n; i++) {
        if (interno(punti[i], rettangolo)) {
            stampa_punto(punti[i]);
        }
    }

    /* Calcolo dell'area del rettangolo */
    printf("[AREA]\n");
    printf("%.3lf\n", area_rettangolo(rettangolo));

    /* Recerca dei punti con distanza massima */
    printf("[COPPIA]\n");
    indici_max_dist(punti, n, &index1, &index2);
    stampa_punto(punti[index1]);
    stampa_punto(punti[index2]);

    return 0;
}

/* Funzione per l'inserimento dei punti */
struct punto_t leggi_punto(void) {
    char buff[1024];
    struct punto_t p;

    fgets(buff, sizeof(buff), stdin);
    sscanf(buff, "%lf %lf", &p.x, &p.y);

    return p;
}

/* Funzione per la stampa dei punti */
void stampa_punto(struct punto_t p) {
    printf("(%.3lf, %.3lf)\n", p.x, p.y);
}

/* Funzione per il calcolo della distanza dall'origine  */
double distanza(struct punto_t p1, struct punto_t p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

/* Funzione per il calcolo dei punti interni al rettangolo */
int interno(struct punto_t p, struct rettangolo_t r) {
    if (p.x >= r.A.x && p.x <= r.B.x && p.y >= r.B.y && p.y <= r.A.y)
        return 1;
    else
        return 0;
}

/* Funzione per il calcolo dell'area del rettangolo */
double area_rettangolo(struct rettangolo_t r) {
    double b, h;

    b = r.B.x - r.A.x;
    h = r.A.y - r.B.y;

    return b * h;
}

/* Funzione per il calcolo dei punti piu' lontani */
void indici_max_dist(struct punto_t vett[], int len, int *max_i, int *max_j) {
    double max, dist;
    int i, j;

    *max_i = 0;
    *max_j = 0;

    max = distanza(vett[0], vett[1]);
    for (i = 0; i < len - 1; i++) {
        for (j = i + 1; j < len; j++) {
            dist = distanza(vett[i], vett[j]);
            if (dist > max) {
                max = dist; 
                *max_i = i;
                *max_j = j;
            }
        }
    }
}
