<p align="center">
<img src="https://github.com/bennyschnabel/tiff2vtk/blob/main/reference_images/repo_card.png" alt="Logo" width="300" height="150">
<br>
Conversion of multipage *.TIFF files to *.VTK file format.
</p>

## Table of contents

- [Description](#description)
- [Example](#example)
- [Requirements](#requirements)
- [Usage](#usage)
- [Additional information](#additional-information)
- [Todo list](#todo-list)
- [License](#license)

## Description

tiff2vtk converts multipage *.TIFF files to *.VTK files. For this vtk DataFile version 5.1 is used.

## Example

Initial image| Converted file
--- | ---
![*.TIFF](https://github.com/bennyschnabel/tiff2vtk/blob/main/reference_images/Knochenprobe2stream_tiff.png) | ![*.VTK](https://github.com/bennyschnabel/tiff2vtk/blob/main/reference_images/Knochenprobe2stream_vtk.png)
*.TIFF | *.VTK - Rendered with [ParaView](https://www.paraview.org/)
&nbsp; | Data type BINARY

## Requirements

### GNU Compiler Collection

The GNU Compiler Collection (GCC) is an optimizing compiler produced by the GNU Project supporting various programming languages, hardware architectures and operating systems [[Wikipedia]](https://en.wikipedia.org/wiki/GNU_Compiler_Collection). 

Install:

```console
foo@bar:~$ sudo apt update
foo@bar:~$ sudo apt-get install build-essential 
```

### LibTIFF - TIFF Library and Utilities

Libtiff is a library for reading and writing Tagged Image File Format (abbreviated TIFF) files [[WIKIPEDIA]](https://en.wikipedia.org/wiki/Libtiff).

Install:

```console
foo@bar:~$ sudo apt update
foo@bar:~$ sudo apt-get install libtiff-dev
```

## Usage

Compilation is done either via the terminal or via the Makefile

### Compilation (Terminal)

For example, comipilate the program as follows:

```console
foo@bar:~$ gcc -g -Wall -Wextra -pedantic-errors -L/usr/lib src/log.c src/main.c -ltiff -o build/tiff2vtk
```

### Compilation (Makefile)

```console
foo@bar:~$ make
```

### Execution

To execute the program, the following arguments are passed to the command line:
- `tiff_file_name`: Filename of the *.TIFF file to be read in
- `vtk_file_name`: Filename of the *.VTK file to be saved
- `ascii_or_binary`: Save the data in ASCII or BINARY format, where `0` = ASCII and `1` = BINARY.

```console
foo@bar:~$ ./build/tiff2vtk tiff_file_name vtk_file_name ascii_or_binary
```

### Example

Conversion of the Knochenprobe2stream.tiff file to the Knochenprobe2stream.vtk file, where the data type is BINARY. And it is a good practice to place the *.TIFF and *.VTK files in the datasets folder.

```console
foo@bar:~$ make
foo@bar:~$ ./build/tiff2vtk datasets/Knochenprobe2stream.tiff datasets/Knochenprobe2stream.vtk 1
```

## Additional information

[VTK File Formats](https://vtk.org/wp-content/uploads/2015/04/file-formats.pdf)

[TIFF Specification](https://www.itu.int/itudoc/itu-t/com16/tiff-fx/docs/tiff6.pdf)

## Todo list

[TODO.md](https://github.com/bennyschnabel/tiff2vtk/blob/main/TODO.md)

## License

[BSD-2-Clause License](https://github.com/bennyschnabel/tiff2vtk/blob/main/LICENSE)
