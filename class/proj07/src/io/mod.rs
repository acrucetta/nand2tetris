// FILE IO

use std::{fs::File, io::Read};

pub fn read_file(file: &str) -> String {
    let mut f = File::open(file).expect("file not found");
    let mut contents = String::new();
    f.read_to_string(&mut contents)
        .expect("something went wrong reading the file");
    contents
}

fn strip_comments(line: &str) -> String {
    let mut result = String::new();
    for c in line.chars() {
        if c == '/' {
            break;
        }
        result.push(c);
    }
    result
}

pub fn clean_file(contents: String) -> Vec<String> {
    let mut lines = contents.lines();
    let mut cleaned_lines : Vec<String> = Vec::new();
    for line in lines {
        let clean_line = strip_comments(line);
        if clean_line != "" {
            cleaned_lines.push(clean_line);
        }
    }
    return cleaned_lines;
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_strip_comments() {
        let line = "push constant 7 // push constant 7";
        assert_eq!(strip_comments(line), "push constant 7 ");
    }
}