#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

typedef struct _DYNAMICARRAYPID{
    int *array;
    int size;     /*Número de elementos no array*/
    int capacity; /*Capacidade total do array*/
} DynamicArrayPID;

void initDynamicArray(DynamicArrayPID *dynArray, int initialCapacity);
void pushDynamicArray(DynamicArrayPID *dynArray, int value);
void freeDynamicArray(DynamicArrayPID *dynArray);

#endif