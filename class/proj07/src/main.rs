pub mod parser;
pub mod io;
pub mod codewriter;

use std::{fs::File, io::Read};
use io::{clean_file, read_file};
use parser::{build_command_list, get_command_type, Command};

const FILENAME : &str = "test/SimpleAdd.vm";
const OUT_FILE : &str = "test/SimpleAdd.asm";
const SP : i16 = 256;

/*
Ram Usage

0-15 : Virtual Registers
16-255 : Static Variables
256-2047 : Stack

SP - RAM[0] - points to the next available location in the stack
LCL - RAM[1] - points to the base of the current VM function's local segment
ARG - RAM[2] - points to the base of the current VM function's argument segment
THIS - RAM[3] - points to the base of the current this segment
THAT - RAM[4] - points to the base of the current that segment
TEMP - RAM[5-12] - points to the base of the temp segment
R13-R15 - RAM[13-15] - general purpose registers
*/ 


fn main() {
    let contents = read_file(FILENAME);
    let cleansed_file = clean_file(contents);
    let commands = build_command_list(cleansed_file);
    let out_file = File::create(OUT_FILE);
}


