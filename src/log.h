#include <stdio.h>
#include <time.h>

#ifndef LOG_DOT_H
#define LOG_DOT_H

void logHeader(FILE *fl_log);
void logFileInformation(FILE *fl_log, char* fileNameImport, char* fileNameExport, int switchASCIIorBINARY);
void logTiffInformation(FILE *fl_log, int dims[3], float spcng[3], int spp, int bps, int comp, int pin);
void logCalculationTime(FILE *fl_log, double cpu_time_used);

#endif