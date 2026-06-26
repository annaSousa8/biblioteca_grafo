#include "merge_sort.h"

void merge_sort(int *lista, int inc, int fim){
    int meio = (inc+fim)/2;

    if(inc!=fim){
        merge_sort(lista, inc, meio);
        merge_sort(lista, meio+1, fim);
    }

    merge(lista, inc, meio, meio+1, fim);

}

void merge(int *lista, int inc_1,int fim_1, int inc_2, int fim_2){
    int i=inc_1, j=inc_2;
    while(i<=fim_2&&j<=fim_2){
        if(i==j){
            j++;
            continue;
        }
        if(lista[i]<lista[j]){
            swap(&(lista[i]), &(lista[j]));
            i++;
        }else
            i++;
    }
}

void swap(int *i, int *j){
    int aux = *j;
    *j=*i;
    *i=aux;
}
