#include <stdio.h>
#include "grafo.h"
#include "merge_sort.h"
#include <stdlib.h>

#include <time.h>

GrafoMatriz *criarGrafo(int numVert){
    GrafoMatriz *grafo = malloc(sizeof(GrafoMatriz));

    int **matriz = (int **) malloc(sizeof(int *) * numVert);

    for(int i = 0; i < numVert; i++){
        matriz[i] = (int *) calloc(numVert, sizeof(int));
    }

    grafo->numVert = numVert;
    grafo->matriz = matriz;
    return grafo;
}
void exibir_grafo(GrafoMatriz *grafo){
    for(int i=0; i<grafo->numVert; i++){
        for(int j=0; j<grafo->numVert; j++){
            printf(" %d ", (grafo->matriz)[i][j]);
        }
        printf("\n");
    }
}
void destruir_grafo(GrafoMatriz *grafo){
    for(int i=0; i<grafo->numVert; i++)
        free(grafo->matriz[i]);

    free(grafo->matriz);
    free(grafo);
}
void add_elemento(GrafoMatriz *grafo, int linha, int coluna){
    grafo->matriz[linha][coluna] = 1;
    grafo->matriz[coluna][linha] = 1;
}


int numero_vertices(GrafoMatriz *grafo){
    return grafo->numVert;
}
int numero_arestas(GrafoMatriz *grafo){
    int cont  = 0, dp = 0, num_arestas = 0;
    for(int i=0; i<grafo->numVert; i++){
        for(int j=0; j<grafo->numVert; j++){
            if(grafo->matriz[i][j] == 1 && i != j)
                cont++;

            if(i == j && grafo->matriz[i][j]==1)
                dp++;
        }
    }
    num_arestas = (cont/2)+dp;
    return(num_arestas);
}


int grau_maior(GrafoMatriz *grafo){
    int aux, maior = 0;
    for(int i=0; i<grafo->numVert; i++){
        aux = 0;
        for(int j=0; j<grafo->numVert; j++){
            if(grafo->matriz[i][j] == 1){
                aux++;
            }
        }
        if(aux>maior){
            maior = aux;
        }
    }
    return(maior);
}
int grau_menor(GrafoMatriz *grafo){
    int aux, menor = grafo->numVert;
    for(int i=0; i<grafo->numVert; i++){
        aux = 0;
        for(int j=0; j<grafo->numVert; j++){
            if(grafo->matriz[i][j] == 1){
                aux++;
            }
        }
        if(aux<menor){
            menor = aux;
        }
    }
    return(menor);
}
float grau_medio(GrafoMatriz *grafo){
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


float mediana(GrafoMatriz *grafo){
    int graus[grafo->numVert];

    for(int i=0; i<grafo->numVert; i++){
        graus[i] = 0;
        for(int j=0; j<grafo->numVert; j++){
            if(grafo->matriz[i][j] == 1)
                graus[i]++;
        }
    }

    merge_sort(graus, 0, grafo->numVert - 1);

    if(grafo->numVert % 2 != 0){
        return(graus[grafo->numVert/2]);
    }
    else{
        return((graus[grafo->numVert/2] + graus[(grafo->numVert/2)-1])/2.0);
    }
}


GrafoMatriz *ler_arquivo(const char *nomeArquivo){
    FILE *arquivo;
    int numVert, vert1, vert2;

    arquivo = fopen(nomeArquivo, "r");
    if(arquivo == NULL){
        printf("Erro ao abrir arquivo!\n");
        return NULL;
    }

    fscanf(arquivo, "%d", &numVert);
    GrafoMatriz *grafo = criarGrafo(numVert);
    while(fscanf(arquivo, "%d %d", &vert1, &vert2) == 2){
        add_elemento(grafo, vert1 - 1, vert2 - 1);
    }

    fclose(arquivo);
    return grafo;
}


static void alg_dfs_matriz(GrafoMatriz *grafo, int idx, int nivel, int *pai, int *niveis, char *visitados){
    visitados[idx] = 'v';
    niveis[idx] = nivel;

    for(int j=0; j<grafo->numVert; j++){
        if(grafo->matriz[idx][j] == 1 && visitados[j] == 'n'){
            pai[j] = idx;
            alg_dfs_matriz(grafo, j, nivel + 1, pai, niveis, visitados);
        }
    }
}
void dfs_matriz(GrafoMatriz *grafo, int inicio, const char *arquivoSaida){
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
void bfs_matriz(GrafoMatriz *grafo, int inicio, const char *arquivoSaida){
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
void bfs_nivel(GrafoMatriz *grafo, int inicio, int *nivel){
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
static int alg_dfs_buscar(GrafoMatriz *grafo, int idx, int alvo, char *visitados){
    if(idx == alvo)
        return 1;
    visitados[idx] = 'v';

    for(int j=0; j<grafo->numVert; j++)
        if(grafo->matriz[idx][j] == 1 && visitados[j] == 'n')
            if(alg_dfs_buscar(grafo, j, alvo, visitados))
                return 1;

    return 0;
}
int dfs_buscar(GrafoMatriz *grafo, int inicio, int alvo){
    char *visitados = malloc(sizeof(char) * grafo->numVert);
    for(int i=0; i<grafo->numVert; i++)
        visitados[i] = 'n';


    clock_t inicio_t = clock();
    int achou = alg_dfs_buscar(grafo, inicio, alvo, visitados);
    clock_t fim_t = clock();
    printf("Tempo: %f s\n", (double)(fim_t-inicio_t)/CLOCKS_PER_SEC);


    free(visitados);
    return achou;
}
int bfs_buscar(GrafoMatriz *grafo, int inicio, int alvo){
    if(inicio == alvo){
        return 1;
    }

    char *visitados = malloc(sizeof(char) * grafo->numVert);
    int *fila = malloc(sizeof(int) * grafo->numVert);
    int ini = 0, fim = 0;

    for(int i=0; i<grafo->numVert; i++){
        visitados[i] = 'n';
    }
    visitados[inicio] = 'v';
    fila[fim++] = inicio;

    int achou = 0;
    clock_t inicio_t = clock();
    while(ini < fim && !achou){
        int atual = fila[ini++];
        for(int j=0; j<grafo->numVert; j++){
            if(grafo->matriz[atual][j] == 1 && visitados[j] == 'n'){
                if(j == alvo){
                    achou = 1;
                    break;
                }
                visitados[j] = 'v';
                fila[fim++] = j;
            }
        }
    }
    clock_t fim_t = clock();
    printf("Tempo: %f s\n", (double)(fim_t-inicio_t)/CLOCKS_PER_SEC);

    free(visitados);
    free(fila);
    return achou;
}


int distancia(GrafoMatriz *grafo, int origem, int destino){
    int *nivel = (int *) malloc(sizeof(int) * grafo->numVert);
    bfs_nivel(grafo, origem, nivel);
    int dist = nivel[destino];
    free(nivel);
    return dist;
}

int diametro(GrafoMatriz *grafo){
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


Componentes *componentes_conexos(GrafoMatriz *grafo){
    char *visitado = malloc(sizeof(char) * grafo->numVert);
    for(int i=0; i<grafo->numVert; i++){
        visitado[i] = 'n';
    }

    int *tamanhos = malloc(sizeof(int) * grafo->numVert);
    int **vertices = malloc(sizeof(int *) * grafo->numVert);
    int numComp = 0;

    int *fila = malloc(sizeof(int) * grafo->numVert);

    for(int i=0; i<grafo->numVert; i++){
        if(visitado[i] == 'n'){
            int ini = 0, fim = 0;
            fila[fim++] = i;
            visitado[i] = 'v';

            int *compVertices = malloc(sizeof(int) * grafo->numVert);
            int tamComp = 0;

            while(ini < fim){
                int atual = fila[ini++];
                compVertices[tamComp++] = atual + 1; /* saida 1-indexada */

                for(int j=0; j<grafo->numVert; j++){
                    if(grafo->matriz[atual][j] == 1 && visitado[j] == 'n'){
                        visitado[j] = 'v';
                        fila[fim++] = j;
                    }
                }
            }

            compVertices = realloc(compVertices, sizeof(int) * tamComp);
            vertices[numComp] = compVertices;
            tamanhos[numComp] = tamComp;
            numComp++;
        }
    }

    free(fila);
    free(visitado);

    /* ordena por tamanho decrescente */
    for(int i=0; i<numComp-1; i++){
        int maior = i;
        for(int j=i+1; j<numComp; j++){
            if(tamanhos[j] > tamanhos[maior]){
                maior = j;
            }
        }
        if(maior != i){
            int tAux = tamanhos[i];
            tamanhos[i] = tamanhos[maior];
            tamanhos[maior] = tAux;

            int *vAux = vertices[i];
            vertices[i] = vertices[maior];
            vertices[maior] = vAux;
        }
    }

    Componentes *comp = malloc(sizeof(Componentes));
    comp->numComponentes = numComp;
    comp->tamanhos = realloc(tamanhos, sizeof(int) * numComp);
    comp->vertices = realloc(vertices, sizeof(int *) * numComp);

    return comp;
}




void gerar_relatorio(GrafoMatriz *grafo, const char *arquivoSaida){
    FILE *saida = fopen(arquivoSaida, "w");
    if(saida == NULL){
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    fprintf(saida, "Numero de vertices: %d\n", numero_vertices(grafo));
    fprintf(saida, "Numero de arestas: %d\n", numero_arestas(grafo));
    fprintf(saida, "Grau minimo: %d\n", grau_menor(grafo));
    fprintf(saida, "Grau maximo: %d\n", grau_maior(grafo));
    fprintf(saida, "Grau medio: %.2f\n", grau_medio(grafo));
    fprintf(saida, "Mediana de grau: %.2f\n", mediana(grafo));

    fclose(saida);
}

