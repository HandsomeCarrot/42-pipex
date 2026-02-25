# pipex

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
- [Configuration](#configuration)
- [Troubleshooting](#troubleshooting)
- [Project Status](#project-status)
- [License](#license)

## Overview

pipex is a command-line utility that mimics the behavior of shell pipes in Unix-like systems. The program replicates the functionality of the bash pipe operator (`|`) by executing two commands in sequence, where the output of the first command becomes the input to the second command. This project is part of the 42 school curriculum and serves as a practical exercise in process management, file descriptors, and inter-process communication using pipes.

The program demonstrates low-level Unix system programming concepts, including `fork()`, `pipe()`, `dup2()`, and `execve()`, providing hands-on experience with how shell pipelines work under the hood.

## Features

- Executes two commands connected by a pipe, mimicking shell behavior
- Reads input from a specified file and writes output to another file
- Validates command existence by searching through PATH environment variable
- Supports both absolute and relative command paths
- Provides detailed error messages for file access issues and command failures
- Handles proper cleanup of file descriptors and child processes
- Returns appropriate exit codes following Unix conventions (127 for command not found, 126 for execution failure)

## Getting Started

### Prerequisites

- GCC or compatible C compiler
- Make build system
- Unix-like operating system (Linux, macOS, or BSD)
- Standard C library with POSIX support

### Installation

1. Clone the repository:
```bash
git clone https://github.com/HandsomeCarrot/42-pipex.git
cd 42-pipex
```

2. Build the project:
```bash
make
```

This compiles the pipex executable along with the required libft library. The Makefile supports the following targets:
- `make` or `make all`: Build the pipex executable
- `make clean`: Remove object files
- `make fclean`: Remove object files and executable
- `make re`: Rebuild the entire project from scratch

## Usage

The pipex program requires exactly four arguments and follows this syntax:

```bash
./pipex file1 cmd1 cmd2 file2
```

This is equivalent to the shell command:
```bash
< file1 cmd1 | cmd2 > file2
```

### Parameters

- `file1`: Input file to read from
- `cmd1`: First command to execute (receives input from file1)
- `cmd2`: Second command to execute (receives input from cmd1's output)
- `file2`: Output file to write to (created with permissions 0644)

### Examples

1. Count lines in a file after filtering:
```bash
./pipex input.txt "grep hello" "wc -l" output.txt
```
Equivalent to: `< input.txt grep hello | wc -l > output.txt`

2. Process text data:
```bash
./pipex data.txt "cat" "tr 'a-z' 'A-Z'" uppercase.txt
```
Equivalent to: `< data.txt cat | tr 'a-z' 'A-Z' > uppercase.txt`

3. Using absolute paths:
```bash
./pipex input.txt "/bin/ls -l" "/usr/bin/head -n 5" output.txt
```

## Configuration

The program uses the following system configurations:

### Environment Variables

- `PATH`: Used to locate executable commands. The program searches each directory in PATH to find the specified commands.

### File Permissions

- Output files are created with permissions `0644` (owner read/write, group/others read-only).

### Exit Codes

- `0`: Successful execution
- `1`: General errors (file access issues, missing arguments)
- `126`: Command execution failed
- `127`: Command not found

## Troubleshooting

### Common Issues

**Issue: "command not found" error**
- Verify the command exists in your PATH: `which <command>`
- Try using the absolute path to the command
- Ensure the command name is spelled correctly

**Issue: Input/output file errors**
- Check file permissions: `ls -l <filename>`
- Verify the input file exists and is readable
- Ensure you have write permissions in the directory for the output file

**Issue: "exactly 4 arguments needed" error**
- Verify you are passing exactly four arguments to pipex
- Use quotes around commands with spaces or special characters: `./pipex in.txt "grep -i test" "wc -l" out.txt`

**Issue: Compilation errors**
- Ensure you have a compatible C compiler installed
- Check that all source files are present in the repository
- Try running `make fclean && make` to rebuild from scratch

**Issue: Program hangs or doesn't complete**
- Check that both commands are valid and can execute independently
- Verify the input file is not empty if commands expect input
- Ensure commands don't require interactive input

## Project Status

This project appears to be actively maintained based on recent commits in February 2025. The latest updates focus on improving error handling, code documentation, and memory management. The project is suitable for educational purposes and demonstrates a functional implementation of Unix pipe mechanics.

## License

No license.
