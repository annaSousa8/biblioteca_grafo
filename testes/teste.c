#include <stdio.h>
#include "grafo.h"


int main(){
    Grafo *grafo = criarGrafo(6);
    
    exibir_grafo(grafo);

    add_elemento(grafo, 0 ,1);
    add_elemento(grafo, 0 ,4);
    add_elemento(grafo, 1 ,4);
    add_elemento(grafo, 2 ,4);
    add_elemento(grafo, 3 ,4);

    printf("\n");
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
    
    /*
    lerArquivo(grafo, "examples/grafo.txt"); 
    */

}