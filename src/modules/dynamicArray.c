#include "scheduler.h"

void initDynamicArray(DynamicArrayPID *dynArray, int initialCapacity) {
    dynArray->array = (int *)malloc(initialCapacity * sizeof(int));
    if (dynArray->array == NULL) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        exit(EXIT_FAILURE);
    }
    dynArray->size = 0;
    dynArray->capacity = initialCapacity;
}

void pushDynamicArray(DynamicArrayPID *dynArray, int value) {

    int i; 

    if (dynArray->size == dynArray->capacity) {
        dynArray->capacity *= 2;
        dynArray->array = (int *)realloc(dynArray->array, dynArray->capacity * sizeof(int));
        if (dynArray->array == NULL) {
            fprintf(stderr, "Erro de realocação de memória.\n");
            exit(EXIT_FAILURE);
        }
    }

    for(i = 0; i < dynArray->size; i++){
        if(value != dynArray->array[i]){
            continue;
        }else{
            break;
        }
    }

    if(i == dynArray->size){
        dynArray->array[dynArray->size] = value;
        dynArray->size++;
    }
}

void freeDynamicArray(DynamicArrayPID *dynArray) {
    free(dynArray->array);
    dynArray->array = NULL;
    dynArray->size = 0;
    dynArray->capacity = 0;
}