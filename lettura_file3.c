#include <stdio.h>
#include <stdlib.h>

#define BUFFSIZE 1024

struct misura {
    int aa, MM, gg;             
    int hh, mm, ss, ms;         
    char id[11];   
    float temp;                 
    int umid;                   
    float vel;                  
};

struct misura *leggi_file(FILE *f, int *n);
void stampa_identificativi(struct misura *elenco, int n);
float max_temp(struct misura *elenco, int n);

int main(int argc, char *argv[]) {
    FILE *file;
    struct misura *misure;
    int n;

    if (argc != 2)
        return 0;

    file = fopen(argv[1], "r");
    if (file == NULL)
        return 0;

    misure = leggi_file(file, &n);

    fclose(file);

    printf("[IDENTIFICATIVI]\n");
    stampa_identificativi(misure, n);

    printf("[MAX-TEMP]\n");
    printf("%.1f\n", max_temp(misure, n));

    printf("[RIGHE]\n");
    printf("%d\n", n);

    return 0;
}


struct misura *leggi_file(FILE *f, int *n) {
    char buff[BUFFSIZE];
    int nconv;        
    struct misura *misura, *elenco;
    int size, i;
    int a, b;

    *n = 0;

    fgets(buff, sizeof(buff), f);
    sscanf(buff, "%d", &a);
    fgets(buff, sizeof(buff), f);
    sscanf(buff, "%d", &b);
    if ((b < a) || (a < 0) || (b < 0)) return NULL;

    size = (b - a + 1);
    elenco = malloc(size * sizeof(*elenco));

    for (i = 0; i < a; i++)
        fgets(buff, sizeof(buff), f);

    while (fgets(buff, sizeof(buff), f)) {
        misura = elenco + (*n);
        nconv = sscanf(buff, "%d-%d-%d %d:%d:%d.%d %s %f %d%% %f",
            &(misura->aa), &(misura->MM), &(misura->gg),
            &(misura->hh), &(misura->mm), &(misura->ss), &(misura->ms),
            (misura->id), &(misura->temp), &(misura->umid), &(misura->vel));
        
        if (nconv != 11) continue;
        
        (*n)++;
        
        if ((*n) >= size) break;
    }
    
    if ((*n < size))
        elenco = realloc(elenco, (*n) * sizeof(*elenco));

    return elenco;
}


void stampa_identificativi(struct misura *elenco, int n) {
    int i;

    for (i = n - 1; i >= 0; i--)
        printf("%s\n", (elenco + i)->id);
}


float max_temp(struct misura *elenco, int n) {
    float max_temp;
    int i;

    if (n <= 0) 
        return -1000;
    max_temp = elenco[0].temp;
    for (i = 1; i < n; i++) {
        if ((elenco + i)->temp > max_temp)
            max_temp = (elenco + i)->temp;
    }
    return max_temp;
}
