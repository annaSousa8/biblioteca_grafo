#define NUMVERT 5

void exibir_grafo(int grafo[NUMVERT][NUMVERT]);

void add_elemento(int grafo[NUMVERT][NUMVERT], int linha, int coluna);

int numero_vertices();

int numero_arestas(int grafo[NUMVERT][NUMVERT]);

int grau_maior(int grafo[NUMVERT][NUMVERT]);

int grau_menor(int grafo[NUMVERT][NUMVERT]);

float grau_medio(int grafo[NUMVERT][NUMVERT]);

float mediana(int grafo[NUMVERT][NUMVERT]);