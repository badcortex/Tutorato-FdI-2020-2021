#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 1024

/* Prototipi delle funzioni */
int trova_ultimo_separatore(const char *percorso);
void basename(const char *percorso, char *basename);
void dirname(const char *percorso, char *dirname);
int assoluto(const char *percorso);
int trova_ultimo_carattere(const char *percorso, char c);
int estensione(const char *percorso, char *est);

/* Main */
int main(int argc, char *argv[]) {
	char buffer[BUFSIZE];

	if (argc != 2) {
		printf("[ERRORE]\n");
		printf("Inserisci dal terminale la stringa da analizzare!\n");
		exit(1);
	} 

	basename(argv[1], buffer);
	printf("[BASENAME]\n");
	printf("%s\n", buffer);

	dirname(argv[1], buffer);
	printf("[DIRNAME]\n");
	printf("%s\n", buffer);

	printf("[TIPO]\n");
	printf("%s\n", assoluto(argv[1]) ? "assoluto" : "relativo");

	printf("[ESTENSIONE]\n");
	printf("%s\n", estensione(argv[1], buffer) ? buffer : "nessuna");
	
	return 0;
}

/* Funzione per la ricerca dell'ultimo separatore */
int trova_ultimo_separatore(const char *percorso) {
	int pos = strlen(percorso) - 1;

	while (pos >= 0 && percorso[pos] != '/')
		pos--;
	return pos;
} 

/* Funzione per l'estrazione del basename */
void basename(const char *percorso, char *basename) {
	int pos = trova_ultimo_separatore(percorso);
	strcpy(basename, percorso + pos + 1);

	return ;
}

/* Funzione per l'estrazione del dirname */
void dirname(const char *percorso, char *dirname) {
	int i;
	int n = trova_ultimo_separatore(percorso);

	if (n >= 0) {
		for (i = 0; i < n; i++)
			dirname[i] = percorso[i];
		dirname[i] = '\0';
	} else {
		dirname[0] = '\0';
	}

	return ;
}

/* Funzione per stabilire se il percorso e' assoluto */
int assoluto(const char *percorso) {
	if (percorso[0] == '/')
		return 1;

	return 0;
}

/* Funzione per la ricerca dell'ultimo carattere */
int trova_ultimo_carattere(const char *percorso, char c) {
	int pos = strlen(percorso) - 1;

	while (pos >= 0 && percorso[pos] != c) 
		pos--;

	return pos;
}

/* Funzione per l'estrazione dell'estensione del file */
int estensione(const char *percorso, char *est) {
	int pos_punto = trova_ultimo_carattere(percorso, '.');
	int pos_sep = trova_ultimo_carattere(percorso, '/');
	int len = strlen(percorso);

	if (pos_punto < pos_sep)
		return 0;
	if (pos_punto + 1 == len) 
		return 0;
	if (pos_punto > 0) {
		strcpy(est, percorso + pos_punto + 1);
		return 1;
	}
	
	return 0;
}
