#include "grafo_geral.h"
#include <stdlib.h>
#include <stdio.h>

GrafoGeral *criar_grafo_geral(TipoGrafo tipo, int numVert){
    GrafoGeral *g = (GrafoGeral *) malloc(sizeof(GrafoGeral));
    g->tipo = tipo;
    g->grafoMatriz = NULL;
    g->grafoLista = NULL;

    if(tipo == MATRIZ){
        g->grafoMatriz = criarGrafo(numVert);
    } else {
        g->grafoLista = criar_grafo(numVert);
    }

    return g;
}

GrafoGeral *ler_grafo_geral(TipoGrafo tipo, const char *nomeArquivo){
    GrafoGeral *g = (GrafoGeral *) malloc(sizeof(GrafoGeral));
    g->tipo = tipo;
    g->grafoMatriz = NULL;
    g->grafoLista = NULL;

    if(tipo == MATRIZ){
        g->grafoMatriz = ler_arquivo(nomeArquivo);
        if(g->grafoMatriz == NULL){
            free(g);
            return NULL;
        }
    } else {
        FILE *arquivo = fopen(nomeArquivo, "r");
        if(arquivo == NULL){
            printf("Erro ao abrir arquivo!\n");
            free(g);
            return NULL;
        }
        int numVert;
        fscanf(arquivo, "%d", &numVert);
        fclose(arquivo);

        g->grafoLista = criar_grafo(numVert);
        lerArquivo(g->grafoLista, nomeArquivo);
    }

    return g;
}

void destruir_grafo_geral(GrafoGeral *g){
    if(g->tipo == MATRIZ){
        destruir_grafo(g->grafoMatriz);
    } else {
        destroir(g->grafoLista);
    }
    free(g);
}

/* recebe vertices 1-indexados (mesmo padrao usado nos arquivos de entrada) */
int gg_adicionar_aresta(GrafoGeral *g, int v1, int v2){
    if(g->tipo == MATRIZ){
        add_elemento(g->grafoMatriz, v1 - 1, v2 - 1);
        return 1;
    }
    return grafo_adicionar_no(g->grafoLista, v1, v2);
}

int gg_numero_vertices(GrafoGeral *g){
    if(g->tipo == MATRIZ)
        return numero_vertices(g->grafoMatriz);
    return grafo_num_vertices(g->grafoLista);
}

int gg_numero_arestas(GrafoGeral *g){
    if(g->tipo == MATRIZ)
        return numero_arestas(g->grafoMatriz);
    return grafo_num_arestas(g->grafoLista);
}

int gg_grau_menor(GrafoGeral *g){
    if(g->tipo == MATRIZ)
        return grau_menor(g->grafoMatriz);
    return grafo_grau_min(g->grafoLista);
}

int gg_grau_maior(GrafoGeral *g){
    if(g->tipo == MATRIZ)
        return grau_maior(g->grafoMatriz);
    return grafo_grau_max(g->grafoLista);
}

float gg_grau_medio(GrafoGeral *g){
    if(g->tipo == MATRIZ)
        return grau_medio(g->grafoMatriz);
    return grafo_grau_medio(g->grafoLista);
}

float gg_mediana(GrafoGeral *g){
    if(g->tipo == MATRIZ)
        return mediana(g->grafoMatriz);
    return grafo_grau_mediano(g->grafoLista);
}

void gg_dfs_arvore(GrafoGeral *g, int inicio, const char *arquivoSaida){
    if(g->tipo == MATRIZ)
        dfs_matriz(g->grafoMatriz, inicio, arquivoSaida);
    else
        dfs_arvore(g->grafoLista, inicio, arquivoSaida);
}

void gg_bfs_arvore(GrafoGeral *g, int inicio, const char *arquivoSaida){
    if(g->tipo == MATRIZ)
        bfs_matriz(g->grafoMatriz, inicio, arquivoSaida);
    else
        bfs_arvore(g->grafoLista, inicio, arquivoSaida);
}

int gg_dfs_buscar(GrafoGeral *g, int inicio, int alvo){
    if(g->tipo == MATRIZ)
        return dfs_buscar(g->grafoMatriz, inicio, alvo);
    return grafo_dfs_buscar(g->grafoLista, inicio, alvo);
}


int gg_bfs_buscar(GrafoGeral *g, int inicio, int alvo){
    if(g->tipo == MATRIZ)
        return bfs_buscar(g->grafoMatriz, inicio, alvo);
    return grafo_bfs_buscar(g->grafoLista, inicio, alvo);
}

int gg_distancia(GrafoGeral *g, int origem, int destino){
    if(g->tipo == MATRIZ)
        return distancia(g->grafoMatriz, origem, destino);
    return grafo_distancia(g->grafoLista, origem, destino);
}

int gg_diametro(GrafoGeral *g){
    if(g->tipo == MATRIZ)
        return diametro(g->grafoMatriz);
    return grafo_diametro(g->grafoLista);
}

int gg_diametro_aproximado(GrafoGeral *g){
    if(g->tipo == MATRIZ)
        return -1;
    return diametro_aproximado(g->grafoLista);
}

Componentes *gg_componentes_conexos(GrafoGeral *g){
    if(g->tipo == MATRIZ)
        return componentes_conexos(g->grafoMatriz);
    return grafo_componentes_conexos(g->grafoLista);
}

void gg_gerar_relatorio(GrafoGeral *g, const char *arquivoSaida){
    if(g->tipo == MATRIZ)
        gerar_relatorio(g->grafoMatriz, arquivoSaida);
    else
        grafo_gerar_relatorio(g->grafoLista, arquivoSaida);
}
