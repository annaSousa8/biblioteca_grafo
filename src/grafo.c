#include <stdio.h>
#define NUMVERT 5
 
void exibir_grafo(int grafo[NUMVERT][NUMVERT]){
    for(int i=0; i<NUMVERT; i++){
        for(int j=0; j<NUMVERT; j++){
            printf(" %d ", grafo[i][j]);
        }
        printf("\n");
    }
}

void add_elemento(int grafo[NUMVERT][NUMVERT], int linha, int coluna){
    grafo[linha][coluna] = 1;
    grafo[coluna][linha] = 1;
}

int numero_vertices(){}

int numero_arestas(int grafo[NUMVERT][NUMVERT]){
    int cont  = 0, dp = 0, num_arestas = 0;
    for(int i=0; i<NUMVERT; i++){
        for(int j=0; j<NUMVERT; j++){
            if(grafo[i][j] == 1 && i != j){
                cont++;
            }
            if(i == j && grafo[i][j]==1){
                dp++;
            }
        }
    }
    //printf("% d, diagonal: %d", cont, dp);
    num_arestas = (cont/2)+dp;
    return(num_arestas);
}

int grau_maior(int grafo[NUMVERT][NUMVERT]){
    int aux, maior = 0, pos_maior = 0;
    for(int i=0; i<NUMVERT; i++){
        aux = 0;
        for(int j=0; j<NUMVERT; j++){
            if(grafo[i][j] == 1){
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

int grau_menor(int grafo[NUMVERT][NUMVERT]){
    int aux, menor = NUMVERT, pos_menor = 0;
    for(int i=0; i<NUMVERT; i++){
        aux = 0;
        for(int j=0; j<NUMVERT; j++){
            if(grafo[i][j] == 1){
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

float grau_medio(int grafo[NUMVERT][NUMVERT]){
    float cont=0, grau=0;
    for(int i=0; i<NUMVERT; i++){
        for(int j=0; j<NUMVERT; j++){
            if(grafo[i][j] == 1){
                cont++;
            }
        }
    }
    grau = cont/NUMVERT;
    return(grau);
}

float mediana(int grafo[NUMVERT][NUMVERT]){
    int graus[NUMVERT];
    int aux;

    for(int i=0; i<NUMVERT; i++){
        graus[i] = 0;
        for(int j=0; j<NUMVERT; j++){
            if(grafo[i][j] == 1){
                graus[i]++;
            }
        }
    }

    for(int i=0; i<NUMVERT-1; i++){
        for(int j=i+1; j<NUMVERT; j++){
            if(graus[i] > graus[j]){
                aux = graus[i];
                graus[i] = graus[j];
                graus[j] = aux;
            }
        }
    }

    for(int i=0; i<NUMVERT; i++){
    printf("%d ", graus[i]);
    }
    printf("\n");

    if(NUMVERT % 2 != 0){
        return(graus[NUMVERT/2]);
    }
    else{
        return((graus[NUMVERT/2] + graus[(NUMVERT/2)-1])/2.0);
    }
}