#ifndef COMPONENTES_H
#define COMPONENTES_H

typedef struct {
    int numComponentes;
    int *tamanhos;
    int **vertices;
} Componentes;

void destruir_componentes(Componentes *comp);

#endif // !COMPONENTES_H
