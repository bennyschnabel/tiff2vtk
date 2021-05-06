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
int dispInformationTIFF(int dims[3], float spcng[3], int spp, int bps, int comp, int pin);

// Variable declaration
char* fileNameImport;
char* fileNameExport;

int debug;
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


int main(int argc, char** argv)
{
	start = clock();

	dispHeader();

	// Debug mode (0 = false, 1 = true)
	debug = 1;

	switch (debug)
	{
	case 0:
		fileNameImport = argv[1];

		fileNameExport = argv[2];
		break;
	case 1:
		fileNameImport = "Multi_page24bpp.tif";
		fileNameImport = "multipage_tiff_example.tif";
		//fileNameImport = "Knochenprobe2stream.tiff";

		fileNameExport = "test.vtk";
		break;
	default:
		fileNameImport = "";
		
		fileNameExport = "";
		break;
	}

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
			// Assume equal spacing along x, y, z
			spcng[2] = spcng[1];
		}
		else 
		{
			// TODO
			printf("Error in spacing!");
			void abort(void);
		}

		// The unit of measurement for XResolution and YResolution.
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
			// TODO
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

		// SamplesPerPixel
		TIFFGetField(tif, TIFFTAG_SAMPLESPERPIXEL, &spp);
		
		// BitsPerSample
		TIFFGetField(tif, TIFFTAG_BITSPERSAMPLE, &bps);

		// Compression
		TIFFGetField(tif, TIFFTAG_COMPRESSION, &comp);
		
		// PhotometricInterpretation
		TIFFGetField(tif, TIFFTAG_PHOTOMETRIC, &pin);

		dispInformationTIFF(dims, spcng, spp, bps, comp, pin);
	}
	
	// Write *.VTK file
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
	
	// Check if the *.TIFF file is open
	if (tif) 
	{
		int countLoop = 0;
		// Loop over tiff stream
		do {
			printf("Image %d of %d scaned\n", countLoop, dims[2] - 1);
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
	printf("Time = %f seconds \n", cpu_time_used);

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

int dispInformationTIFF(int dims[3], float spcng[3], int spp, int bps, int comp, int pin)
{
	// Dimensions
	printf("Dimensions: x = %d, y = %d, z = %d\n", dims[0], dims[1], dims[2]);

	// Spacing
	printf("Spacing: x = %f, y = %f, z = %f\n", spcng[0], spcng[1], spcng[2]);

	// The number of components per pixel
	printf("SamplesPerPixel = %d\n", spp);

	// Number of bits per component
	printf("BitsPerSample = %d\n", bps);

	// Compression scheme used on the image data
	printf("Compression = %d ", comp);

	if (comp == 1)
	{
		printf("(No compression)\n");
	}
	else if (comp == 2)
	{
		printf("(CCITT modified Huffman RLE)\n");
	}
	else if (comp == 3)
	{
		printf("(CCITT Group 3 fax encoding)\n");
	}
	else if (comp == 4)
	{
		printf("(CCITT Group 4 fax encoding)\n");
	}
	else if (comp == 5)
	{
		printf("(LZW)\n");
	}
	else if (comp == 6)
	{
		printf("(JPEG ('old-style' JPEG, later overridden in Technote2))\n");
	}
	else if (comp == 7)
	{
		printf("(JPEG ('new-style' JPEG))\n");
	}
	else if (comp == 32773)
	{
		printf("(PackBits compression, aka Macintosh RLE)\n");
	}
	else
	{
		printf("(Not defined yet)\n");
	}
	
	// The color space of the image data
	printf("PhotometricInterpretation = %d ", pin);

	if (pin == 0)
	{
		printf("(WhiteIsZero. For bilevel and grayscale images: 0 is imaged as white.)\n");
	}
	else if (pin == 1)
	{
		printf("(BlackIsZero. For bilevel and grayscale images: 0 is imaged as black.)\n");
	}
	else if (pin == 2)
	{
		printf("(RGB. RGB value of (0,0,0) represents black, and (255,255,255) represents white, assuming 8-bit components.)\n");
	}
	else if (pin == 3)
	{
		printf("(Palette color. In this model, a color is described with a single component.)\n");
	}
	else if (pin == 4)
	{
		printf("(Transparency Mask.)\n");
	}
	else if (pin == 5)
	{
		printf("(Seperated, usually CMYK.)\n");
	}
	else if (pin == 6)
	{
		printf("(YCbCr)\n");
	}
	else if (pin == 8)
	{
		printf("(CIE L*a*b*)\n");
	}
	else if (pin == 9)
	{
		printf("(CIE L*a*b*, alternate encoding also known as ICC L*a*b*)\n");
	}
	else if (pin == 10)
	{
		printf("(CIE L*a*b*, alternate encoding also known as ITU L*a*b*)\n");
	}
	else
	{
		printf("(Not defined yet)\n");
	}

	return 0;
}