// Parser
//
// The parser handles a single.vm command. It reads a VM command, parses it,
// and provides convenient access to the command’s components (fields and symbols).
// In addition, it removes all white space and comments.

use std::{fs::File, io::Read};

#[derive(Debug, PartialEq)]
enum CommandType {
    CPop,
    CArithmetic,
    CPush,
    CLabel,
    CGoto,
    CIf,
    CFunction,
    CReturn,
    CCall,
}

struct Command {
    command_type: CommandType,
    arg1: String,
    arg2: Option<i32>,
}

impl Command {
    fn new(command_type: CommandType, arg1: String, arg2: Option<i32>) -> Command {
        Command {
            command_type: command_type,
            arg1: arg1,
            arg2: arg2,
        }
    }
}

fn get_command_type(command : &str) -> CommandType {
    let command = command.split(" ").collect::<Vec<&str>>();
    match command.first() {
        Some(&"pop") => CommandType::CPop,
        Some(&"push") => CommandType::CPush,
        Some(&"label") => CommandType::CLabel,
        Some(&"goto") => CommandType::CGoto,
        Some(&"if-goto") => CommandType::CIf,
        Some(&"function") => CommandType::CFunction,
        Some(&"return") => CommandType::CReturn,
        Some(&"call") => CommandType::CCall,
        _ => CommandType::CArithmetic,
    }
}

// FILE IO

fn read_file(file: &str) -> String {
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

fn clean_file(contents: String) -> Vec<String> {
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

// PARSER

/// Builds a list of commands based on cleaned lines.
///
/// # Arguments
///
/// * `cleaned_lines` - A vector of cleaned lines.
///
/// # Returns
///
/// A vector of commands.
fn build_command_list(cleaned_lines: Vec<String>) -> Vec<Command> {
    let mut commands : Vec<Command> = Vec::new();
    for command in cleaned_lines {
        let command_type = get_command_type(&command);
        let command_parts = command.split(" ").collect::<Vec<&str>>();
        let arg1 = command_parts[0].to_string();
        let arg2 = match command_parts.get(2) {
            Some(arg) => Some(arg.parse::<i32>().unwrap()),
            None => None,
        };
        let command = Command::new(command_type, arg1, arg2);
        commands.push(command);
    }
    return commands;
}

fn main() {
    let test_file = "test/SimpleAdd.vm";
    let contents = read_file(test_file);
    let cleansed_file = clean_file(contents);
    let commands = build_command_list(cleansed_file);
    return ();
}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_strip_comments() {
        let line = "push constant 7 // push constant 7";
        assert_eq!(strip_comments(line), "push constant 7 ");
    }

    #[test]
    fn test_get_command_type() {
        let command = "push constant 7";
        assert_eq!(get_command_type(command), CommandType::CPush);

        let command = "add";
        assert_eq!(get_command_type(command), CommandType::CArithmetic);

        let command = "pop local 0";
        assert_eq!(get_command_type(command), CommandType::CPop);

        let command = "label LOOP_START";
        assert_eq!(get_command_type(command), CommandType::CLabel);

        let command = "goto LOOP_START";
        assert_eq!(get_command_type(command), CommandType::CGoto);

        let command = "if-goto LOOP_START";
        assert_eq!(get_command_type(command), CommandType::CIf);

        let command = "function SimpleFunction.test 2";
        assert_eq!(get_command_type(command), CommandType::CFunction);
    }
}