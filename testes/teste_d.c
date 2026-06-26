#include "grafo_d.h"
#include <stdio.h>

int main(){

    Grafo *g = criar_grafo(5);

    grafo_adicionar_no(g, 1, 2);
    grafo_adicionar_no(g, 2, 3);
    grafo_adicionar_no(g, 4, 5);
    grafo_adicionar_no(g, 4, 1);
    grafo_adicionar_no(g, 4, 3);
    //grafo_adicionar_no(g, 3, 4);
    //grafo_adicionar_no(g, 4, 5);
    //grafo_adicionar_no(g, 5, 1);

    grafo_mostrar(g);



    printf("\nO grafo possui %d arestas\n", grafo_num_arestas(g));
    printf("\nO grafo possui %d vertices\n", grafo_num_vertices(g));

    printf("\nA media do grafo eh %.2f\n", grafo_grau_medio(g));
    printf("\nA mediano do grafo eh %.2f\n", grafo_grau_mediano(g));


    printf("\nO grau minimo do grafo eh %d\n", grafo_grau_min(g));

    printf("\nO grau maximo do grafo eh %d\n", grafo_grau_max(g));


    grafo_limpar(g);

    lerArquivo(g, "./examples/grafo.txt");

    grafo_mostrar(g);



    printf("\nO grafo possui %d arestas\n", grafo_num_arestas(g));
    printf("\nO grafo possui %d vertices\n", grafo_num_vertices(g));

    printf("\nA media do grafo eh %.2f\n", grafo_grau_medio(g));
    printf("\nA mediano do grafo eh %.2f\n", grafo_grau_mediano(g));


    printf("\nO grau minimo do grafo eh %d\n", grafo_grau_min(g));

    printf("\nO grau maximo do grafo eh %d\n", grafo_grau_max(g));


    destroir(g);

    return 0;
}
