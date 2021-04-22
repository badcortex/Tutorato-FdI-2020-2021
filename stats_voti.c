#include <stdio.h>
#include <stdlib.h>

#define MINVOTO 18 
#define MAXVOTO 30
#define NMAX 100
#define NVOTI (MAXVOTO - MINVOTO + 1)

/* Prototipi delle funzioni */
void leggi_voti(int vet[], int n);
void stampa_vettore(int vet[], int n);
int minimo(int vet[], int n);
void frequenze(int vet[], int n, int freq[]);
int max_indice(int vet[], int n);

/* Main */
int main() {
    int i, n;
    int voti[NMAX],
        freq[NVOTI] = {0};

    scanf("%d", &n);

    if (n <= 0 || n > NMAX) {
        printf("[RISULTATO]\nerrore\n");

        return 0;
    }

    leggi_voti(voti, n);

    printf("[VALORI]\n");
    stampa_vettore(voti, n);

    printf("[MINIMO]\n");
    printf("%d\n", minimo(voti, n));

    frequenze(voti, n, freq);
    printf("[FREQUENZE]\n");
    for (i = 0; i < NVOTI; i++)
        printf("%d\n", freq[i]);

    printf("[MAXFREQ]\n");
    printf("%d\n", max_indice(freq, NVOTI) + MINVOTO);

    return 0;
}

/* Funzione per lalettura dei voti da tastiera */
void leggi_voti(int vet[], int n) {
    char s[80];
    int i, voto;

    i = 0;
    do {
        fgets(s, sizeof(s), stdin);
        voto = atoi(s);

        if (voto >= MINVOTO && voto <= MAXVOTO) {
            vet[i] = voto;
            i++;
        }
    } while(i < n);
}

/* Funzione per l stampa dei vettori */
void stampa_vettore(int vet[], int n) {
    int i;
    for (i = 0; i < n; i++)
        printf("%d\n", vet[i]);
}

/* Funzione per il calcolo del minimo */
int minimo(int vet[], int n) {
    int i, min;
    
    min = vet[0];
    for (i = 1; i < n; i++)
        if(vet[i] < min)
            min = vet[i];

    return min;
}

/* Funzione per il calcolo delle frequenze */
void frequenze(int vet[], int n, int freq[]) {
    int i;
    for (i = 0; i < n; i++)
        freq[vet[i] - MINVOTO]++;
}

/* Funzione per il calcolo dell'oindice massimo */
int max_indice(int vet[], int n) {
    int i, maxIndice = 0;

    for (i = 1; i < n; i++)
        if (vet[i] > vet[maxIndice])
            maxIndice = i;

    return maxIndice;
}