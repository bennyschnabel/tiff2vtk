//
// tiff2vtk
//
// Author: Benjamin Schnabel
// High Performance Computing Center Stuttgart (HLRS)
// BSD-2-Clause License 
// Date: 2021.05.05
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
// LibTIFF - TIFF Library and Utilities
#include <tiffio.h>

// Function declaration
int dispHeader(void);

// Variable declaration
char* fileNameImport;
char* fileNameExport;

int spp;
int bps;
int comp;
int pin;
int count;
int resunit;

int dims[3];

float spcng[3];
float delta;

clock_t start, end;
double cpu_time_used;


int main()
{
	start = clock();

	dispHeader();

	// File name of the *.TIFF file to be imported
	fileNameImport = "Multi_page24bpp.tif";
	fileNameImport = "multipage_tiff_example.tif";
	
	//fileNameImport = "Knochenprobe2stream.tiff";
	fileNameExport = "test.vtk";

	// Open *.TIFF file
	TIFF* tif = TIFFOpen(fileNameImport, "r");

	// Check if the *.TIFF file is open 
	if (tif) {

		// Determination of the dimensions of the *.TIFF file		
		TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &dims[0]);
		TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &dims[1]);
		dims[2] = TIFFNumberOfDirectories(tif);
		
		// Determination of the spacing of the *.TIFF file
		TIFFGetField(tif, TIFFTAG_XRESOLUTION, &spcng[0]);
		TIFFGetField(tif, TIFFTAG_YRESOLUTION, &spcng[1]);
		
		if (spcng[0] == spcng[1])
		{
			// Equal spacing along x, y, z
			spcng[2] = spcng[1];
		}
		else 
		{
			printf("Error in spacing!");
			void abort(void);
		}

		TIFFGetField(tif, TIFFTAG_RESOLUTIONUNIT, &resunit);
		printf("Resolution Unit: ");
		if (resunit == 1)
		{
			printf("No absolute unit of measurement. Used for images that may have a non-square aspect ratio, but no meaningful absolute dimensions.\n");
		}
		else if (resunit == 2)
		{
			printf("Inch\n");
			
			for (int i = 0; i < 3; i++)
			{
				spcng[i] = 25.4 / spcng[i];
			}
		}
		else if (resunit == 3)
		{
			printf("Centimeter\n");
			
			for (int i = 0; i < 3; i++)
			{
				spcng[i] = 64.516 / spcng[i];
			}
		}
		else
		{
			printf("Error in resolution unit\nCode: %d\n", resunit);

			float spcngUserInput;
			printf("Enter resolution in pixels/in: ");
			scanf("%f", &spcngUserInput); 

			for (int i = 0; i < 3; i++)
			{
				spcng[i] = 25.4 / spcngUserInput;
			}
		}
		
		printf("dims = %d %d %d\n", dims[0], dims[1], dims[2]);
		printf("spcng = %f %f %f\n", spcng[0], spcng[1], spcng[2]);
		
		
		// SamplesPerPixel
		TIFFGetField(tif, TIFFTAG_SAMPLESPERPIXEL, &spp);
		printf("SamplesPerPixel = %d\n", spp);
		
		// BitsPerSample
		TIFFGetField(tif, TIFFTAG_BITSPERSAMPLE, &bps);
		printf("BitsPerSample = %d\n", bps);

		// Compression
		TIFFGetField(tif, TIFFTAG_COMPRESSION, &comp);
		printf("Compression = %d\n", comp);
		
		// PhotometricInterpretation
		TIFFGetField(tif, TIFFTAG_PHOTOMETRIC, &pin);
		printf("PhotometricInterpretation = %d\n", pin);
	}
	
	
	FILE *fl_un;
	fl_un = fopen(fileNameExport, "w+");
	// Part 1:Header
	fprintf(fl_un, "# vtk DataFile Version 5.1\n");
	// Part 2:Title (256 characters maximum, terminated with newline \n character)
	fprintf(fl_un, "%s\n", fileNameImport);
	// Part 3:Data type, either ASCII or BINARY
	fprintf(fl_un, "ASCII\n");
	// Part 4:Geometry/topology.Type is one of: STRUCTURED_POINTS, STRUCTURED_GRID, UNSTRUCTURED_GRID, POLYDATA, RECTILINEAR_GRID, FIELD
	fprintf(fl_un, "DATASET STRUCTURED_POINTS\n");
	// Part4: DIMENSIONS nx ny nz
	fprintf(fl_un, "DIMENSIONS %d %d %d\n", dims[0], dims[1], dims[2]);
	// Part4: ORIGIN x y z
	fprintf(fl_un, "ORIGIN 0 0 0\n");
	// Part4: SPACING sx sy sz
	fprintf(fl_un, "SPACING %f %f %f\n", spcng[0], spcng[1], spcng[2]);
	// Part 5:Dataset attributes. The number of data items n of each type must match the numberof points or cells in the dataset. (If type is FIELD, point and cell data should be omitted.
	fprintf(fl_un, "POINT_DATA %d\n", dims[0] * dims[1] * dims[2]);
	fprintf(fl_un, "SCALARS DICOMImage short\n");
	fprintf(fl_un, "LOOKUP_TABLE default\n");
	fclose(fl_un);
	
	// check the tif is open
	if (tif) 
	{
		int countLoop = 0;
		// Loop over tiff stream
		do {
			//printf("%d\n", countLoop);
			countLoop++;
			count = 0;
			tsize_t scanline;
			tdata_t buf;
			uint32_t row;
			uint32_t col;
			
			scanline = TIFFScanlineSize(tif);
			buf = _TIFFmalloc(scanline);
			uint8_t* data;
			
			fl_un = fopen(fileNameExport, "a");
			
			for (row = 0; row < dims[1]; row++)
			{
				TIFFReadScanline(tif, buf, row,1);
				data = (uint8_t*)buf;
				
				for (col = 0; col < dims[0]; col++)
				{
					unsigned int im_int = (uintptr_t) *data;
					fprintf(fl_un, "%d ", (short) im_int);
					count++;
					data++;
				}
			}
			
			fclose(fl_un);
		} while (TIFFReadDirectory(tif));
	}

	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Time: %f seconds \n", cpu_time_used);

	return 0;
}

int dispHeader(void)
{
	printf("######################################################\n");
	printf("# tiff2vtk                                           #\n");
	printf("#                                                    #\n");
	printf("# Author: Benjamin Schnabel                          #\n");
	printf("# High Performance Computing Center Stuttgart (HLRS) #\n");
	printf("# Date: 2021.05.05                                   #\n");
	printf("######################################################\n\n");

	return 0;
}