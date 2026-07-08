#include "merge_sort.h"
#include <stdlib.h>

void merge_sort(int *lista, int inicio, int fim){

    if(inicio<fim){
        int meio = (inicio+fim)/2;
        merge_sort(lista, inicio, meio);
        merge_sort(lista, meio+1, fim);
        merge(lista, inicio, meio, meio+1, fim);
    }
}

void merge(int *lista, int inicio1,int fim1, int inicio2, int fim2){
    int tam = fim2 - inicio1 +1;
    int *temp = (int *) malloc(sizeof(int)*tam);
    int i=inicio1, j=inicio2, k=0;
    while(i<=fim1 && j<=fim2){
        if(lista[i]<=lista[j])
            temp[k++] = lista[i++];
        else
            temp[k++] = lista[j++];
    }

    while(i<=fim1)
        temp[k++] = lista[i++];

    while(j<=fim1)
        temp[k++] = lista[j++];

    for(i=0;i<tam;i++)
        lista[inicio1 + i] = temp[i];

    free(temp);

}
