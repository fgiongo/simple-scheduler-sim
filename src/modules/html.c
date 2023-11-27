#include "scheduler.h"


void getNumTrTd(int* tr, int* td, Graph data, DynamicArrayPID* pid){
    int i;

    for(i = 0; i < data.n_elem; i++){
        pushDynamicArray(pid, data.pid[i]);
        (*td) = (int) data.time[i];
    }

    (*tr) = (int) (*pid).size;
}

void bodyBuilder(StringBuffer* stringHTML_body, int numTR, int numTD, Graph output_data, DynamicArrayPID arrayPID){

    StringBuffer temporaryString;
    int i = 0;
    int j, k;
    initStringBuffer(&temporaryString, MIN_STRING_LENGTH);

    saferCopy(stringHTML_body,
        "<body>\n"
        "<h2>Simple Process Scheduler Simulator</h2>\n"
        "<h4>by Fernando Giongo, Matheus Hack and Samuel Sampaio\n"
        "   <table>\n");
    
    while(i < numTR){
        saferCopy(&temporaryString, "       <tr>\n");
        saferConcat(stringHTML_body, &temporaryString);

        saferCopy(&temporaryString, "           <td class=\"legenda\">");
        saferConcat(stringHTML_body, &temporaryString);

        sprintf(temporaryString.string, " Processo: %d ", arrayPID.array[i]);
        saferConcat(stringHTML_body, &temporaryString);

        saferCopy(&temporaryString, "           </td>\n");
        saferConcat(stringHTML_body, &temporaryString);
        

        j = 0;
        while(j <= numTD){

            int found = 0;

            for(k = 0; k < output_data.n_elem; k++){
                if(output_data.pid[k] == arrayPID.array[i] && output_data.time[k] == j){
                    found = 1;
                    break;
                }
            }

            if (found) {
                saferCopy(&temporaryString, "           <td class=\"pintar\">#</td>\n");
            } else {
                saferCopy(&temporaryString, "           <td></td>\n");
            }

            saferConcat(stringHTML_body, &temporaryString);
            j++;

        }
        saferCopy(&temporaryString, "       </tr>\n");
        saferConcat(stringHTML_body, &temporaryString);
        i++;
    }

    saferCopy(&temporaryString, "       <tr class=\"legenda\">\n");
    saferConcat(stringHTML_body, &temporaryString);

    saferCopy(&temporaryString, "           <td></td>\n");
    saferConcat(stringHTML_body, &temporaryString);

    for(j = 0; j <= numTD; j++){
        saferCopy(&temporaryString, "           <td class=\"legenda\">");
        saferConcat(stringHTML_body, &temporaryString); 

        sprintf(temporaryString.string, " %d ", j);
        saferConcat(stringHTML_body, &temporaryString);

        saferCopy(&temporaryString, "           </td>\n");
        saferConcat(stringHTML_body, &temporaryString); 
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
                             "            font-family: monospace;\n"
                             "            font-size: 1.3em;\n"
                             "            border-collapse: collapse;\n"
                             "        }\n"
                             "\n"
                             "        tr, td {\n"
                             "            border: 1px solid black;\n"
                             "            text-align: center;\n"
                             "            padding: 8px;\n"
                             "        }\n"
                             "\n");

    saferConcat(stringHTML_Head, &temporaryString);

    saferCopy(&temporaryString, 
                             "        tr {\n"
                             "            background-color: #f2f2f2;\n"
                             "            width: 100px;\n"
                             "        }\n"
                             "        .legenda{\n"
                             "             background-color: #D0D0D0;\n"
                             "             font-weight: bold;\n"
                             "        }\n"
                             "        .pintar{\n"
                             "             background-color: #187bcd;\n"
                             "             color: #187bcd;\n"
                             "        }\n"
                             "        h2, h4{\n"
                             "             margin-left: 20px;\n"
                             "        }" 
                             "    </style>\n"
                             "    <title>String Buffer to HTML</title>\n"
                             "</head>");
    saferConcat(stringHTML_Head, &temporaryString);

    free(temporaryString.string);
}