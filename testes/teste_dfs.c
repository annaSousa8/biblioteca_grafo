#include "grafo_d.h"
#include <stdio.h>

int main(){

    Grafo *g = criar_grafo(5);

    lerArquivo(g, "./examples/grafo.txt");

    grafo_mostrar(g);

    dfs(g, 0);

    destroir(g);

    return 0;
}
