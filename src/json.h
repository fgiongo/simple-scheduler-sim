#ifndef JSON_H
#define JSON_H

#include "queue.h"

ProcessQueue* parse_JSON(void);
int get_size_array(char *str);
int* str_to_int_array(char *str, int max);

#endif