# Parser Coding Challenge

This C program can parse MP4 files and extract information about the different box structures contained within.

> [!NOTE]
> 
> Files conforming to the ISO base media file format are formed as a series of objects, called "boxes".
All data is contained in boxes and there is no other data within the file. This includes any initial
signature required by the specific file format. The "box" is object oriented building block defined by a
unique type identifier and length. It was called "atom" in some specifications (e.g. the first definition of
MP4 file format).
> 
> [MP4Box.js / ISOBMFF Box Structure Viewer](https://gpac.github.io/mp4box.js/test/filereader.html) to visualize the structure of the sample file.
> 
> Details about the format can be found at [Wikipedia - ISO base media file format](https://en.wikipedia.org/wiki/ISO_base_media_file_format).

## Features
- Iteratively parses an entire MP4 file as a byte stream
- Extracts the type and size of each box encountered
- Handles the special case of the mdat box that contains an UTF8 encoded XML string

## How to use

Clone the repository and run:

`mp4-parser-project .\sample\test0.mp4`

## Simple code explanation

The `main` function is the entry point of the program. It checks if a filename is provided as a command-line argument, opens the file, and calls `ft_readFile`.

`ft_readFile` takes a file pointer and a filename as input, reads the file into memory, and then calls `ft_parseFile` to initiate the parsing process.

 `ft_parseFile` is the main function for parsing the entire file. It iterates through the file content, identifies the type of each box, and calls `ft_extractBox`.
 
 `ft_extractBox` is responsible for extracting information about a box, filling in a `BoxInfo` structure, and calling `ft_processBox` to further process the box.
 
 `ft_processBox` takes the file content and a `BoxInfo` structure as input and processes the box. It includes logic for handling the MDAT box, printing its content, and printing information about their type and size.
 
## Project structure
- **sample**
  - test0.mp4
- **src**
  - main.c
  - mp4-parser-prj.c
  - mp4-parser-prj.h
- mp4-parser-prj.exe
## Output 
mdat_content.dat --> UTF8 encoded XML string in mdat box.

## Bonus : : Which problem can occur if the content of the MDAT box is very large?

- **File size limits**: On some systems there may be limits on size of files that can be opened/processed in a program. A file with an extremely large MDAT could exceed these limits.

- **Streaming support**: The current implementation requires the full file in memory. For large files it would be better to support streaming/random access so not everything needs to be loaded at once.

- **Memory issues**: If the entire file is read into a buffer in memory as currently done, it may exceed available RAM for very large files. This could cause the program to crash or throw errors.
