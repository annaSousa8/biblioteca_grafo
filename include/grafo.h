
typedef struct Grafo
{
    int numVert;
    int **matriz;
} Grafo;


void exibir_grafo(Grafo *grafo);

void add_elemento(Grafo *grafo, int linha, int coluna);

int numero_vertices(Grafo *grafo);

int numero_arestas(Grafo *grafo);

int grau_maior(Grafo *grafo);

int grau_menor(Grafo *grafo);

float grau_medio(Grafo *grafo);

float mediana(Grafo *grafo);

Grafo *criarMatriz(int numVert);

void lerArquivo(Grafo *grafo, const char *nomeArquivo);