#include "../scheduler.h"

int main (void){
    int i;
    DynamicArray *arrayD;
    char *toString;

    arrayD = initialize_array();
    for(i = 0; i < arrayD -> size; i++){
        toString = process_tostring(arrayD -> Darray[i], 1024);
        printf("%s", toString);
    }

    return 0;
}