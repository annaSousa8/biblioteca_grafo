#include <stdio.h>
#include "grafo_geral.h"

static void testar(TipoGrafo tipo, const char *nome, const char *caminho){
    printf("=== Representacao: %s ===\n", nome);
    printf("%s\n", caminho);

    GrafoGeral *g = ler_grafo_geral(tipo, caminho);
    if(g == NULL){
        printf("Falha ao ler o grafo.\n");
        return;
    }

    printf("Numero de vertices: %d\n", gg_numero_vertices(g));
    /*
    printf("Numero de arestas: %d\n", gg_numero_arestas(g));
    printf("Grau minimo: %d\n", gg_grau_menor(g));
    printf("Grau maximo: %d\n", gg_grau_maior(g));
    printf("Grau medio: %.2f\n", gg_grau_medio(g));
    printf("Mediana de grau: %.2f\n", gg_mediana(g));

    printf("DFS busca 1 -> 4 (existe caminho?): %s\n", gg_dfs_buscar(g, 0, 3) ? "sim" : "nao");
    printf("BFS busca 1 -> 6 (existe caminho?): %s\n", gg_bfs_buscar(g, 0, 5) ? "sim" : "nao");

    printf("Distancia 1 -> 4: %d\n", gg_distancia(g, 0, 3));
    printf("Diametro (do componente alcancavel a partir de cada vertice): %d\n", gg_diametro(g));

    Componentes *comp = gg_componentes_conexos(g);
    printf("Numero de componentes conexos: %d\n", comp->numComponentes);
    for(int i=0; i<comp->numComponentes; i++){
        printf("  Componente %d (tamanho %d): ", i+1, comp->tamanhos[i]);
        for(int j=0; j<comp->tamanhos[i]; j++){
            printf("%d ", comp->vertices[i][j]);
        }
        printf("\n");
    }
    destruir_componentes(comp);

    char nomeRelatorio[64];
    sprintf(nomeRelatorio, "relatorio_%s.txt", nome);
    gg_gerar_relatorio(g, nomeRelatorio);
    printf("Relatorio salvo em %s\n", nomeRelatorio);
    */

    printf("parou\n");
    while(1)
    {
        if (getchar())
            break;
    }

    destruir_grafo_geral(g);
    printf("\n");
}

int main(void){
    //testar(MATRIZ, "matriz", "examples/grafo_3.txt");
    testar(LISTA, "lista", "examples/grafo_6.txt");
    return 0;
}
