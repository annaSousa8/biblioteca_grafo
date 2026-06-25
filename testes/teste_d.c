#include "grafo_d.h"
#include <stdio.h>

int main(){

    Grafo *g = criar_grafo(5);

    grafo_adicionar_no(g, 1, 2);
    grafo_adicionar_no(g, 2, 3);
    grafo_adicionar_no(g, 4, 5);
    //grafo_adicionar_no(g, 3, 4);
    //grafo_adicionar_no(g, 4, 5);
    //grafo_adicionar_no(g, 5, 1);

    grafo_mostrar(g);

    printf("\nA media do grafo eh %.2f\n", grafo_grau_medio(g));

    printf("\nA mediano do grafo eh %.2f\n", grafo_grau_mediano(g));


    destroir(g);

    return 0;
}
