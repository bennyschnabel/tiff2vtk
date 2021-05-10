#include "log.h"

// ***************************
// * logHeader(FILE *fl_log) *
// ***************************

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

// *********************************************************************************************************
// * logFileInformation(FILE *fl_log, char* fileNameImport, char* fileNameExport, int switchASCIIorBINARY) *
// *********************************************************************************************************

void logFileInformation(FILE *fl_log, char* fileNameImport, char* fileNameExport, int switchASCIIorBINARY)
{
    fprintf(fl_log, "Import file (*.TIFF): %s\n", fileNameImport);
    fprintf(fl_log, "Export file (*.VTK): %s\n", fileNameExport);
    if(switchASCIIorBINARY == 0)
    {
        fprintf(fl_log, "Data of the *.VTK file are saved in ASCII format\n");
    }
    else if(switchASCIIorBINARY == 1)
    {
        fprintf(fl_log, "Data of the *.VTK file are saved in BINARY format\n");
    }
    else
    {
        fprintf(fl_log, "Data of the *.VTK file are saved in ASCII format\n\n");
    }
}