"""
This python script will take a file "<filename>.in" and remove blank lines and leading white space. It will also
remove all comments, which can come of the type "//" and end at the line return or with the sequence /* and end with the sequence */

The final cleansed file will have the file extension .out
"""
import sys


def remove_comments(line: str) -> str:
    """
    Removes comments from a given line of code.

    Args:
        line (str): The line of code to remove comments from.

    Returns:
        str: The line of code with comments removed.
    """
    # If the line is empty, return it
    if not line:
        return line
    # If the line starts with //, return an empty string
    if line.startswith("//"):
        return ""

    # Case 1: Line has a comment with // that needs to be removed
    # we grab all the strings after // and remove them from the line
    if "//" in line:
        # Find the index of "//" and return a line
        # with values up to the index before //
        index = line.index("//")
        return line[:index]
    # Case 2: Line has a comment with /* that needs to be removed
    # we grab all the strings after /* and remove them from the line
    if "/*" in line:
        # Check if there's a */ in the line
        # if not, we return the line up to the /*
        if "*/" not in line:
            index = line.index("/*")
            return line[:index]
        start_index = line.index("/*")
        end_index = line.index("*/") + 2
        return line[:start_index] + line[end_index:]
    # Case 3: Line has a comment with */ that needs to be removed
    # we grab all the strings after */ and remove them from the line
    if "*/" in line:
        # Return only the values after the */
        index = line.index("*/") + 2
        return line[index:]
    return line


def clean_file(filename: str):
    """
    Cleans the contents of a file by removing comments and leading/trailing white space.

    Args:
        filename (str): The path to the file to be cleaned.

    Returns:
        int: Always returns 0.
    """
    # Check that the file extension is .in
    assert filename.endswith(".in"), "File must have extension .in"
    
    # Open the file for reading
    with open(filename, "r", encoding="utf-8") as f:
        # Read all the lines from the file
        lines = f.readlines()
    cleansed_lines = []
    for line in lines:
        # Remove all comments
        line = remove_comments(line)
        # Remove leading and trailing white space
        line = line.strip()
        # If the line is not empty, add it to the cleansed lines
        if line:
            cleansed_lines.append(line)
    
    output_filename = filename.replace(".in", ".out")
    with open(output_filename, "w", encoding="utf-8") as f:
        # Write all the cleansed lines to the file
        for line in cleansed_lines:
            f.write(line + "\n")
    return 0


if __name__ == "__main__":
    # Accept arguments from the command line
    if len(sys.argv) != 2:
        print("Usage: python clean.py <filename>")
        exit(1)
    filename = sys.argv[1]
    clean_file(filename)
