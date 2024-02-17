pub mod codewriter;
pub mod io;
pub mod parser;

use codewriter::write_code;
use io::{clean_file, read_file};
use parser::{build_command_list, get_command_type, Command};
use std::iter::FromIterator;
use std::{collections::HashMap, fs::File, hash::Hash, io::Read};

const FILENAME: &str = "test/SimpleAdd.vm";
const OUT_FILE: &str = "test/SimpleAdd.asm";
const SP: i16 = 256;

/*
Global Stack
0-15 : Virtual Registers
16-255 : Static Variables
256-2047 : Stack

RAM
SP - RAM[0] - points to the next available location in the stack
LCL - RAM[1] - points to the base of the current VM function's local segment
ARG - RAM[2] - points to the base of the current VM function's argument segment
THIS - RAM[3] - points to the base of the current this segment
THAT - RAM[4] - points to the base of the current that segment
TEMP - RAM[5-12] - points to the base of the temp segment
R13-R15 - RAM[13-15] - general purpose registers
*/

// RAM
struct RAM {
    memory: HashMap<i16, i32>,
}

impl RAM {
    fn new() -> Self {
        let mut memory = HashMap::new();
        memory.insert(0, 256);
        return RAM { memory };
    }
}

// Virtual Memory

#[derive(Debug)]
struct MemoryCell {
    address: usize,
    value: i32,
}

fn main() {
    let contents = read_file(FILENAME);
    let cleansed_file = clean_file(contents);
    let commands = build_command_list(cleansed_file);
    let out_file = File::create(OUT_FILE);

    let mut stack = Vec::<i16>::new();
    let mut ram = RAM::new();
    let asm: Vec<String> = Vec::new();
    for command in commands {
        let i_asm = codewriter::write_code(command, function, index);
        match i_asm {
            Ok(i_asm) => {
                asm.extend(i_asm);
            }
            Err(i_asm) => {}
        }
    }
    return;
}
