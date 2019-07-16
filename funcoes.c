#include "grafos.h"

void Argumentos (int argc, char *argv[]){      // Esta função manipula os arquivos de entrada e saída digitados na linha de comando 
  for(int i = 0; i < argc; i++){               // Utilizamos um "for" para percorrer os argumentos
    if(strcmp(argv[i], "-i")==0){              // quando encontrarmos o parâmetro "-i",
      i++;                                     // incrementamos i, logo o próximo argumento será a entrada.
      strcpy(string_i, argv[i]);               // Logo a string "string_i" recebe o argumento de argv[i](entrada).
    }                                          // E...
    else if(strcmp(argv[i], "-o")==0){         // quando encontrarmos o parâmetro "-o",
      i++;                                     // incrementamos i, logo o proximo argumento será a saída.
      strcpy(string_o, argv[i]);               // Logo a string "string_o" recebe o argumento de argv[i](saída).
    }
  }
}

VERTICE *VETORIZA(int **matrix, FILE *read){                 // Função que lê dados dos arquivos
    int i, A, B;
    arestas = 0;                                              // int A = Vértice A e int B = Vértice B

  VERTICE *leitura = (VERTICE*) malloc(sizeof(VERTICE)*(numv+1));  // É feita uma alocação dinâmica para armazenar todos os vértices
  for ( i = 0; i < numv+1; i++){
      leitura[i] = criaVertice(i);                      // Os vértices são inicializados
  }
  while(!feof(read)){                                   // Depois o ponteiro irá seguir da segunda linha do documento até o fim
    fscanf (read,"%d" "%d", &A, &B);
    // printf ("A - %d B - %d\n", A, B);              // Os dados recebidos são responsáveis por indicar a ligação entre os vértices
    ligaVertices(A, B, leitura, matrix);              // que serão armazenados nas variáveis A e B e logo em seguida será feita a ligação dos vértices
  }                                                     // na função ligaVertices.
  fclose(read);                                         // Ponteiro "read" fecha o arquivo.
  printf ("Arestas %d\n", arestas);
  return leitura;
}                                                     // retorna o primeiro elemento do vetor de vértices (grafo)


VERTICE criaVertice(int id){                    // Onde é feita a inicialização de cada vértice

	VERTICE novoVertice = (VERTICE) malloc(sizeof(struct NO)); // Aloca um novo Vértice
	novoVertice->id = id;                      // Identidade do Vértice
	novoVertice->grau = 0;                     // Número de vizinhos para a lista de adjacência
	novoVertice->colorido = 0;                 // Funciona como uma variável booleana, avisando se o vértice já foi colorido
	novoVertice->cor = 0;                      // Cor do vértice
    
	return novoVertice;                         // retorna o vértice
}


void ligaVertices(int v1, int v2, VERTICE *GRAFO, int **matrix){      // Faz a ligação entre os vértices

  if (matrix[v1][v2] == 0 && matrix[v2][v1] == 0){
    matrix[v1][v2] = 1;
    matrix[v2][v1] = 1;

    GRAFO[v1]->grau++; // Incrementa o número de vizinhos
  // printf ("%d[%d] ", v1, GRAFO[v1]->grau);
    GRAFO[v2]->grau++; // Incrementa o número de vizinhos
  // printf ("%d[%d] ", v2, GRAFO[v2]->grau);
  // printf ("\n");
  arestas++;
  }
}

int **matrix (){

    int **matriz = (int **) calloc(numv+1, sizeof (int*));

    for (int i = 0; i < numv+1; i++){
        matriz[i] = (int *) calloc (numv+1, sizeof (int));
    }
    return matriz;
}

void Shellsort (VERTICE *vet, int tam){                     // Algoritmo de ordenação em ordem crescente em função do 
                                                            // número de vizinhos (grau do vértice). 
    int i , j;                                              // Variáveis do contador: i e j. E variável int tam é o tamanho do meu vetor(ou quantidade de pontos)
    VERTICE aux;                                            // Crio uma variável auxiliar "aux" do tipo VERTICE
    int intervalo = 1;                                      
    
    while(intervalo < tam){                                                                 
    intervalo = 3*intervalo+1;                              
    }
    while ( intervalo > 1) {                                
    intervalo /= 3;                                         
        for(i = intervalo; i < tam; i++) {                  
        aux = vet[i];                                       
        j = i - intervalo;
            while (j >= 0 && aux->grau < vet[j]->grau) {
            vet[j + intervalo] = vet[j];
            j -= intervalo;
            }
        vet[j + intervalo] = aux;
        }
    }
}

int Algoritmo_WP(VERTICE *GRAFO, int **conjcores, int **matriz, int tam){

  int cor = 0, indice = 0, cont = 0;

  Shellsort(GRAFO,tam);
  
  for (int i = tam-1; i >= 0; i--){
    if (GRAFO[i]->colorido == 0){
      conjcores[cor][indice] = GRAFO[i]->id;
      indice++;
      GRAFO[i]->colorido = 1;
      GRAFO[i]->cor = cor+1;
      for (int j = i-1; j >= 0; j--){
        if (GRAFO[j]->colorido == 0){
          if (matriz[GRAFO[i]->id][GRAFO[j]->id] == 0){
            for (int k = 1; k < indice && cont != 1; k++){
              if (matriz[conjcores[cor][k]][GRAFO[j]->id] == 1){
                cont++;
              }
            }
            if (cont == 0){
              conjcores[cor][indice] = GRAFO[j]->id;
              indice++;
              GRAFO[j]->colorido = 1;
              GRAFO[j]->cor = cor+1;
            }
          }
          cont = 0;
        }
      }
      cor++;
    }
  }
  return cor;
}


// FUNÇÕES DE TEMPO

void Imprimir_usuario (struct timeval start, struct timeval tend){                    // Função Tempo utilizando getrusage
    // start.tv_sec e start.tv_usec são dadas em long int, porém são de grandezas escalares diferentes, pois são segundos
    // e micro-segundos(1 milhão de vezes menor que o segundo) respectivamente.
    // O tempo de leitura é dado por "startsec", que foi onde terminamos de analisar o tempo de leitura e começamos a analisar o tempo de processamento do algoritmo
    double startsec = (((double)start.tv_sec) + ((double)start.tv_usec/1000000));   // O tempo total do programa é dado por "endsec".
    double endsec = (((double)tend.tv_sec) + ((double)tend.tv_usec/1000000));       // O tempo de processamento do algoritmo de ordenação e 
    double process = (endsec - startsec);                                           // comparação é dado pela diferença de "endsec" e "startsec"
                                                                                    // 
    printf ("\nTempo de Leitura: %.5f segundos.\n Tempo de Processamento: %.5f segundos.\n", startsec, process);
}

void Imprimir_sistema (struct timeval start, struct timeval tend){                    // Função Tempo utilizando getrusage
  double sistema = (((double)tend.tv_sec) + ((double)tend.tv_usec/1000000)) - (((double)start.tv_sec) + ((double)start.tv_usec/1000000));
  printf ("Tempo Sistema: %.5f segundos.\n", sistema);
}