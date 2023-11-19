#ifndef JSON_H
#define JSON_H

#include "queue.h"

typedef struct _DynamicArray{
    int size;
    int capacity;
    Process **Darray;
} DynamicArray;


ProcessQueue* parse_JSON(void);
int get_size_array(char *str);
int* str_to_int_array(char *str, int max);
DynamicArray* initialize_array();
void increase_Darray_size(DynamicArray* _vector);
void insert_dynamic_array(Process *_process, DynamicArray* _vector);

#endif