#include <stdio.h>

#ifndef LOG_DOT_H    /* This is an "include guard" */
#define LOG_DOT_H    /* prevents the file from being included twice. */
                     /* Including a header file twice causes all kinds */
                     /* of interesting problems.*/

/**
 * This is a function declaration.
 * It tells the compiler that the function exists somewhere.
 */

void logHeader(FILE *fl_log);
void logFileInformation(FILE *fl_log, char* fileNameImport, char* fileNameExport);

#endif /* LOG_DOT_H */