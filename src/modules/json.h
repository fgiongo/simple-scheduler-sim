#ifndef JSON_H
#define JSON_H

#include "queue.h"

typedef struct _DynamicArray{
    int size;
    int capacity;
    Process **Darray;
} DynamicArray;


ProcessQueue* parse_JSON(void);
int get_size_array_int(char*);
int get_size_array_str(char*);
int* str_to_int_array(char*, int);
DynamicArray* initialize_array(void);
void increase_Darray_size(DynamicArray*);
void insert_dynamic_array(Process*, DynamicArray*);
int* map_io_to_numbers(char*, int);
void check_whitespace(char* str);

#endif
