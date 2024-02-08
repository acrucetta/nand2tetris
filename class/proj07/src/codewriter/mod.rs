use std::{collections::HashMap, fmt::Error, fs::File, io::ErrorKind};

use parser::{CommandType};
use crate::parser::{self, Command};

/*

Code Writer Module.

This module translates a parsed VM command into Hack assembly code.
For example, calling writePushPop (C_PUSH,"local",2) would result in 
generating assembly instructions that implement the VM command push local 2.

*/



/*
Arithmetic-Logical Commands:
- add, sub, neg
- eq, gt, lt
- and, or, not

The VM implementation pops two values off the stack's top, computes them,
and pushes the resulting value back onto the stack.
*/

fn write_arithmetic(command : Command) -> Result<Vec<String>, ErrorKind> {
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
    ].into_iter().collect();

    let mut result : Vec<String> = Vec::new();

    // Adding SP-- to the result
    result.extend(vec!["@SP", "AM=M-1", "D=M", "A=A-1"].iter().map(|x| x.to_string()));


    let operation = command.arg1.to_string();
    let op = mapping.get(operation.as_str()).unwrap();
    match operation.as_str() {
        "add" | "sub" | "and" | "or" => {
            result.push(format!("M=M{}D", op));
        },
        "eq" | "gt" | "lt" => {
            return Err(ErrorKind::InvalidInput);
        },
        _ => {
            return Err(ErrorKind::InvalidInput);
        }
    }
    return result;
}

/*
Push Segment Index:
- Pushes the value of segment[index] onto the stack. Where segment is: argument
local, static, constant, this, that, pointer, or temp, and index is a nonnegative
integer.

Pop Segment Index:
- Pops the top stack value and stores it in segment[index], where segment is
argument, local, static, this, that, pointer, or temp and index is a nonnegative 
integer.

*/

fn write_pushpop(command : CommandType, segment : &str, index : i16) {
    return ();
}
