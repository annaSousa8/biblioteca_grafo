#include "grafo_d.h"
#include "merge_sort.h"

#include <stdlib.h>
#include <stdio.h>


Grafo * criar_grafo(int tam) {
	Elem **lista = (Elem **) malloc(sizeof(Elem *)*tam);

	for(int i=0;i<tam;i++)
		lista[i] = NULL;

	Grafo *g = (Grafo *) malloc(sizeof(Grafo));

	g->lista = lista;
	g->tam = tam;

	return g;
}
void destroir( Grafo *g ){
    Elem *atual, *prox;
    printf("destroir\n");

    for(int i=0; i<5; i++){
        atual=g->lista[i];
        while(atual!=NULL){
            prox=atual->prox;
            free(atual);
            atual=prox;
        }
    }
    free(g);
}

int grafo_adicionar_no(Grafo *g, int n1, int n2){
	if(!((n1-1)>=0&&(n1-1)<g->tam)||!((n2-1)>=0&&(n2-1)<g->tam))
		return 0;

	Elem *elem2 = (Elem *) malloc(sizeof(Elem));

	elem2->valor = n2-1;
	elem2->prox = g->lista[n1-1];

	g->lista[n1-1] = elem2;

	Elem *elem1 = (Elem *) malloc(sizeof(Elem));

	elem1->valor = n1-1;
	elem1->prox = g->lista[n2-1];

	g->lista[n2-1] = elem1;

	return 1;
}

int grafo_num_arestas( Grafo *g);
int grafo_num_vertices( Grafo *g);

int grafo_grau_min( Grafo *g){
    int grau = -1;
    Elem *aux;

    for(int i=0;i<g->tam; i++){
        int cntg=0;
        for(aux=g->lista[i];aux!=NULL;cntg++, aux=aux->prox);
        if(cntg<grau||grau==-1)
            grau = cntg;
    }

    return grau;
}
int grafo_grau_max( Grafo *g){
    int grau = -1;
    Elem *aux;

    for(int i=0;i<g->tam; i++){
        int cntg=0;
        for(aux=g->lista[i];aux!=NULL;cntg++,aux=aux->prox);
        if(cntg>grau)
            grau = cntg;
    }

    return grau;
}
float grafo_grau_medio(Grafo *g){
	int graus[g->tam];
	int total=0;
	Elem *aux;
	for(int i=0;i<g->tam;i++){
		graus[i]=0;

		for(aux=g->lista[i];aux!=NULL;aux=aux->prox){
			graus[i]++;
			total++;
		}
	}

	return total/(float)g->tam;
}
float grafo_grau_mediano(Grafo *g){
	int graus[g->tam];
	Elem *aux;
	for(int i=0;i<g->tam;i++){
		graus[i]=0;

		for(aux=g->lista[i];aux!=NULL;aux=aux->prox)
			graus[i]++;
	}

    merge_sort(graus, 0, g->tam);

    if(g->tam/2>0){
        return graus[(g->tam/2)+1];
    }

    return ((graus[g->tam/2]+graus[(g->tam/2)+1])/2);
}

void grafo_mostrar(Grafo *g){
	Elem *aux;
	for(int i=0;i<g->tam;i++){
		printf("\nNo %d\n\t",i);

		for(aux=g->lista[i];aux!=NULL;aux=aux->prox)
			printf("%d ", aux->valor);

	}
}
void grafo_limpar(Grafo *g){
    Elem *atual, *prox;

    for(int i=0; i<5; i++){
        atual=g->lista[i];
        while(atual!=NULL){
            prox=atual->prox;
            free(atual);
            atual=prox;
        }
        g->lista[i]=NULL;
    }
}
