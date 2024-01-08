import unittest
from clean import clean_file
import os

class TestCleanScript(unittest.TestCase):

    def setUp(self):
        # Set up any test data or state here
        self.test_filename = "test.in"
        self.test_output_filename = "test.out"
        with open(self.test_filename, "w") as f:
            f.write("This is a test file.\n")
            f.write("    This line has leading white space.\n")
            f.write("// This line is a comment.\n")
            f.write("This line has a // comment.\n")
            f.write("/* This is a block comment */\n")
            f.write("\n")
            f.write("This line is not a comment.\n")
        clean_file(self.test_filename)

    def test_remove_blank_lines(self):
        # Test to ensure blank lines are removed
        with open(self.test_output_filename, 'r') as f:
            lines = f.readlines()
        self.assertNotIn('\n', lines, "Blank lines were not removed.")

    def test_remove_leading_white_spaces(self):
        # Test to ensure leading white spaces are removed
        with open(self.test_output_filename, 'r') as f:
            for line in f:
                self.assertFalse(line.startswith(' '), "Leading white spaces were not removed.")

    def test_remove_double_slash_comments(self):
        # Test to ensure "//" comments are removed
        with open(self.test_output_filename, 'r') as f:
            for line in f:
                self.assertNotIn("//", line, "Double slash comments were not removed.")

    def test_remove_block_comments(self):
        # Test to ensure "/* */" comments are removed
        with open(self.test_output_filename, 'r') as f:
            content = f.read()
        self.assertNotIn("/*", content, "Block comments start not removed.")
        self.assertNotIn("*/", content, "Block comments end not removed.")

    def test_non_commented_lines(self):
        # Test to ensure non-commented lines are unchanged
        expected_line = "This line is not a comment.\n"
        with open(self.test_output_filename, 'r') as f:
            self.assertIn(expected_line, f.readlines(), "Non-commented lines were changed.")

    def test_file_extension_check(self):
        # Test to ensure only ".in" files are accepted
        with self.assertRaises(AssertionError):
            clean_file("invalid_file.txt")

    def tearDown(self):
        # Clean up any test data or state here
        os.remove(self.test_filename)
        os.remove(self.test_output_filename)

if __name__ == '__main__':
    unittest.main()
