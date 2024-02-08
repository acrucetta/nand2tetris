#[derive(Debug, PartialEq)]

pub enum CommandType {
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

pub struct Command {
    pub command_type: CommandType,
    pub arg1: String,
    pub arg2: Option<i32>,
}

impl Command {
    pub fn new(command_type: CommandType, arg1: String, arg2: Option<i32>) -> Command {
        Command {
            command_type: command_type,
            arg1: arg1,
            arg2: arg2,
        }
    }
}

pub fn get_command_type(command: &str) -> CommandType {
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

/// Builds a list of commands based on cleaned lines.
///
/// # Arguments
///
/// * `cleaned_lines` - A vector of cleaned lines.
///
/// # Returns
///
/// A vector of commands.
pub fn build_command_list(cleaned_lines: Vec<String>) -> Vec<Command> {
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

mod tests {
    use super::*;

    #[test]
    fn test_new_command() {
        let command = Command::new(CommandType::CPop, "local".to_string(), Some(0));
        assert_eq!(command.command_type, CommandType::CPop);
        assert_eq!(command.arg1, "local");
        assert_eq!(command.arg2, Some(0));
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
