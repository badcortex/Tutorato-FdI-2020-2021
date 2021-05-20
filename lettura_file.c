#include <stdio.h>
#include <stdlib.h>

#define BUFFSIZE 1024

void elabora_file(FILE *f);
int notturno(int h);

int main(int argc, char *argv[]) {
    FILE *infile;

    if (argc != 2) {
        return 1;
    }

    infile = fopen(argv[1], "r");

    if (infile == NULL) {
        fprintf(stderr, "# ERRORE apertura file \n");
        return 1;
    }

    elabora_file(infile);
    fclose(infile);

    return 0;
}

void elabora_file(FILE *f) {
    char buff[BUFFSIZE];
    int n, ncov;
    float max_temp;
    int aa, MM, gg;
    int hh, mm, ss, ms;
    char id[11];
    float temp;
    int umid;
    float vel;

    printf("[NOTTURNO]\n");
    n = 0;
    max_temp = -300.0;
    while(fgets(buff, sizeof(buff), f)) {
        ncov = sscanf(buff, "%d-%d-%d %d:%d:%d.%d %s %f %d%% %f", 
                      &aa, &MM, &gg, &hh, &mm, &ss, &ms, id, &temp, &umid, &vel);
        
        if (ncov != 11)
            continue;
        if (temp > max_temp)
            max_temp = temp;
        if (notturno(hh))
            printf("%s", buff);
        n++;
    }

    printf("[MAX-TEMP]\n");
    printf("%.1f\n", max_temp);
    printf("[RIGHE]\n");
    printf("%d\n", n);
}

int notturno(int h) {
    if ((h >= 22) || (h <= 5))
        return 1;
    return 0; 
}