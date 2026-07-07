#include <stdio.h>
#include "grafo.h"


int main(){    
    Grafo *grafo = ler_arquivo("examples/grafo.txt");
    if(grafo == NULL){
        return 1;
    }

    exibir_grafo(grafo);

    int vert = numero_vertices(grafo);
    printf("\nNumero de vertices: %d", vert);

    int num_arestas = numero_arestas(grafo);
    printf("\nNumero de arestas: %d", num_arestas);

    int gmaior = grau_maior(grafo);
    printf("\nGrau maximo: %d", gmaior);

    int gmenor = grau_menor(grafo);
    printf("\nGrau minimo: %d", gmenor);

    float g = grau_medio(grafo);
    printf("\nGrau medio: %f", g);

    float med = mediana(grafo);
    printf("\nMediana dos graus: %.3f", med);
}