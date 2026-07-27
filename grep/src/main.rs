use std::{env, fs, io::Read};

fn text_grep(pattern: String) {
    let mut input = String::new();
    let _ = std::io::stdin().read_to_string(&mut input);
    let lines = input.split("\n");
    let found = lines.filter(|x| x.contains(&pattern));
    for line in found {
        println!("{}", line);
    }
}
fn file_grep(pattern: String, file_name: String) {
    let file = fs::read_to_string(file_name);
    if file.is_err() {
        println!("Failed to read the file");
        return;
    }
    let content = file.unwrap();
    let lines = content.split("\n");
    let found = lines.filter(|x| x.contains(&pattern));
    for line in found {
        println!("{}", line);
    }
}

fn main() {
    let mut args = env::args();
    let args_len = args.len();
    if args_len == 2 {
        let pattern = args.nth(1).unwrap();
        text_grep(pattern);
        return;
    } else if args_len == 3 {
        let pattern = args.nth(1).unwrap();
        let file_name = args.nth(0).unwrap();
        file_grep(pattern, file_name);
        return;
    }
    println!("Invalid number of arguments!");
    return;
}
