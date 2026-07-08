#include "componentes.h"
#include <stdlib.h>

void destruir_componentes(Componentes *comp){
    for(int i=0; i<comp->numComponentes; i++){
        free(comp->vertices[i]);
    }

    free(comp->vertices);
    free(comp->tamanhos);
    free(comp);
}
