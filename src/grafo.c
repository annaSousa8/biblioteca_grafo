#include <stdio.h>
#include "grafo.h"
#include <stdlib.h>
 
/*
void exibir_grafo(Grafo *grafo){
    for(int i=0; i<grafo->numVert; i++){
        for(int j=0; j<grafo->numVert; j++){
            printf(" %d ", (grafo->matriz)[i][j]);
        }
        printf("\n");
    }
}

void add_elemento(Grafo *grafo, int linha, int coluna){
    grafo->matriz[linha][coluna] = 1;
    grafo->matriz[coluna][linha] = 1;
}

int numero_vertices(Grafo *grafo){
    return grafo->numVert;
}

int numero_arestas(Grafo *grafo){
    int cont  = 0, dp = 0, num_arestas = 0;
    for(int i=0; i<grafo->numVert; i++){
        for(int j=0; j<grafo->numVert; j++){
            if(grafo->matriz[i][j] == 1 && i != j){
                cont++;
            }
            if(i == j && grafo->matriz[i][j]==1){
                dp++;
            }
        }
    }
    //printf("% d, diagonal: %d", cont, dp);
    num_arestas = (cont/2)+dp;
    return(num_arestas);
}

int grau_maior(Grafo *grafo){
    int aux, maior = 0, pos_maior = 0;
    for(int i=0; i<grafo->numVert; i++){
        aux = 0;
        for(int j=0; j<grafo->numVert; j++){
            if(grafo->matriz[i][j] == 1){
                aux++;
            }
        }
        if(aux>maior){
            maior = aux;
            pos_maior = i;
        }
    }
    return(maior);
}

int grau_menor(Grafo *grafo){
    int aux, menor = grafo->numVert, pos_menor = 0;
    for(int i=0; i<grafo->numVert; i++){
        aux = 0;
        for(int j=0; j<grafo->numVert; j++){
            if(grafo->matriz[i][j] == 1){
                aux++;
            }
        }
        if(aux<menor){
            menor = aux;
            pos_menor = i;
        }
    }
    return(menor);
}

float grau_medio(Grafo *grafo){
    float cont=0, grau=0;
    for(int i=0; i<grafo->numVert; i++){
        for(int j=0; j<grafo->numVert; j++){
            if(grafo->matriz[i][j] == 1){
                cont++;
            }
        }
    }
    grau = cont/grafo->numVert;
    return(grau);
}

float mediana(Grafo *grafo){
    int graus[grafo->numVert];
    int aux;

    for(int i=0; i<grafo->numVert; i++){
        graus[i] = 0;
        for(int j=0; j<grafo->numVert; j++){
            if(grafo->matriz[i][j] == 1){
                graus[i]++;
            }
        }
    }

    for(int i=0; i<grafo->numVert-1; i++){
        for(int j=i+1; j<grafo->numVert; j++){
            if(graus[i] > graus[j]){
                aux = graus[i];
                graus[i] = graus[j];
                graus[j] = aux;
            }
        }
    }

    for(int i=0; i<grafo->numVert; i++){
    printf("%d ", graus[i]);
    }
    printf("\n");

    if(grafo->numVert % 2 != 0){
        return(graus[grafo->numVert/2]);
    }
    else{
        return((graus[grafo->numVert/2] + graus[(grafo->numVert/2)-1])/2.0);
    }
}

*/
Grafo *criarMatriz(int numVert){
    Grafo *grafo = (Grafo *) malloc(sizeof(Grafo));

    grafo->numVert = numVert;

    for(int i=0; i<numVert; i++){
        for(int j=0; j<numVert; j++){
            printf("teste 0\n");

            grafo->matriz[i][j] = 0;
            printf("teste 1\n");
        }
    }

    return grafo;
}
/*
void lerArquivo(Grafo *grafo, const char *nomeArquivo){
    FILE *arquivo;
    int numVert, vert1, vert2;
   
    if((arquivo=fopen(nomeArquivo, "r"))==NULL){
        printf("\nErro ao abrir arquivo!");
    } else {
        fscanf(arquivo, "%d\n", &numVert);
        //matriz = criarMatriz(numVert);
        
        while (!feof(arquivo))
        {
            fscanf(arquivo, "%d %d\n", &vert1, &vert2);
            add_elemento(grafo, vert1-1, vert2-1);
        }
    }
}
*/

