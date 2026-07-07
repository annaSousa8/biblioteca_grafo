
typedef struct Grafo
{
    int numVert;
    int **matriz;
} Grafo;

void exibir_grafo(Grafo *grafo);

void destruir_grafo(Grafo *grafo);

void add_elemento(Grafo *grafo, int linha, int coluna);

int numero_vertices(Grafo *grafo);

int numero_arestas(Grafo *grafo);

int grau_maior(Grafo *grafo);

int grau_menor(Grafo *grafo);

float grau_medio(Grafo *grafo);

float mediana(Grafo *grafo);

Grafo *criarGrafo(int numVert);

Grafo *ler_arquivo(const char *nomeArquivo);

void dfs_matriz(Grafo *grafo, int inicio, const char *arquivoSaida);

void bfs_matriz(Grafo *grafo, int inicio, const char *arquivoSaida);

int distancia(Grafo *grafo, int origem, int destino);

int diametro(Grafo *grafo);