# tiff2vtk

Conversion of multipage *.TIFF files to *.VTK file format.

## Example


*.TIFF | *.VTK
--- | ---
![*.TIFF](https://github.com/bennyschnabel/tiff2vtk/blob/main/reference_images/Knochenprobe2stream.png) | ![*.VTK](https://github.com/bennyschnabel/tiff2vtk/blob/main/reference_images/Knochenprobe2stream_vtk.png)
 | [ParaView](https://www.paraview.org/)

## Requirements

### LibTIFF - TIFF Library and Utilities

Libtiff is a library for reading and writing Tagged Image File Format (abbreviated TIFF) files [[WIKIPEDIA]](https://en.wikipedia.org/wiki/Libtiff).

Install:
```
sudo apt update
sudo apt install libtiff-dev
```
## Usage

To run this project, compile it like:
```
gcc -Wall -L/usr/lib main.c -ltiff -o tiff2vtk
./tiff2vtk tiff_file_name vtk_file_name
```

Example:
```
gcc -Wall -L/usr/lib main.c -ltiff -o tiff2vtk
./tiff2vtk Knochenprobe2stream.tiff Knochenprobe2stream.vtk
```

## Additional information

[VTK File Formats](https://vtk.org/wp-content/uploads/2015/04/file-formats.pdf)

## TODO - Known bugs

- [ ] TIFFReadDirectory: Warning, Unknown field with tag 59932 (0xea1c) encountered
- [ ] Image is compressed with the following configuration: SamplesPerPixel = 3, BitsPerSample = 8

## License

[BSD-2-Clause License](https://github.com/bennyschnabel/tiff2vtk/blob/main/LICENSE)
