#include <stddef.h>
#include "scheduler.h"

/* TODO: parse JSON from stdin and return queue of processes
 *       ordered by start time (earliest first) */
ProcessQueue* parse_JSON(void){
    ProcessQueue *queue = pq_create;
    int pid, creation_time, cpu_time_max, i, sizeTimes, sizeTypes;
    int *io_times, *io_types;
    char buffer[1024], *rest;
    char ch = '[';

    while (fgets(buffer, sizeof(buffer), stdin) != NULL){
        
        if (strstr(buffer, "pid") != NULL) {    
            sscanf(buffer, "\"pid\": %d,", &pid);

            fgets(buffer, sizeof(buffer), stdin); 
            sscanf(buffer, "\"creation_time\": %d,", &creation_time);

            fgets(buffer, sizeof(buffer), stdin); 
            sscanf(buffer, "\"cpu_time_max\": %d,", &cpu_time_max);

            fgets(buffer, sizeof(buffer), stdin); 
            rest = strchr(buffer, ch);
            rest[strlen(rest) - 3] = '\0';
            sizeTimes = get_size_array(rest);
            io_times = str_to_int_array(rest, sizeTimes);

            fgets(buffer, sizeof(buffer), stdin); 
            rest = strchr(buffer, ch);
            rest[strlen(rest) - 2] = '\0';
            sizeTypes = get_size_array(rest);
            io_types = str_to_int_array(rest, sizeTypes);

            if (sizeTypes != sizeTimes){
                printf("error: the number of io_times does not equal the amount of times io activates the OS\n");
                exit(1);
            }

            Process *p = process_create(pid, creation_time, cpu_time_max);
            
            for(i = 0; i < sizeTimes; i++){
                add_io_operation(p, io_times[i], io_types[i]);
            }

            pq_insert(p, queue);
        }
        else {
            continue;
        }
    }

    return queue;
}

int get_size_array(char *str){
    int count = 0;

    do {
        if (*str == ',')
            count++;
    } while (*(str++));

    count = count + 1;
    return count; 
}

int* str_to_int_array(char *str, int max){
    int num, i = 0;
    const char* token = strtok((char*)str, "[,");
    
    int* arr = malloc(sizeof(int) * max);
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    while (token != NULL) {
        num = atoi(token);
        arr[i] = num;

        token = strtok(NULL, ",]");
        i++;
    }

    return arr;
}