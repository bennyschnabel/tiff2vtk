# tiff2vtk

Conversion of multipage *.TIFF files to *.VTK file format.

## Requirements

### LibTIFF - TIFF Library and Utilities

Libtiff is a library for reading and writing Tagged Image File Format (abbreviated TIFF) files [WIKIPEDIA](https://en.wikipedia.org/wiki/Libtiff).

Install:
```
sudo apt update
sudo apt install libtiff-dev
```
## Usage

To run this project, compile it like:
```
gcc -Wall -L/usr/lib main.c -ltiff -o tiff2vtk
./tiff2vtk **tiff file name** **vtk file name**
```

Example:
```
gcc -Wall -L/usr/lib main.c -ltiff -o tiff2vtk
./tiff2vtk Knochenprobe2stream.tiff Knochenprobe2stream.vtk
```

## Additional information

[VTK File Formats](https://vtk.org/wp-content/uploads/2015/04/file-formats.pdf)

## License

[BSD-2-Clause License](https://github.com/bennyschnabel/tiff2vtk/blob/main/LICENSE)
