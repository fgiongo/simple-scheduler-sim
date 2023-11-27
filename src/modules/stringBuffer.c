#include "scheduler.h"

void initStringBuffer(StringBuffer* stringHTML, int initialSize){
    stringHTML->size = initialSize;
    stringHTML->string = (char*) malloc(initialSize*sizeof(char));
    stringHTML->string[0] = '\0'; /*initialize a void string*/
}

void stringBufferOverflow(StringBuffer* stringHTML){
    stringHTML->size *= 2;
    stringHTML->string = (char*)realloc(stringHTML->string, stringHTML->size);
}

void saferConcat(StringBuffer* destination, StringBuffer* source){
    long int currentLength = strlen(destination->string);
    long int newLength = currentLength + strlen(source->string)+1;

    while((newLength*100/destination->size) >= MAX_PERCENTAGE){
        stringBufferOverflow(destination);  
    }

    strcat(destination->string, source->string);
}

void saferCopy(StringBuffer* destination, char* source){
    long int currentLength = strlen(destination->string);
    long int newLength = currentLength = strlen(source)+1;

    while((newLength*100/destination->size) >= MAX_PERCENTAGE){
        stringBufferOverflow(destination);  
    }

    strcpy(destination->string, source);
}

