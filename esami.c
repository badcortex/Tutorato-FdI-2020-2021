#include <stdio.h>
#include <stdlib.h>

#define DIM 100
#define MIN 0
#define MAX4 22
#define MAX6 33
#define SUP4 10
#define SUP6 16

/* Prototipi delle funzioni */ 
int leggi_voti(int vet[], int n, int m);
void stampa_vettore(int vet[], int n);
int superati(int vet[], int n, int m);

/* Main */
int main() {
	int voti[DIM], // Vettore dei voti 
		n, 		   // Lunghezza del vettore dei voti 
		m;		   // Numero di domande 
	int voti_scartati = 0;

	scanf("%d", &n);
	if (n <= 0 || n > 100) {
		printf("[RISULTATO]\n");
		printf("errore\n");
		return 0;
	}

	scanf("%d", &m);
	if (m != 4 &&  m != 6) {
		printf("[RISULTATO]\n");
		printf("errore\n");
		return 0;
	}

	// Inserimento dei voti da tastiera
	voti_scartati = leggi_voti(voti, n, m);

	// Stampa del vettore dei valori inseriti
	printf("[VALORI]\n");
	stampa_vettore(voti, n);

	printf("[SCARTATI]\n");
	printf("%d\n", voti_scartati);

	// Calcolo e stampa degli esami superati
	printf("[SUPERATI]\n");
	printf("%d\n", superati(voti, n, m));
	
	return 0;
}

/* Funzione per la lettura del vettore dei voti */
int leggi_voti(int vet[], int n, int m) {
	int i, voto, max_voto, voti_scartati = 0;

	if (m == 4) 
		max_voto = MAX4;
	else
		max_voto = MAX6;

	i = 0;
	do {
		scanf("%d", &voto);

		if (voto >= MIN && voto <= max_voto) {
			vet[i] = voto;
			i++;
		} else {
			voti_scartati++;
		}
	} while (i < n);

	return voti_scartati;
}

/* Funzione per la stampa del vettore */
void stampa_vettore(int vet[], int n) {
	int i;
	for (i = 0; i < n; i++) 
		printf("%d\n", vet[i]);
}

/* Funzione per il calcolo degli esami superati */
int superati(int vet[], int n, int m) {
	int i, min_sup, superati = 0;
	if (m == 4)
		min_sup = SUP4;
	else 
		min_sup = SUP6;

	for (i = 0; i < n; i++) 
		if (vet[i] > min_sup)
			superati++;

	return superati;
}
