#ifndef GRAFO_D_H
#define GRAFO_D_H

#include "componentes.h"

typedef struct elem{
    int valor;
    int visitado;
    struct elem *prox;
}Elem;

typedef struct grafo{
    Elem **lista;
    int tam;
}GrafoLista;

GrafoLista * criar_grafo(int tam);
void destroir( GrafoLista *g );

int grafo_adicionar_no(GrafoLista *g, int n1, int n2);

int grafo_num_arestas( GrafoLista *g);
int grafo_num_vertices( GrafoLista *g);
int grafo_grau_min( GrafoLista *g);
int grafo_grau_max( GrafoLista *g);
float grafo_grau_medio(GrafoLista *g);
float grafo_grau_mediano(GrafoLista *g);

void grafo_mostrar(GrafoLista *g);
void grafo_limpar(GrafoLista *g);

void lerArquivo(GrafoLista *grafo, const char *nomeArquivo);

void dfs_arvore(GrafoLista *g, int inicio, const char *arquivoSaida);
void bfs_arvore(GrafoLista *g, int inicio, const char *arquivoSaida);

int grafo_dfs_buscar(GrafoLista *g, int inicio, int alvo);
int grafo_bfs_buscar(GrafoLista *g, int inicio, int alco);

void grafo_bfs_distancia(GrafoLista *g, int inicio, int *dist);
int vertice_mais_distante(GrafoLista *g, int *dist);
int diametro_aproximado(GrafoLista *g);

int grafo_distancia(GrafoLista *g, int origem, int destino);
int grafo_diametro(GrafoLista *g);

Componentes *grafo_componentes_conexos(GrafoLista *g);

void grafo_gerar_relatorio(GrafoLista *g, const char *arquivoSaida);

#endif // !GRAFO_D_H
