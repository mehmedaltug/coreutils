# CoreUtils

A lightweight, ground-up reimplementation of classic Unix core utilities written in standard C. Built as a hands-on project to explore system-level POSIX tools, low-level string handling, and manual memory management.

---

## Technical Highlights

* **Custom String Struct:** Replaced raw `char*` arrays with a custom `String` struct featuring dynamic memory resizing, bounds checking, and custom string manipulation helpers.
* **Hybrid Test Suite:** Uses Python integration tests and C function tests to assert stdout, stderr, and exit codes directly against the system's native Unix utilities.
* **Cross Platform:** Uses universal functions and standard libraries to create a suitable set for Windows and Linux (possibly MacOS too, testing required).

---

## Utility Status

| Utility | Status | Description |
| --- | --- | --- |
| `echo` | **Implemented** | Print user input to the console |
| `ls` | **Implemented** | List directory contents |
| `cat` | **Implemented** | Concatenate and display file contents |
| `cut` | **Implemented** | Extract sections from lines of standard input/files |
| `pwd` | **Implemented** | Print current working directory |
| `clear` | **Implemented** | Clear the terminal screen |
| `head` | **Implemented** | Output the first portion of files |
| `tail` | **Implemented** | Output the last portion of files |
| `grep` | **Implemented** | Search for patterns within text |

---

## Architecture Overview

* **`src/`** — Entry points and logic for individual core utility binaries.
* **`lib/`** — Shared headers, core helper functions, and the custom `String` struct implementation.
* **`tests/`** — Python and C test suite comparing compiled binary outputs against native POSIX tools.

---

## Building & Testing

**Prerequisites**

* `gcc` or `clang`
* `bash`
* `python3`

**Commands**

```bash
# Build all utilities
make

# Build specific utilities
make TOOL_NAME

# Run tests
make test

```
