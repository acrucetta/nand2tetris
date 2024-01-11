## Introduction
This Python script is designed to cleanse a given input file by removing blank lines, leading/trailing whitespace, and comments. Comments can be of two types: single-line comments starting with `//` and multi-line comments enclosed within `/*` and `*/`.

## How to Compile
No compilation is needed as the script is written in Python. Ensure that Python is installed on your system.

## How to Run
1. Place your input file in the same directory as the script. The input file should have the `.in` extension.
2. Run the script from the command line using Python:

   ```bash
   python clean.py <filename.in>
   ```

   Replace `<filename.in>` with the actual name of your input file.

## Description of Functionality
### What Works
- The script removes any lines starting with `//` and any text following `//` in a line.
- It also removes text enclosed within `/*` and `*/`, handling cases where these markers appear on the same or separate lines.
- Blank lines and leading/trailing whitespace are removed.
- The cleansed content is saved in a new file with the same name but with a `.out` extension.

### Limitations
- The script expects the input filename to have a `.in` extension and will assert an error if this is not the case.
- Incomplete multi-line comment syntax (e.g., missing `*/`) might lead to unexpected results.
- The script does not handle nested comments.
- It only accepts one file at a time and cannot process directories or multiple files simultaneously.
