#include <stdio.h>

#ifndef LOG_DOT_H
#define LOG_DOT_H

void logHeader(FILE *fl_log);
void logFileInformation(FILE *fl_log, char* fileNameImport, char* fileNameExport, int switchASCIIorBINARY);
void logTiffInformation(FILE *fl_log, int dims[3], float spcng[3], int spp, int bps, int comp, int pin);

#endif