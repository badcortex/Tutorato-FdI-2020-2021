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

    return 0;
}


struct misura *leggi_file(FILE *f, int *n)
{
    struct misura *misura, *elenco, *tmp_ptr;
    char buff[BUFFSIZE];
    int nconv;      
    int dim = 4;

    *n = 0;

    elenco = malloc(dim * sizeof(*elenco));

    while (fgets(buff, sizeof(buff), f)) {
        
        misura = elenco + (*n);
        nconv = sscanf(buff, "%d-%d-%d %d:%d:%d.%d %s %f %d%% %f",
            &(misura->aa), &(misura->MM), &(misura->gg),
            &(misura->hh), &(misura->mm), &(misura->ss), &(misura->ms),
            (misura->id), &(misura->temp), &(misura->umid), &(misura->vel));
        
        if (nconv != 11) continue;
        
        (*n)++;
        
        if ((*n) >= dim) {
            dim *= 2;
            tmp_ptr = realloc(elenco, dim * sizeof(*elenco));
            if (tmp_ptr == NULL) return NULL;
            elenco = tmp_ptr;
        }
    }
    
    elenco = realloc(elenco, (*n) * sizeof(*elenco));

    return elenco;
}


void stampa_identificativi(struct misura *elenco, int n) {
    int i;

    for (i = n - 1; i >= 0; i--)
        printf("%s\n", (elenco + i)->id);
}


