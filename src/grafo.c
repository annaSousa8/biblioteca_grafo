#include <stdio.h>
#include "grafo.h"
#include "merge_sort.h"
#include <stdlib.h>
 

void exibir_grafo(Grafo *grafo){
    for(int i=0; i<grafo->numVert; i++){
        for(int j=0; j<grafo->numVert; j++){
            printf(" %d ", (grafo->matriz)[i][j]);
        }
        printf("\n");
    }
}

void destruir_grafo(Grafo *grafo){
    for(int i=0; i<grafo->numVert; i++){
        free(grafo->matriz[i]);
    }

    free(grafo->matriz);
    free(grafo);
}

void add_elemento(Grafo *grafo, int linha, int coluna){
    grafo->matriz[linha][coluna] = 1;
    grafo->matriz[coluna][linha] = 1;
}


int numero_vertices(Grafo *grafo){
    return grafo->numVert;
}


int numero_arestas(Grafo *grafo){
    int cont  = 0, dp = 0, num_arestas = 0;
    for(int i=0; i<grafo->numVert; i++){
        for(int j=0; j<grafo->numVert; j++){
            if(grafo->matriz[i][j] == 1 && i != j){
                cont++;
            }
            if(i == j && grafo->matriz[i][j]==1){
                dp++;
            }
        }
    }
    //printf("% d, diagonal: %d", cont, dp);
    num_arestas = (cont/2)+dp;
    return(num_arestas);
}


int grau_maior(Grafo *grafo){
    int aux, maior = 0, pos_maior = 0;
    for(int i=0; i<grafo->numVert; i++){
        aux = 0;
        for(int j=0; j<grafo->numVert; j++){
            if(grafo->matriz[i][j] == 1){
                aux++;
            }
        }
        if(aux>maior){
            maior = aux;
            pos_maior = i;
        }
    }
    return(maior);
}


int grau_menor(Grafo *grafo){
    int aux, menor = grafo->numVert, pos_menor = 0;
    for(int i=0; i<grafo->numVert; i++){
        aux = 0;
        for(int j=0; j<grafo->numVert; j++){
            if(grafo->matriz[i][j] == 1){
                aux++;
            }
        }
        if(aux<menor){
            menor = aux;
            pos_menor = i;
        }
    }
    return(menor);
}


float grau_medio(Grafo *grafo){
    float cont=0, grau=0;
    for(int i=0; i<grafo->numVert; i++){
        for(int j=0; j<grafo->numVert; j++){
            if(grafo->matriz[i][j] == 1){
                cont++;
            }
        }
    }
    grau = cont/grafo->numVert;
    return(grau);
}


float mediana(Grafo *grafo){
    int graus[grafo->numVert];
    int aux;

    for(int i=0; i<grafo->numVert; i++){
        graus[i] = 0;
        for(int j=0; j<grafo->numVert; j++){
            if(grafo->matriz[i][j] == 1){
                graus[i]++;
            }
        }
    }

    merge_sort(graus, 0, grafo->numVert);

    if(grafo->numVert % 2 != 0){
        return(graus[grafo->numVert/2]);
    }
    else{
        return((graus[grafo->numVert/2] + graus[(grafo->numVert/2)-1])/2.0);
    }
}


Grafo *criarGrafo(int numVert){
    Grafo *grafo = malloc(sizeof(Grafo));

    int **matriz = (int **) malloc(sizeof(int *) * numVert);

    for(int i = 0; i < numVert; i++){
        matriz[i] = (int *) calloc(numVert, sizeof(int));
    }

    grafo->numVert = numVert;
    grafo->matriz = matriz;
    return grafo;
}


Grafo *ler_arquivo(const char *nomeArquivo){
    FILE *arquivo;
    int numVert, vert1, vert2;

    arquivo = fopen(nomeArquivo, "r");
    if(arquivo == NULL){
        printf("Erro ao abrir arquivo!\n");
        return NULL;
    }

    fscanf(arquivo, "%d", &numVert);
    Grafo *grafo = criarGrafo(numVert);
    while(fscanf(arquivo, "%d %d", &vert1, &vert2) == 2){
        add_elemento(grafo, vert1 - 1, vert2 - 1);
    }

    fclose(arquivo);
    return grafo;
}


static void alg_dfs_matriz(Grafo *grafo, int idx, int nivel, int *pai, int *niveis, char *visitados){
    visitados[idx] = 'v';
    niveis[idx] = nivel;

    for(int j=0; j<grafo->numVert; j++){
        if(grafo->matriz[idx][j] == 1 && visitados[j] == 'n'){
            pai[j] = idx;
            alg_dfs_matriz(grafo, j, nivel + 1, pai, niveis, visitados);
        }
    }
}


void dfs_matriz(Grafo *grafo, int inicio, const char *arquivoSaida){
    FILE *saida = fopen(arquivoSaida, "w");
    if(saida == NULL){
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    int *pai = malloc(sizeof(int) * grafo->numVert);
    int *niveis = malloc(sizeof(int) * grafo->numVert);
    char *visitados = malloc(sizeof(char) * grafo->numVert);

    for(int i=0; i<grafo->numVert; i++){
        pai[i] = -1;
        niveis[i] = -1;
        visitados[i] = 'n';
    }
    alg_dfs_matriz(grafo, inicio, 0, pai, niveis,visitados);

    fprintf(saida,"VERTICE PAI NIVEL\n");
    for(int i=0; i<grafo->numVert; i++){
        fprintf(saida, "%d %d %d\n", i+1, pai[i] == -1 ? 0 : pai[i]+1, niveis[i]);
    }

    fclose(saida);
    free(pai);
    free(niveis);
    free(visitados);
}


void bfs_matriz(Grafo *grafo, int inicio, const char *arquivoSaida){
    FILE *saida = fopen(arquivoSaida, "w");
    if(saida == NULL){
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    int *pai = malloc(sizeof(int) * grafo->numVert);
    int *nivel = malloc(sizeof(int) * grafo->numVert);
    char *visitados = malloc(sizeof(char) * grafo->numVert);
    int fila[grafo->numVert];
    int ini = 0, fim = 0;

    for(int i=0; i<grafo->numVert; i++){
        pai[i] = -1;
        nivel[i] = -1;
        visitados[i] = 'n';
    }

    visitados[inicio] = 'v';
    nivel[inicio] = 0;
    fila[fim++] = inicio;

    while(ini < fim){
        int atual = fila[ini++];
        for(int j=0; j<grafo->numVert; j++){
            if(grafo->matriz[atual][j] == 1 && visitados[j] == 'n'){
                visitados[j] = 'v';
                pai[j] = atual;
                nivel[j] = nivel[atual] + 1;
                fila[fim++] = j;
            }
        }
    }

    fprintf(saida, "VERTICE PAI NIVEL\n");
    for(int i=0; i<grafo->numVert; i++){
        fprintf(saida, "%d %d %d\n", i+1, pai[i] == -1 ? 0 : pai[i]+1, nivel[i]);
    }

    fclose(saida);
    free(pai);
    free(nivel);
    free(visitados);
}


void bfs_nivel(Grafo *grafo, int inicio, int *nivel){
    char *visitados = (char *) malloc(sizeof(char)*grafo->numVert);
    int fila[grafo->numVert];
    int ini = 0, fim = 0;

    for(int i=0; i<grafo->numVert; i++){
        visitados[i] = 'n';
        nivel[i] = -1;
    }
    visitados[inicio] = 'v';
    nivel[inicio] = 0;
    fila[fim++] = inicio;

    while (ini < fim){
        int atual = fila[ini++];
        for(int j=0; j<grafo->numVert; j++){
            if(grafo->matriz[atual][j] == 1 && visitados[j] == 'n'){
                visitados[j] = 'v';
                nivel[j] = nivel[atual] + 1;
                fila[fim++] = j;
            }
        }
    }
    free(visitados);
}


int distancia(Grafo *grafo, int origem, int destino){
    int *nivel = (int *) malloc(sizeof(int) * grafo->numVert);
    bfs_nivel(grafo, origem, nivel);
    int dist = nivel[destino];
    free(nivel);
    return dist;
}

int diametro(Grafo *grafo){
    int diam = 0;
    int *nivel = (int *) malloc(sizeof(int) * grafo->numVert);

    for(int i=0; i<grafo->numVert; i++){
        bfs_nivel(grafo, i, nivel);
        for(int j=0; j<grafo->numVert; j++){
            if(nivel[j] > diam){
                diam = nivel[j];
            }
        }
    }

    free(nivel);
    return diam;
}