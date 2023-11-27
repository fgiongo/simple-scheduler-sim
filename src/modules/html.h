#ifndef HTML_H
#define HTML_H

#include "scheduler.h"

void getNumTrTd(int* tr, int* td, Graph data, DynamicArrayPID* pid);
void headBuilder(StringBuffer* stringHTML_Head);
void bodyBuilder(StringBuffer* stringHTML_body, int numTR, int numTD, Graph output_data, DynamicArrayPID arrayPID);

#endif