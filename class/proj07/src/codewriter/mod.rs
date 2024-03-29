use std::{collections::HashMap, fmt::Error, fs::File, io::ErrorKind};

use crate::parser::{self, Command};
use parser::CommandType;

/*

Code Writer Module.

This module translates a parsed VM command into Hack assembly code.
For example, calling writePushPop (C_PUSH,"local",2) would result in
generating assembly instructions that implement the VM command push local 2.

*/

pub struct VMWriter {
    file: File,
    vm_counter: i16,
    function: String,
}

impl VMWriter {
    pub fn new(file: File) -> VMWriter {
        VMWriter {
            file,
            vm_counter: 0,
            function: String::from("boot"),
        }
    }

    pub fn parse(self, command: Command) -> Result<Vec<String>, ErrorKind> {
        let asm = match command.command_type {
            CommandType::CLabel | CommandType::CGoto | CommandType::CIf => {
                self.write_branch(command)
            }
            CommandType::CPop | CommandType::CPush => self.write_pushpop(command),
            CommandType::CCall | CommandType::CFunction | CommandType::CReturn => {
                self.write_function(command)
            }
            CommandType::CArithmetic => self.write_arithmetic(command),
        };
        asm
    }

    fn write_branch(&self, command: Command) -> Result<Vec<String>, ErrorKind> {
        let mut asm: Vec<String> = Vec::new();
        let label_name = String::from(format!("{}${}", self.function, command.arg1)); // boot$function
        let decrement_sp_and_store = vec![
            String::from("@SP"),
            String::from("AM=M-1"),
            String::from("D=M"),
        ];
        match command.command_type {
            CommandType::CLabel => {
                asm.push(format!("({})", label_name)); // (labelname)
            }
            CommandType::CGoto => {
                asm.push(format!("@{}", label_name)); // @labelname
                asm.push(String::from("0;JMP"));
            }
            CommandType::CIf => {
                asm.extend(decrement_sp_and_store);
                asm.push(format!("@{}", label_name));
                asm.push(String::from("D;JNE"));
            }
            _ => return Err(ErrorKind::InvalidInput),
        }
        return Ok(asm);
    }

    fn write_function(&self, command: Command) -> Result<Vec<String>, ErrorKind> {
        match command.command_type {
            CommandType::CCall => {
                let function_name = command.arg1;
                let n_args = command.arg2;
                let return_address = format!("{}$ret.{}", function_name, self.vm_counter);
                // Push Symbols (LCL, ARG, THIS, THAT)
                // Push Call ASM
                return Ok(Vec::new());
            }
            CommandType::CFunction => {
                let function_name = command.arg1;
                let n_locals = command.arg2;
                // Push Function ASM
                // Re-assign label
                return Ok(Vec::new());
            }
            CommandType::CReturn => {
                return Ok(Vec::new());
            }
            _ => return Err(ErrorKind::InvalidInput),
        }
    }

    fn write_arithmetic(&self, command: Command) -> Result<Vec<String>, ErrorKind> {
        let mapping: HashMap<&str, &str> = vec![
            ("add", "+"),
            ("sub", "-"),
            ("neg", "-"),
            ("eq", "JEQ"),
            ("gt", "JGT"),
            ("lt", "JLT"),
            ("and", "&"),
            ("or", "|"),
            ("not", "!"),
        ]
        .into_iter()
        .collect();

        let pop_one = vec![String::from("@SP"), String::from("AM=M-1")];
        let pop_two = vec![
            String::from("@SP"),
            String::from("AM=M-1"),
            String::from("D=M"),
            String::from("A=A-1"),
        ];

        let operation = command.arg1.to_string();
        let op = mapping.get(operation.as_str()).unwrap();

        let mut asm: Vec<String> = Vec::new();

        match operation.as_str() {
            "add" | "sub" | "and" | "or" => {
                asm.extend(pop_two);
                asm.push(format!("M=M{}D", op));
            }
            "neg" | "not" => {
                asm.extend(pop_one);
                asm.push(format!("M={}M", op));
            }
            "eq" | "gt" | "lt" => {
                let op_lines = 14;
                let label_true = format!("{}_TRUE_{}", operation, op_lines);
                let label_end = format!("{}_END_{}", operation, op_lines);
                asm.extend(pop_two);
                asm.push(format!("D=M-D"));
                asm.push(format!("@{}", label_true));
                asm.push(format!("D;{}", op));
                asm.push(String::from("@SP"));
                asm.push(String::from("A=M-1"));
                asm.push(String::from("M=0"));
                asm.push(format!("@{}", label_end));
                asm.push(String::from("0;JMP"));
                asm.push(format!("({})", label_true));
                asm.push(String::from("@SP"));
                asm.push(String::from("A=M-1"));
                asm.push(String::from("M=-1"));
                asm.push(format!("({})", label_end));
            }
            _ => {
                return Err(ErrorKind::InvalidInput);
            }
        }
        return Ok(asm);
    }

    fn write_pushpop(&self, command: Command) -> Result<Vec<String>, ErrorKind> {
        let mapping: HashMap<&str, &str> = vec![
            ("local", "LCL"),
            ("argument", "ARG"),
            ("this", "THIS"),
            ("that", "THAT"),
            ("temp", "5"),
            ("pointer", "3"),
            ("static", "16"),
        ]
        .into_iter()
        .collect();

        let mut asm: Vec<String> = Vec::new();
        let segment = command.arg1.to_string();
        let op_segment = mapping.get(segment.as_str()).unwrap();
        let index = command.arg2.expect("Error: No index provided");

        let put_at_sp = vec![
            String::from("@SP"),
            String::from("A=M"),
            String::from("M=D"),
        ];
        let increment_sp = vec![String::from("@SP"), String::from("M=M+1")];
        let decrement_sp_and_store = vec![
            String::from("@SP"),
            String::from("AM=M-1"),
            String::from("D=M"),
        ];

        match command.command_type {
            CommandType::CPush => match segment.as_str() {
                "constant" => {
                    asm.push(format!("@{}", index));
                    asm.push(String::from("D=A"));
                    asm.extend(put_at_sp);
                    asm.extend(increment_sp);
                }
                "static" | "pointer" | "temp" => {
                    let relative_segment = index + op_segment.parse::<i32>().unwrap();
                    asm.push(format!("@{}", relative_segment));
                    asm.push(String::from("D=A"));
                    asm.push(format!("@{}", op_segment));
                    asm.push(String::from("A=D+A"));
                    asm.push(String::from("D=M"));
                    asm.extend(put_at_sp);
                }
                "local" | "argument" | "this" | "that" => {
                    asm.push(format!("@{}", index));
                    asm.push(String::from("D=A"));
                    asm.push(format!("@{}", op_segment));
                    asm.push(String::from("A=D+M"));
                    asm.push(String::from("D=M"));
                    asm.extend(put_at_sp);
                    asm.extend(increment_sp);
                }
                _ => {
                    return Err(ErrorKind::InvalidInput);
                }
            },
            CommandType::CPop => match segment.as_str() {
                "local" | "argument" | "this" | "that" => {
                    asm.extend(decrement_sp_and_store);
                    asm.push(format!("@{}", op_segment));
                    asm.push(String::from("D=M"));
                    asm.push(format!("@{}", index));
                    asm.push(String::from("A=D+A"));
                    asm.push(String::from("M=D"));
                }
                "temp" | "pointer" | "static" => {
                    let relative_segment = index + op_segment.parse::<i32>().unwrap();
                    asm.extend(decrement_sp_and_store);
                    asm.push(format!("@{}", relative_segment));
                    asm.push(String::from("M=D"));
                }
                _ => return Err(ErrorKind::InvalidData),
            },
            _ => {
                return Err(ErrorKind::InvalidInput);
            }
        }
        return Ok(asm);
    }
}

#[cfg(test)]

mod tests {
    use super::*;

    #[test]
    fn test_write_arithmetic() {
        let command = Command {
            command_type: CommandType::CArithmetic,
            arg1: String::from("add"),
            arg2: None,
        };
        let result = write_arithmetic(command);
        assert_eq!(
            result,
            Ok(vec![
                String::from("@SP"),
                String::from("AM=M-1"),
                String::from("D=M"),
                String::from("A=A-1"),
                String::from("M=M+D"),
            ])
        );
    }

    #[test]
    fn test_write_pushpop() {
        let command = Command {
            command_type: CommandType::CPush,
            arg1: String::from("local"),
            arg2: Some(2),
        };
        let index = 0;
        let result = write_pushpop(command, index);
        assert_eq!(
            result,
            Ok(vec![
                String::from("@2"),
                String::from("D=A"),
                String::from("@LCL"),
                String::from("A=D+M"),
                String::from("D=M"),
                String::from("@SP"),
                String::from("A=M"),
                String::from("M=D"),
                String::from("@SP"),
                String::from("M=M+1"),
            ])
        );
    }
}
