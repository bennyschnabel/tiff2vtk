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

    time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	fprintf(fl_log, "Date: %d-%02d-%02d %02d:%02d:%02d\n\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
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
		fprintf(fl_log, "Data of the *.VTK file are saved in ASCII format\n\n");
	}
	else if(switchASCIIorBINARY == 1)
	{
		fprintf(fl_log, "Data of the *.VTK file are saved in BINARY format\n\n");
	}
	else
	{
		fprintf(fl_log, "Data of the *.VTK file are saved in ASCII format\n\n");
	}
}

// *************************************************
// * logErrorSpacing(FILE *fl_log, float spcng[3]) *
// *************************************************

void logErrorSpacing(FILE *fl_log, float spcng[3])
{
	fprintf(fl_log, "Error in spacing\nx = %f, y = %f\n\n", spcng[0], spcng[1]);
}

// ******************************************************************************************************
// * logTiffInformation(FILE *fl_log, int dims[3], float spcng[3], int spp, int bps, int comp, int pin) *
// ******************************************************************************************************

void logTiffInformation(FILE *fl_log, int dims[3], float spcng[3], int spp, int bps, int comp, int pin)
{
	fprintf(fl_log, "TIFF image information:\n");

	// Dimensions
	fprintf(fl_log, "Dimensions: x = %d, y = %d, z = %d\n", dims[0], dims[1], dims[2]);

	// Spacing
	fprintf(fl_log, "Spacing: x = %f, y = %f, z = %f\n", spcng[0], spcng[1], spcng[2]);

	// The number of components per pixel
	fprintf(fl_log, "SamplesPerPixel = %d\n", spp);

	// Number of bits per component
	fprintf(fl_log, "BitsPerSample = %d\n", bps);

	// Compression scheme used on the image data
	fprintf(fl_log, "Compression = %d ", comp);

	if (comp == 1)
	{
		fprintf(fl_log, "(No compression)\n");
	}
	else if (comp == 2)
	{
		fprintf(fl_log, "(CCITT modified Huffman RLE)\n");
	}
	else if (comp == 3)
	{
		fprintf(fl_log, "(CCITT Group 3 fax encoding)\n");
	}
	else if (comp == 4)
	{
		fprintf(fl_log, "(CCITT Group 4 fax encoding)\n");
	}
	else if (comp == 5)
	{
		fprintf(fl_log, "(LZW)\n");
	}
	else if (comp == 6)
	{
		fprintf(fl_log, "(JPEG ('old-style' JPEG, later overridden in Technote2))\n");
	}
	else if (comp == 7)
	{
		fprintf(fl_log, "(JPEG ('new-style' JPEG))\n");
	}
	else if (comp == 32773)
	{
		fprintf(fl_log, "(PackBits compression, aka Macintosh RLE)\n");
	}
	else
	{
		fprintf(fl_log, "(Not defined yet)\n");
	}
	
	// The color space of the image data
	fprintf(fl_log, "PhotometricInterpretation = %d ", pin);

	if (pin == 0)
	{
		fprintf(fl_log, "(WhiteIsZero. For bilevel and grayscale images: 0 is imaged as white.)\n");
	}
	else if (pin == 1)
	{
		fprintf(fl_log, "(BlackIsZero. For bilevel and grayscale images: 0 is imaged as black.)\n");
	}
	else if (pin == 2)
	{
		fprintf(fl_log, "(RGB. RGB value of (0,0,0) represents black, and (255,255,255) represents white, assuming 8-bit components.)\n");
	}
	else if (pin == 3)
	{
		fprintf(fl_log, "(Palette color. In this model, a color is described with a single component.)\n");
	}
	else if (pin == 4)
	{
		fprintf(fl_log, "(Transparency Mask.)\n");
	}
	else if (pin == 5)
	{
		fprintf(fl_log, "(Seperated, usually CMYK.)\n");
	}
	else if (pin == 6)
	{
		fprintf(fl_log, "(YCbCr)\n");
	}
	else if (pin == 8)
	{
		fprintf(fl_log, "(CIE L*a*b*)\n");
	}
	else if (pin == 9)
	{
		fprintf(fl_log, "(CIE L*a*b*, alternate encoding also known as ICC L*a*b*)\n");
	}
	else if (pin == 10)
	{
		fprintf(fl_log, "(CIE L*a*b*, alternate encoding also known as ITU L*a*b*)\n");
	}
	else
	{
		fprintf(fl_log, "(Not defined yet)\n");
	}
}

// **********************************************************
// * logCalculationTime(FILE *fl_log, double cpu_time_used) *
// **********************************************************

void logCalculationTime(FILE *fl_log, double cpu_time_used)
{
	fprintf(fl_log, "\nCPU time used = %f seconds", cpu_time_used);
}