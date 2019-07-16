#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <time.h>

typedef struct NO{
    int id;
    int grau;
    int cor;
    int colorido;
}*VERTICE;

int numv;
int arestas;

char string_i[40];
char string_o[40];

// função manipula os arquivos de entrada e saída digitados na linha de comando
void Argumentos (int argc, char *argv[]);
VERTICE *VETORIZA(int **matrix, FILE *read);                      // Faz a leitura do arquivo e monta o grafo
VERTICE criaVertice(int id);                                       // Inicia os vértices
void ligaVertices(int v1, int v2, VERTICE *GRAFO, int **matrix);   // Define as adjacencias do grafo na matriz

// Algoritmo de Ordenação
void Shellsort (VERTICE *vet, int tam);

// matriz de adjacencia
int **matrix();

// heuristica de Welsh Powell
int Algoritmo_WP(VERTICE *GRAFO, int **conjcores, int **matriz, int tam);

// funções do tempo
void Imprimir_usuario (struct timeval start, struct timeval tend);
void Imprimir_sistema (struct timeval start, struct timeval tend);
