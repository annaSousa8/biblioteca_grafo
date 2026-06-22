#include <stdio.h>
#include "grafo.h"
#define NUMVERT 5

int main(){
    int grafo[NUMVERT][NUMVERT] = {{0, 1, 0, 0, 1},
                                   {1, 0, 1, 1, 0},
                                   {0, 1, 0, 0, 0}, 
                                   {0, 1, 0, 0, 1},
                                   {1, 0, 0, 1, 0}
                                };
    
    add_elemento(grafo, 4 ,1);
    add_elemento(grafo, 4 ,2);

    exibir_grafo(grafo);

    int num_arestas = numero_arestas(grafo);
    printf("\nNumero de arestas: %d", num_arestas);

    int gmaior = grau_maior(grafo);
    printf("\nGrau maximo: %d", gmaior);

    int gmenor = grau_menor(grafo);
    printf("\nGrau minimo: %d", gmenor);

    float g = grau_medio(grafo);
    printf("\nGrau medio: %f", g);

    float med = mediana(grafo);
    printf("\nMediana dos graus: %.f", med);
}