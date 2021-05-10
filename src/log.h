#include <stdio.h>

#ifndef LOG_DOT_H
#define LOG_DOT_H

void logHeader(FILE *fl_log);
void logFileInformation(FILE *fl_log, char* fileNameImport, char* fileNameExport, int switchASCIIorBINARY);

#endif