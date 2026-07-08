#include "grafo_d.h"
#include "merge_sort.h"

#include <stdlib.h>
#include <stdio.h>

#include <time.h>


GrafoLista *criar_grafo(int tam) {
	Elem **lista = (Elem **) malloc(sizeof(Elem *)*tam);

	for(int i=0;i<tam;i++)
		lista[i] = NULL;

	GrafoLista *g = (GrafoLista *) malloc(sizeof(GrafoLista));

	g->lista = lista;
	g->tam = tam;

	return g;
}
void destroir( GrafoLista *g ){
    Elem *atual, *prox;

    for(int i=0; i<g->tam; i++){
        atual=g->lista[i];
        while(atual!=NULL){
            prox=atual->prox;
            free(atual);
            atual=prox;
        }
    }
    free(g->lista);
    free(g);
}


int grafo_adicionar_no(GrafoLista *g, int n1, int n2){

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


int grafo_num_arestas( GrafoLista *g){
    int totalVert=0;
    Elem *aux;

    for(int i=0;i<g->tam; i++)
        for(aux=g->lista[i];aux!=NULL;totalVert++, aux=aux->prox);

    return totalVert;
}
int grafo_num_vertices( GrafoLista *g){
    return g->tam;
}
int grafo_grau_min( GrafoLista *g){
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
int grafo_grau_max( GrafoLista *g){
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
float grafo_grau_medio(GrafoLista *g){
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
float grafo_grau_mediano(GrafoLista *g){
	int graus[g->tam];
	Elem *aux;
	for(int i=0;i<g->tam;i++){
		graus[i]=0;

		for(aux=g->lista[i];aux!=NULL;aux=aux->prox)
			graus[i]++;
	}

    merge_sort(graus, 0, g->tam-1);

    if(g->tam/2 != 0){
        return graus[g->tam/2];
    }

    return ((graus[g->tam/2]+graus[(g->tam/2)-1])/2.0);
}


void grafo_mostrar(GrafoLista *g){
	Elem *aux;
	for(int i=0;i<g->tam;i++){
		printf("No %d\n\t",i);

		for(aux=g->lista[i];aux!=NULL;aux=aux->prox)
			printf("%d ", aux->valor);

		printf("\n");
	}
}
void grafo_limpar(GrafoLista *g){
    Elem *atual, *prox;

    for(int i=0; i<g->tam; i++){
        atual=g->lista[i];
        while(atual!=NULL){
            prox=atual->prox;
            free(atual);
            atual=prox;
        }
        g->lista[i]=NULL;
    }
}


void lerArquivo(GrafoLista *g, const char *nomeArquivo){
    FILE *arquivo;
    int numVert, vert1, vert2;


    if((arquivo=fopen(nomeArquivo, "r"))==NULL){
        printf("\nErro ao abrir arquivo!");
        return;
    }
    fscanf(arquivo, "%d\n", &numVert);

    while (fscanf(arquivo, "%d %d\n", &vert1, &vert2) == 2){
        grafo_adicionar_no(g, vert1, vert2);
    }

    fclose(arquivo);
}

static void alg_dfs_arvore(GrafoLista *g, int idx, int nivel, int *pai, int *niveis, char *visitados){
    visitados[idx] = 'v';
    niveis[idx] = nivel;

    for(Elem *elem = g->lista[idx]; elem != NULL; elem = elem->prox){
        if(visitados[elem->valor] == 'n'){
            pai[elem->valor] = idx;
            alg_dfs_arvore(g, elem->valor, nivel + 1, pai, niveis, visitados);
        }
    }
}
void dfs_arvore(GrafoLista *g, int inicio, const char *arquivoSaida){
    FILE *saida = fopen(arquivoSaida, "w");
    if(saida == NULL){
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    int *pai = malloc(sizeof(int) * g->tam);
    int *niveis = malloc(sizeof(int) * g->tam);
    char *visitados = malloc(sizeof(char) * g->tam);

    for(int i=0; i<g->tam; i++){
        pai[i] = -1;
        niveis[i] = -1;
        visitados[i] = 'n';
    }

    alg_dfs_arvore(g, inicio, 0, pai, niveis, visitados);

    fprintf(saida, "VERTICE PAI NIVEL\n");
    for(int i=0; i<g->tam; i++){
        fprintf(saida, "%d %d %d\n", i+1, pai[i] == -1 ? 0 : pai[i]+1, niveis[i]);
    }

    fclose(saida);
    free(pai);
    free(niveis);
    free(visitados);
}
void bfs_arvore(GrafoLista *g, int inicio, const char *arquivoSaida){
    FILE *saida = fopen(arquivoSaida, "w");
    if(saida == NULL){
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    int *pai = malloc(sizeof(int) * g->tam);
    int *nivel = malloc(sizeof(int) * g->tam);
    char *visitados = malloc(sizeof(char) * g->tam);
    int *fila = malloc(sizeof(int) * g->tam);
    int ini = 0, fim = 0;

    for(int i=0; i<g->tam; i++){
        pai[i] = -1;
        nivel[i] = -1;
        visitados[i] = 'n';
    }

    visitados[inicio] = 'v';
    nivel[inicio] = 0;
    fila[fim++] = inicio;

    while(ini < fim){
        int atual = fila[ini++];
        for(Elem *elem = g->lista[atual]; elem != NULL; elem = elem->prox){
            if(visitados[elem->valor] == 'n'){
                visitados[elem->valor] = 'v';
                pai[elem->valor] = atual;
                nivel[elem->valor] = nivel[atual] + 1;
                fila[fim++] = elem->valor;
            }
        }
    }

    fprintf(saida, "VERTICE PAI NIVEL\n");
    for(int i=0; i<g->tam; i++){
        fprintf(saida, "%d %d %d\n", i+1, pai[i] == -1 ? 0 : pai[i]+1, nivel[i]);
    }

    fclose(saida);
    free(pai);
    free(nivel);
    free(visitados);
    free(fila);
}
int alg_dfs_buscar(GrafoLista *g, int idx, int alvo, char *visitados){
    if(idx == alvo)
        return 1;

    visitados[idx] = 'v';

    for(Elem *elem = g->lista[idx]; elem!=NULL; elem=elem->prox)
        if(visitados[elem->valor]=='n')
            if(alg_dfs_buscar(g, elem->valor, alvo, visitados))
                return 1;

    return 0;
}
int grafo_dfs_buscar(GrafoLista *g, int inicio, int alvo){
    char *visitados = (char*) malloc(sizeof(char)*g->tam);
    for(int i=0;i<g->tam;i++)
        visitados[i]='n';

    clock_t inicio_t = clock();
    int achou = alg_dfs_buscar(g, inicio, alvo, visitados);
    clock_t fim_t = clock();
    printf("Tempo: %f s\n", (double)(fim_t-inicio_t)/CLOCKS_PER_SEC);

    free(visitados);
    return achou;
}
void grafo_bfs_nivel(GrafoLista *g, int inicio, int *nivel){
    char *visitados = (char *) malloc(sizeof(char) * g->tam);
    int *fila = (int *) malloc(sizeof(int) * g->tam);
    int ini = 0, fim = 0;

    for(int i=0; i<g->tam; i++){
        visitados[i] = 'n';
        nivel[i] = -1;
    }

    visitados[inicio] = 'v';
    nivel[inicio] = 0;
    fila[fim++] = inicio;

    while(ini < fim){
        int atual = fila[ini++];
        for(Elem *elem = g->lista[atual]; elem!=NULL; elem=elem->prox){
            if(visitados[elem->valor] == 'n'){
                visitados[elem->valor] = 'v';
                nivel[elem->valor] = nivel[atual] + 1;
                fila[fim++] = elem->valor;
            }
        }
    }

    free(visitados);
    free(fila);
}
int grafo_bfs_buscar(GrafoLista *g, int inicio, int alvo){
    if(inicio == alvo){
        return 1;
    }

    char *visitados = (char *) malloc(sizeof(char) * g->tam);
    int *fila = (int *) malloc(sizeof(int) * g->tam);
    int ini = 0, fim = 0;

    for(int i=0; i<g->tam; i++)
        visitados[i] = 'n';

    visitados[inicio] = 'v';
    fila[fim++] = inicio;

    int achou = 0;
    clock_t inicio_t = clock();
    while(ini < fim && !achou){
        int atual = fila[ini++];
        for(Elem *elem = g->lista[atual]; elem!=NULL; elem=elem->prox){
            if(visitados[elem->valor] == 'n'){
                if(elem->valor == alvo){
                    achou = 1;
                    break;
                }
                visitados[elem->valor] = 'v';
                fila[fim++] = elem->valor;
            }
        }
    }
    clock_t fim_t = clock();
    printf("Tempo: %f s\n", (double)(fim_t-inicio_t)/CLOCKS_PER_SEC);

    free(visitados);
    free(fila);
    return achou;
}

void grafo_bfs_distancia(GrafoLista *g, int inicio, int *dist){
    int *fila = (int *) malloc(sizeof(int) * g->tam);
    if(fila == NULL)
        return;

    int ini = 0, fim = 0;

    for(int i=0; i<g->tam; i++)
        dist[i] = -1;

    fila[fim++] = inicio;
    dist[inicio] = 0;

    clock_t inicio_t = clock();
    while(ini < fim){
        int atual = fila[ini++];

        for(Elem *elem = g->lista[atual]; elem!=NULL; elem=elem->prox){
            if(dist[elem->valor] == -1){
                dist[elem->valor] = dist[atual] + 1;
                fila[fim++] = elem->valor;
            }
        }
    }
    clock_t fim_t = clock();
    printf("Tempo: %f s\n", (double)(fim_t-inicio_t)/CLOCKS_PER_SEC);

    free(fila);
}
int vertice_mais_distante(GrafoLista *g, int *dist) {
    int maior = -1;
    int indice = 0;

    for (int i = 0; i < g->tam; i++) {
        if (dist[i] > maior) {
            maior = dist[i];
            indice = i;
        }
    }

    return indice;
}
int diametro_aproximado(GrafoLista *g) {

    int *dist = (int *) malloc(sizeof(int) * g->tam);
    if(dist == NULL)
        return -1;

    // primeira BFS
    grafo_bfs_distancia(g, 0, dist);

    int u = vertice_mais_distante(g, dist);

    // segunda BFS
    grafo_bfs_distancia(g, u, dist);

    int v = vertice_mais_distante(g, dist);

    printf("u = %d\n", u);
    printf("v = %d\n", v);

    int diam = dist[v];

    free(dist);

    return diam;
}


int grafo_distancia(GrafoLista *g, int origem, int destino){
    int *nivel = (int *) malloc(sizeof(int) * g->tam);
    grafo_bfs_nivel(g, origem, nivel);
    int dist = nivel[destino];
    free(nivel);
    return dist;
}
int grafo_diametro(GrafoLista *g){
    int diam = 0;
    int *nivel = (int *) malloc(sizeof(int) * g->tam);

    for(int i=0;i<g->tam;i++){
        grafo_bfs_nivel(g, i, nivel);
        for(int j=0; j<g->tam; j++)
            if(nivel[j] > diam)
                diam = nivel[j];
    }

    free(nivel);
    return diam;
}


Componentes *grafo_componentes_conexos(GrafoLista *g){
    char *visitado = (char *) malloc(sizeof(char) * g->tam);
    for(int i=0; i<g->tam; i++){
        visitado[i] = 'n';
    }

    int *tamanhos = (int *) malloc(sizeof(int) * g->tam);
    int **vertices = (int **) malloc(sizeof(int *) * g->tam);
    int numComp = 0;

    int *fila = (int *) malloc(sizeof(int) * g->tam);

    for(int i=0; i<g->tam; i++){
        if(visitado[i] == 'n'){
            int ini = 0, fim = 0;
            fila[fim++] = i;
            visitado[i] = 'v';

            int *compVertices = (int *) malloc(sizeof(int) * g->tam);
            int tamComp = 0;

            while(ini < fim){
                int atual = fila[ini++];
                compVertices[tamComp++] = atual + 1; /* saida 1-indexada */

                for(Elem *elem = g->lista[atual]; elem!=NULL; elem=elem->prox){
                    if(visitado[elem->valor] == 'n'){
                        visitado[elem->valor] = 'v';
                        fila[fim++] = elem->valor;
                    }
                }
            }

            compVertices = (int *) realloc(compVertices, sizeof(int) * tamComp);
            vertices[numComp] = compVertices;
            tamanhos[numComp] = tamComp;
            numComp++;
        }
    }

    free(fila);
    free(visitado);

    for(int i=0; i<numComp-1; i++){
        int maior = i;
        for(int j=i+1; j<numComp; j++){
            if(tamanhos[j] > tamanhos[maior]){
                maior = j;
            }
        }
        if(maior != i){
            int tAux = tamanhos[i];
            tamanhos[i] = tamanhos[maior];
            tamanhos[maior] = tAux;

            int *vAux = vertices[i];
            vertices[i] = vertices[maior];
            vertices[maior] = vAux;
        }
    }

    Componentes *comp = (Componentes *) malloc(sizeof(Componentes));
    comp->numComponentes = numComp;
    comp->tamanhos = (int *) realloc(tamanhos, sizeof(int) * numComp);
    comp->vertices = (int **) realloc(vertices, sizeof(int *) * numComp);

    return comp;
}


void grafo_gerar_relatorio(GrafoLista *g, const char *arquivoSaida){
    FILE *saida = fopen(arquivoSaida, "w");
    if(saida == NULL){
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    fprintf(saida, "Numero de vertices: %d\n", grafo_num_vertices(g));
    fprintf(saida, "Numero de arestas: %d\n", grafo_num_arestas(g));
    fprintf(saida, "Grau minimo: %d\n", grafo_grau_min(g));
    fprintf(saida, "Grau maximo: %d\n", grafo_grau_max(g));
    fprintf(saida, "Grau medio: %.2f\n", grafo_grau_medio(g));
    fprintf(saida, "Mediana de grau: %.2f\n", grafo_grau_mediano(g));

    fclose(saida);
}
