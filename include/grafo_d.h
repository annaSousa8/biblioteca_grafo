typedef struct elem{
    int valor;
    struct elem *prox;
}Elem;

typedef struct grafo{
    Elem **lista;
    int tam;
}Grafo;

Grafo * criar_grafo(int tam);
void destroir( Grafo *g );

int grafo_adicionar_no(Grafo *g, int n1, int n2);

int grafo_num_arestas( Grafo *g);
int grafo_num_vertices( Grafo *g);

int grafo_grau_min( Grafo *g);
int grafo_grau_max( Grafo *g);
float grafo_grau_medio(Grafo *g);
float grafo_grau_mediano(Grafo *g);

void grafo_mostrar(Grafo *g);
void grafo_limpar(Grafo *g);

void lerArquivo(Grafo *grafo, const char *nomeArquivo);
