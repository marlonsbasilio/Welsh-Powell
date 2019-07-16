#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    // Argumentos(argc, argv);
    FILE *write = fopen ("completo10","w");
    // int arestas;
    int numv = 15000;
    // arestas = (numv * ( numv-1))/2;

    fprintf (write, "%d\n", numv);

    for (int i = 1; i < numv+1; i++){
        for (int j = i+1; j < numv+1; j++){
            fprintf(write, "%d %d\n", i, j);
        }
    }   
    fclose(write);
    return 0;
}