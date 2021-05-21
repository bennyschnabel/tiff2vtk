 #!/usr/bin/env pvpython

import sys
import os
import argparse
import time

import vtk
import numpy as np
from PIL import Image

# Set path to paraview build folder
sys.path.insert(0, '/home/benny/paraview_build/lib/python3.8/site-packages')

#https://python.hotexamples.com/de/examples/vtk/-/vtkTIFFReader/python-vtktiffreader-function-examples.html

HEADER = """# vtk DataFile Version 5.1
vtk output
ASCII
DATASET STRUCTURED_POINTS
DIMENSIONS %s %s %s
ORIGIN 0 0 0
SPACING %s %s %s
POINT_DATA %s
SCALARS DICOMImage short
LOOKUP_TABLE default\n"""

def createHeader(outdir, outFile, dims, spcng):
    if not os.path.isdir(outdir):
        os.makedirs(outdir)
    if os.path.isdir(outdir):
        string_ = HEADER %(dims[0], dims[1], dims[2], spcng[0], spcng[1], spcng[2], dims[0] * dims[1] * dims[2])
        file_ = open(outFile, "w")
        file_.write(string_)
        file_.close()

def convertFile(filepath, outdir, outFile, dims):
    if not os.path.isdir(outdir):
        os.makedirs(outdir)
    if os.path.isfile(filepath):
        basename = os.path.basename(filepath)
        print("Converting file:", basename)
        im = Image.open(filepath)
        array = np.array(im)

        file_ = open(outFile, "a+")

        for i in range(0, dims[0]):
            for j in range(0, dims[1]):
                file_.write("%s " % array[i, j])

        file_.close()

        #print(array)
        return True

    return False

def convertFiles(indir, outdir):
    files = os.listdir(indir)
    files = [ os.path.join(indir,f) for f in files if f.endswith('.tif') ]
    # Check if file extension is *.TIFF
    if len(files) == 0:
        files = [ os.path.join(indir,f) for f in files if f.endswith('.tiff') ]
    
    if len(files) == 0:
        sys.exit("Error!\nIn dir is empty!")

    files = sorted(files)

    fileName = time.strftime("output_%Y%m%d_%H%M%S")
    outFile = os.path.join(outdir, fileName+".vtk")

    # Header Information
    im = Image.open(files[0])
    dims[0], dims[1] = im.size
    dims[2] = len(files)
    spcng[0] = im.info['dpi'][0]
    spcng[1] = im.info['dpi'][1]
    # Equal spacing!
    spcng[2] = im.info['dpi'][0]

    createHeader(outdir, outFile, dims, spcng)
    
    ret = 0

    print(len(files))
    print("In dir:", indir)
    print("Out dir:", outdir)
    for f in files:
        ret += convertFile(f, outdir, outFile, dims)

    print("Successfully converted %d out of %d files." % (ret, len(files)))

def run(args):
    convertFiles(args.indir, args.outdir)

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="TIFF to VTK converter")
    parser.add_argument('indir', help="Path to input directory.")
    parser.add_argument('--outdir', '-o', default='output', help="Path to output directory.")
    parser.set_defaults(func=run)
    args = parser.parse_args()
    ret = args.func(args)