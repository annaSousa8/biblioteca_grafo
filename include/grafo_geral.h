#ifndef GRAFO_GERAL_H
#define GRAFO_GERAL_H

#include "grafo.h"
#include "grafo_d.h"
#include "componentes.h"

/* Representacao escolhida pelo usuario para o grafo */
typedef enum {
    MATRIZ,
    LISTA
} TipoGrafo;

/*
 * Struct "fachada": guarda qual representacao foi escolhida e um ponteiro
 * para o grafo de fato (so um dos dois ponteiros vai estar preenchido).
 * As funcoes gg_* recebem essa struct e chamam a funcao certa por baixo,
 * de acordo com o campo "tipo".
 */
typedef struct {
    TipoGrafo tipo;
    GrafoMatriz *grafoMatriz;
    GrafoLista *grafoLista;
} GrafoGeral;

GrafoGeral *criar_grafo_geral(TipoGrafo tipo, int numVert);
GrafoGeral *ler_grafo_geral(TipoGrafo tipo, const char *nomeArquivo);
void destruir_grafo_geral(GrafoGeral *g);

int gg_adicionar_aresta(GrafoGeral *g, int v1, int v2);

int gg_numero_vertices(GrafoGeral *g);
int gg_numero_arestas(GrafoGeral *g);
int gg_grau_menor(GrafoGeral *g);
int gg_grau_maior(GrafoGeral *g);
float gg_grau_medio(GrafoGeral *g);
float gg_mediana(GrafoGeral *g);

int gg_dfs_buscar(GrafoGeral *g, int inicio, int alvo);
int gg_bfs_buscar(GrafoGeral *g, int inicio, int alvo);

int gg_distancia(GrafoGeral *g, int origem, int destino);
int gg_diametro(GrafoGeral *g);

Componentes *gg_componentes_conexos(GrafoGeral *g);

void gg_gerar_relatorio(GrafoGeral *g, const char *arquivoSaida);

#endif
