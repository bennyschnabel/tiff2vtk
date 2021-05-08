
<p align="center">
<img src="https://github.com/bennyschnabel/tiff2vtk/blob/main/reference_images/repo_card.png" alt="Logo" width="300" height="150">
<br>
Conversion of multipage *.TIFF files to *.VTK file format.
</p>

## Table of contents

- [Example](#example)
- [Requirements](#requirements)
- [Usage](#usage)
- [Additional information](#additional-information)
- [TODO / Known bugs](#todo--known-bugs)
- [License](#license)

## Example

Initial image| Converted file
--- | ---
![*.TIFF](https://github.com/bennyschnabel/tiff2vtk/blob/main/reference_images/Knochenprobe2stream.png) | ![*.VTK](https://github.com/bennyschnabel/tiff2vtk/blob/main/reference_images/Knochenprobe2stream_vtk.png)
*.TIFF | *.VTK - Rendered with [ParaView](https://www.paraview.org/)

## Requirements

### LibTIFF - TIFF Library and Utilities

Libtiff is a library for reading and writing Tagged Image File Format (abbreviated TIFF) files [[WIKIPEDIA]](https://en.wikipedia.org/wiki/Libtiff).

Install:
```
sudo apt update
sudo apt install libtiff-dev
```
## Usage

### Compilation and execution

For example, comipilate the program as follows:
```
gcc -g -Wall -Wextra -pedantic-errors -L/usr/lib src/main.c -ltiff -o build/tiff2vtk
```

To execute the program, the following arguments are passed to the command line:
- `tiff_file_name`: Filename of the *.TIFF file to be read in
- `vtk_file_name`: Filename of the *.VTK file to be saved
- `binary_or_ascii`: Save the data in ASCII or BINARY format, where `0` = ASCII and `1` = BINARY.

```
./build/tiff2vtk tiff_file_name vtk_file_name binary_or_ascii
```

### Example

Conversion of the Knochenprobe2stream.tiff file to the Knochenprobe2stream.vtk file, where the data type is ASCII.

```
gcc -g -Wall -Wextra -pedantic-errors -L/usr/lib src/main.c -ltiff -o build/tiff2vtk
./build/tiff2vtk Knochenprobe2stream.tiff Knochenprobe2stream.vtk 0
```

## Additional information

[VTK File Formats](https://vtk.org/wp-content/uploads/2015/04/file-formats.pdf)

[TIFF Specification](https://www.itu.int/itudoc/itu-t/com16/tiff-fx/docs/tiff6.pdf)

## TODO / Known bugs

- [ ] CMake
- [ ] TIFFReadDirectory: Warning, Unknown field with tag 59932 (0xea1c) encountered
- [ ] Image is compressed with the following configuration: SamplesPerPixel = 3, BitsPerSample = 8

## License

[BSD-2-Clause License](https://github.com/bennyschnabel/tiff2vtk/blob/main/LICENSE)
