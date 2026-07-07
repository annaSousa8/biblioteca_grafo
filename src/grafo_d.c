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
    elem2->visitado = 0;

	g->lista[n1-1] = elem2;

	Elem *elem1 = (Elem *) malloc(sizeof(Elem));

	elem1->valor = n1-1;
	elem1->prox = g->lista[n2-1];
    elem1->visitado = 0;

	g->lista[n2-1] = elem1;

	return 1;
}

int grafo_num_arestas( Grafo *g){
    return g->tam;
}
int grafo_num_vertices( Grafo *g){
    int totalVert=0;
    Elem *aux;

    for(int i=0;i<g->tam; i++)
        for(aux=g->lista[i];aux!=NULL;totalVert++, aux=aux->prox);

    return totalVert;
}

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

    merge_sort(graus, 0, g->tam-1);

    if(g->tam/2>0){
        return graus[g->tam/2];
    }

    return ((graus[g->tam/2]+graus[(g->tam/2)-1])/2);
}

void grafo_mostrar(Grafo *g){
	Elem *aux;
	for(int i=0;i<g->tam;i++){
		printf("No %d\n\t",i);

		for(aux=g->lista[i];aux!=NULL;aux=aux->prox)
			printf("%d ", aux->valor);

		printf("\n");
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

void lerArquivo(Grafo *g, const char *nomeArquivo){
    FILE *arquivo;
    int numVert, vert1, vert2;


    if((arquivo=fopen(nomeArquivo, "r"))==NULL){
        printf("\nErro ao abrir arquivo!");
    } else {
        fscanf(arquivo, "%d\n", &numVert);

        while (!feof(arquivo))
        {
            fscanf(arquivo, "%d %d\n", &vert1, &vert2);
            grafo_adicionar_no(g, vert1, vert2);
        }
    }
}

void dfs(Grafo *g, int idx){
    char *visitados = (char*) malloc(sizeof(char)*g->tam);
    for(int i=0;i<g->tam;i++)
        visitados[i]='n';
    alg_dfs(g, idx, 0, visitados);
}

void alg_dfs(Grafo *g, int idx, int nvl, char *visitados){

    printf("%d %d\n", idx, nvl);
    visitados[idx] = 'v';


    for(Elem *elem = g->lista[idx];elem!=NULL;elem=elem->prox){
        if(visitados[elem->valor]=='n')
            alg_dfs(g,elem->valor, nvl+1, visitados);
    }

}

int bfs(Grafo *g, int idx){
    int *visitados = (int*) malloc(sizeof(int)*g->tam);
    for(int i=0;i<g->tam;i++)
        visitados[i]=-1;

    int *ordem = (int *) malloc(sizeof(int)*g->tam);
    for(int i=0;i<g->tam;i++)
        ordem[i]=0;

    ordem[0]=idx;
    visitados[idx] = 0;
    return alg_bfs(g, visitados, ordem);
}

int alg_bfs(Grafo *g, int *visitados, int *ordem){
    int i=0, j=1, nvl=0;

    do{
        printf("\t%d %d\n", ordem[i], visitados[ordem[i]]);
        if(visitados[ordem[i]]==0)
            nvl = nvl+1;

        for(Elem *elem = g->lista[ordem[i++]];elem!=NULL;elem=elem->prox){
            if(visitados[elem->valor]<0){
                ordem[j++] = elem->valor;
                visitados[elem->valor] = nvl;
            }
        }
    }while(i<j);

    return nvl;
}

int diametro(Grafo *g){
    int diametro = 0;

    for(int i=0;i<g->tam;i++){
        int dist = bfs(g, i);
        printf("i=%d dist=%d\n", i, dist);
        if(diametro<dist)
            diametro = dist;
    }

    return diametro;

}




