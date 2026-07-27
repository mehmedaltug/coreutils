use std::{env, fs, os::windows::fs::MetadataExt, path::Path};

const WINDOWS_DELIMITER: &str = "\\";
const UNIX_DELIMITER: &str = "/";

fn main() {
    let mut list_path: String;
    let delimiter: &str;
    if env::consts::OS.eq("windows") {
        delimiter = WINDOWS_DELIMITER;
    } else {
        delimiter = UNIX_DELIMITER;
    }
    list_path = format!(".{}", delimiter);

    let args: Vec<String> = env::args().collect();
    if args.len() > 1 {
        let path = Path::new(&args[1]);
        if path.is_dir() {
            list_path = args[1].to_string();
        } else {
            println!("Invalid path given!");
            return;
        }
    }
    if args.len() > 2 {
        println!("Invalid number of arguments!");
        return;
    }

    let paths = fs::read_dir(list_path).unwrap();
    let mut path_vec: Vec<String> = vec![];
    for path in paths {
        path_vec.push(path.unwrap().path().display().to_string());
    }
    println!(" PERM\tSIZE\tFILE NAME");
    for path in path_vec {
        print_info(path, delimiter);
    }
}

fn print_info(path: String, delimiter: &str) {
    let name = path.split(delimiter).last().unwrap().to_string();
    let meta = fs::metadata(path).unwrap();
    let permissions = meta.permissions().readonly();
    let mut permission_text = "rw";
    if permissions {
        permission_text = "r-"
    }
    let mut size = meta.file_size();
    let mut size_type = "B";
    if size >= 1024 {
        size /= 1024;
        size_type = "KB";
    }
    if size >= 1024 {
        size /= 1024;
        size_type = "MB";
    }
    if size >= 1024 {
        size /= 1024;
        size_type = "GB";
    }
    let file_type = meta.file_type().is_dir();
    let mut file_type_text = "-";
    if file_type {
        file_type_text = "d";
    }
    println!(
        " {}{}\t{}{}\t{}",
        file_type_text, permission_text, size, size_type, name
    );
}
