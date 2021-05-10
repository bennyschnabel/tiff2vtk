#include "log.h"

/**
 * This is the function definition.
 * It is the actual body of the function which was declared elsewhere.
 */

// *******************
// * logHeader() *
// *******************

void logHeader(FILE *fl_log)
{
    fprintf(fl_log, "######################################################\n");
	fprintf(fl_log, "# tiff2vtk                                           #\n");
	fprintf(fl_log, "#                                                    #\n");
	fprintf(fl_log, "# Author: Benjamin Schnabel                          #\n");
	fprintf(fl_log, "# High Performance Computing Center Stuttgart (HLRS) #\n");
	fprintf(fl_log, "# Date: 2021.05.05                                   #\n");
	fprintf(fl_log, "######################################################\n\n");
}


void logFileInformation(FILE *fl_log, char* fileNameImport, char* fileNameExport)
{
    fprintf(fl_log, "Import file (*.TIFF): %s\n", fileNameImport);
    fprintf(fl_log, "Export file (*.VTK): %s\n", fileNameExport);
}