#ifndef GRAFO_H
#define GRAFO_H

#include "componentes.h"

typedef struct grafomatriz
{
    int numVert;
    int **matriz;
} GrafoMatriz;

GrafoMatriz *criarGrafo(int numVert);
void exibir_grafo(GrafoMatriz *grafo);
void destruir_grafo(GrafoMatriz *grafo);
void add_elemento(GrafoMatriz *grafo, int linha, int coluna);

int numero_vertices(GrafoMatriz *grafo);
int numero_arestas(GrafoMatriz *grafo);
int grau_maior(GrafoMatriz *grafo);
int grau_menor(GrafoMatriz *grafo);
float grau_medio(GrafoMatriz *grafo);
float mediana(GrafoMatriz *grafo);

GrafoMatriz *ler_arquivo(const char *nomeArquivo);

void dfs_matriz(GrafoMatriz *grafo, int inicio, const char *arquivoSaida);
void bfs_matriz(GrafoMatriz *grafo, int inicio, const char *arquivoSaida);
void bfs_nivel(GrafoMatriz *grafo, int inicio, int *nivel);

int dfs_buscar(GrafoMatriz *grafo, int inicio, int alvo);
int bfs_buscar(GrafoMatriz *grafo, int inicio, int alvo);

int distancia(GrafoMatriz *grafo, int origem, int destino);
int diametro(GrafoMatriz *grafo);

Componentes *componentes_conexos(GrafoMatriz *grafo);

void gerar_relatorio(GrafoMatriz *grafo, const char *arquivoSaida);

#endif // !GRAFO_H
