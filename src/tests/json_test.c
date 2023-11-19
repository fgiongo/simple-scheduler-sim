#include "../scheduler.h"

int main (void){
    int i;
    DynamicArray *arrayD;
    char *toString;

    ProcessQueue* queue;
    arrayD = initialize_array();
    queue = parse_JSON(arrayD);

    for(i = 0; i < arrayD -> size; i++){
        toString = process_tostring(arrayD -> Darray[i], 1024);
        printf("%s", toString);
    }

    return 0;
}