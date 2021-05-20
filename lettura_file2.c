#include <stdio.h>
#include <stdlib.h>

#define MAX_LETTURE 168
#define BUFFSIZE 1024

struct misura {
    int aa, MM, gg;             
    int hh, mm, ss, ms;         
    char id[11];   
    float temp;                 
    int umid;                   
    float vel;                  
};

void leggi_file(FILE *f, struct misura *elenco, int *n);
void stampa_elenco(struct misura *elenco, int n);
float max_temp(struct misura *elenco, int n);
void stampa_riga(struct misura *elenco);

int main(int argc, char *argv[]) {
    FILE *file;
    struct misura misure[MAX_LETTURE];
    int n_lett;

    if (argc != 2) 
        return 0;

    file = fopen(argv[1], "r")
    if (file == NULL) 
        return 0;

    n_lett = leggi_file(file, misure);

    fclose();

    printf("[INVERSO]\n");
    stampa_elenco(misure, n_lett);

    printf("[MAX-TEMP]\n");
    printf("%.1f\n", max_temp(misure, n_lett));
    return 0;
}

void leggi_file(FILE *f, struct misura *elenco, int *n) {
    char buf[1000];
    int nconv;        
    struct misura *m;

    *n = 0;
    
    while (fgets(buf, sizeof(buf), f)) {
        
        m = elenco + (*n);
            nconv = sscanf(buf, "%d-%d-%d %d:%d:%d.%d %s %f %d%% %f",
                &(m->aa), &(m->MM), &(m->gg),
                &(m->hh), &(m->mm), &(m->ss), &(m->ms),
                (m->id), &(m->temp), &(m->umid), &(m->vel));
        
        if (nconv != 11) 
            continue;
        (*n)++;
        if ((*n) >= MAX_LETTURE) 
            break;
    }
}

void stampa_elenco(struct misura *elenco, int n) {
    int i;
    if (n <= 6) {
        for (i = n - 1; i >= 0; i--)
            stampa_riga(elenco + i);
    } else {
        for (i = 0; i < 3; i++)
            stampa_riga(elenco + i);
        for (i = n - 1; i >= n - 3; i--)
            stampa_riga(elenco + i);
    }
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

void stampa_riga(struct misura *elenco) {
    printf("%d-%d-%d %d:%d:%d.%d %s %f %d%% %f",
            elenco->aa, elenco->MM, elenco->gg,
            elenco->hh, elenco->mm, elenco->ss, elenco->ms,
            elenco->id, elenco->temp, elecno->umid, elenco->vel);
}