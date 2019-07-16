#include "grafos.h"

int main(int argc, char *argv[]){
    Argumentos(argc, argv);
    printf ("Nome do arquivo: %s\n", string_i);
    VERTICE *GRAFO;

    struct rusage usage;                                // Struct utilizada para contagem de tempo da biblioteca #include<sys/time.h>
    struct timeval usu_comeco_wp, usu_fim_wp;           // Struct utilizada para marcar o começo e o fim da contagem
    struct timeval sis_comeco_wp, sis_fim_wp;           // de tempo do Algoritmo de Coloração de Welsh Powell
    struct timeval comeco, fim;
    gettimeofday(&comeco,NULL);                         // Se inicia a contagem do tempo total do programa

    FILE *read;                                               // Ponteiro que irá ler o arquivo.
    read = fopen (string_i,"r");                                // Ponteiro "read" abre o arquivo de entrada e fará a leitura dos caracteres do arquivo
    if (read == NULL){                                        // Caso o ponteiro "read" não ler nada, aparecerá a mensagem de erro.
        printf ("Arquivo não existente.\n");
        exit (1);
    }
    else{
        fscanf(read, "%d", &numv);                            // Caso exista o arquivo, o ponteiro irá ler a primeira linha do documento
        printf ("Vertices: %d\n", numv);                      // e armazerar o valor do numéro máximo de vertices na variável global "numv"

        int **matriz = matrix();
        int **conjcores = matrix();

        GRAFO = VETORIZA(matriz, read);

        // for (int i = 1; i < numv+1; i++){
        //     for (int j = 1; j < numv+1; j++){
        //         printf ("[%d] ", matriz[i][j]);
        //     }
        //     printf ("\n");
        // }

        // for (int i = 1; i < numv+1; i++)
        //     printf ("%d[%d] ", i, GRAFO[i]->grau);

        // printf ("\n");

        getrusage(RUSAGE_SELF, &usage);                     // Função que irá fazer a contagem de tempo do usuário e do sistema 
    
        usu_comeco_wp = usage.ru_utime;                    // Inicia a contagem do tempo usuário para o Algoritmo de Welsh Powell
        sis_comeco_wp = usage.ru_stime;                    // Inicia a contagem do tempo sistema para o Algoritmo de Welsh Powell

        int cor = Algoritmo_WP(GRAFO, conjcores, matriz, numv+1);

        printf ("VALOR CROMATICO: %d\n",cor);
        getrusage(RUSAGE_SELF, &usage);                     // Finaliza a contagem do tempo e retorna o tempo gasto executando do algoritmo 
        usu_fim_wp = usage.ru_utime;                       // Tempo total executando o algoritmo
        sis_fim_wp = usage.ru_stime;                       // Tempo real que o sistema gastou executando o algoritmo

        Imprimir_usuario(usu_comeco_wp, usu_fim_wp);          // Imprime o tempo de leitura, processamento e total
        Imprimir_sistema(sis_comeco_wp, sis_fim_wp);          // Imprime o tempo do sistema


        for (int i = 0; i < numv+1; i++){
            printf ("V:%d|Cor:%d / ", GRAFO[i]->id, GRAFO[i]->cor);
        }
        printf ("\n");
    }

    return 0;
}