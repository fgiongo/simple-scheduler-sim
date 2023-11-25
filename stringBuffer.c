#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_STRING_LENGTH 1000
#define MAX_PERCENTAGE 75

typedef struct _STRINGBUFFER
{
    char* string;
    long int size;
}StringBuffer;


void headBuilder(StringBuffer* stringHTML_Head);
void bodyBuilder(StringBuffer* stringHTML_body, int numTR, int numTD);
void initStringBuffer(StringBuffer* stringHTML, int initialSize);
void overflow(StringBuffer* stringHTML);
void saferConcat(StringBuffer* destination, StringBuffer* source);
void saferCopy(StringBuffer* destination, char* source);


int main(void){

    StringBuffer stringHTML;
    StringBuffer stringHTML_Head;
    StringBuffer stringHTML_Body;
    initStringBuffer(&stringHTML, MIN_STRING_LENGTH);
    initStringBuffer(&stringHTML_Head, MIN_STRING_LENGTH);
    initStringBuffer(&stringHTML_Body, MIN_STRING_LENGTH);

    headBuilder(&stringHTML_Head);
    printf("%s\n", stringHTML_Head.string);
    
    bodyBuilder(&stringHTML_Body, 3, 3);
    printf("%s\n", stringHTML_Body.string);
   /* saferCopy(&stringHTML, stringHTML_Head.string);
    saferConcat(&stringHTML, &stringHTML_Body);

    printf("%s\n", stringHTML.string);*/

    return 0;

}


void initStringBuffer(StringBuffer* stringHTML, int initialSize){
    stringHTML->size = initialSize;
    stringHTML->string = (char*) malloc(initialSize*sizeof(char));
    stringHTML->string[0] = '\0'; /*initialize a void string*/
}

void overflow(StringBuffer* stringHTML){
    stringHTML->size *= 2;
    stringHTML->string = (char*)realloc(stringHTML->string, stringHTML->size);
}

void saferConcat(StringBuffer* destination, StringBuffer* source){
    long int currentLength = strlen(destination->string);
    long int newLength = currentLength + strlen(source->string)+1;

    while((newLength*100/destination->size) >= MAX_PERCENTAGE){
        overflow(destination);  
    }

    strcat(destination->string, source->string);
}

void saferCopy(StringBuffer* destination, char* source){
    long int currentLength = strlen(destination->string);
    long int newLength = currentLength = strlen(source)+1;

    while((newLength*100/destination->size) >= MAX_PERCENTAGE){
        overflow(destination);  
    }

    strcpy(destination->string, source);
}

void bodyBuilder(StringBuffer* stringHTML_body, int numTR, int numTD){

    StringBuffer temporaryString;
    int i = 0;
    int j;
    initStringBuffer(&temporaryString, MIN_STRING_LENGTH);

    saferCopy(stringHTML_body,
        "<body>\n"
        "   <table>\n");
    
    while(i < numTR){
        saferCopy(&temporaryString, "       <tr>\n");
        saferConcat(stringHTML_body, &temporaryString);

        j = 0;

        while(j < numTD){
            saferCopy(&temporaryString, "           <td>"
                                        "</td>\n");
            saferConcat(stringHTML_body, &temporaryString);
            j++;
        }
        saferCopy(&temporaryString, "       </tr>\n");
        saferConcat(stringHTML_body, &temporaryString);
        i++;
    }

    saferCopy(&temporaryString, 
                        "   </table>\n"
                        "</body>\n"
                        "</html>\n");
    saferConcat(stringHTML_body, &temporaryString);

    free(temporaryString.string);
}


void headBuilder(StringBuffer* stringHTML_Head) {

    StringBuffer temporaryString;
    initStringBuffer(&temporaryString, MIN_STRING_LENGTH);

    strcpy(stringHTML_Head->string, "<!DOCTYPE html>\n"
                             "<html lang=\"en\">\n"
                             "<head>\n"
                             "    <meta charset=\"UTF-8\">\n"
                             "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
                             );

    saferCopy(&temporaryString, "    <style>\n"
                             "        /* Add some basic styling to the table */\n"
                             "        table {\n"
                             "            font-family: Arial, sans-serif;\n"
                             "            border-collapse: collapse;\n"
                             "            width: 50%;\n"
                             "            margin: 20px;\n"
                             "        }\n"
                             "\n"
                             "        th, td {\n"
                             "            border: 1px solid #dddddd;\n"
                             "            text-align: left;\n"
                             "            padding: 8px;\n"
                             "        }\n"
                             "\n"
                             "        th {\n"
                             "            background-color: #f2f2f2;\n"
                             "        }\n"
                             "    </style>\n"
                             "    <title>String Buffer to HTML</title>\n"
                             "</head>");

    saferConcat(stringHTML_Head, &temporaryString);

    free(temporaryString.string);
}