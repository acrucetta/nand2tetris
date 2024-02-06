pub mod parser;
pub mod io;

use std::{fs::File, io::Read};
use io::{clean_file, read_file};
use parser::{build_command_list, get_command_type, Command};

fn main() {
    let test_file = "test/SimpleAdd.vm";
    let contents = read_file(test_file);
    let cleansed_file = clean_file(contents);
    let commands = build_command_list(cleansed_file);
    return ();
}


