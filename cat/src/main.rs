use std::{env, fs};

fn main() {
    let args = env::args();
    let mut files: Vec<String> = vec![];
    let mut skip = false;
    for arg in args {
        if !skip {
            skip = true;
            continue;
        }
        files.push(arg.to_string());
    }

    for file in files {
        print!("{}", fs::read_to_string(file).unwrap());
    }
}
