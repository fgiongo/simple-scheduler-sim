#ifndef STRINGBUFFER_H
#define STRINGBUFFER_H

#define MIN_STRING_LENGTH 1000
#define MAX_PERCENTAGE 75

typedef struct _STRINGBUFFER
{
    char* string;
    long int size;
}StringBuffer;

void initStringBuffer(StringBuffer* stringHTML, int initialSize);
void stringBufferOverflow(StringBuffer* stringHTML);
void saferConcat(StringBuffer* destination, StringBuffer* source);
void saferCopy(StringBuffer* destination, char* source);

#endif