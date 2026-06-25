#include "merge_sort.h"

void merge_sort(int *lista, int inc, int fim){
    if(inc!=fim){
        int meio = (inc+fim)/2;
        merge_sort(lista, inc, meio);
        merge_sort(lista, meio+1, fim);
    }

    merge(lista, inc, fim);

}

void merge(int *lista, int inc, int fim){
    int i=inc, j=fim+1;
    while(i<=inc||j<=fim){
        if(lista[i]<lista[j]){
            swap(&(lista[i]), &(lista[j]));
            j++;
        }else{
            i++;
        }
    }
}

void swap(int *i, int *j){
    int aux = *j;
    *j=*i;
    *i=aux;
}
