*This project has been created as part of the 42 curriculum by vpoka.*

# pipex

Recreating the shell pipeline `< file1 cmd1 | cmd2 > file2` in C.

## Table of Contents
- [Description](#description)
- [Instructions](#instructions)
  - [Prerequisites](#prerequisites)
  - [Building](#building)
  - [Usage](#usage)
  - [Parameters](#parameters)
  - [Examples](#examples)
- [Resources](#resources)
  - [AI usage](#ai-usage)
- [Configuration](#configuration)
- [Troubleshooting](#troubleshooting)
- [Status](#status)

## Description

pipex is a command-line program that reproduces exactly what the shell does for a two-command pipeline. You give it an input file, two shell commands and an output file, and it runs the first command on the input, pipes its output into the second command, and writes the result to the output file — the same as `< file1 cmd1 | cmd2 > file2`.

It is a 42 school project meant to let you discover in detail a UNIX mechanism you already use every day. Under the hood it works with the raw building blocks of a shell pipeline: `fork()`, `pipe()`, `dup2()`, `execve()` and `waitpid()`, with careful handling of file descriptors, paths and error cases.

Features:

- Executes two commands connected by a pipe, mimicking shell behavior
- Reads input from a given file and writes output to another file (created or truncated)
- Resolves commands through the `PATH` environment variable, and also accepts absolute or relative command paths
- Reports errors like the shell does, with exit codes following Unix conventions (127 for command not found, 126 for execution failure)
- Cleans up file descriptors and child processes properly
- Builds on the project's own `libft` library (authorized by the subject)

The mandatory part (exactly two commands) is implemented; the bonus features (multiple pipes, `here_doc`) are not included.

## Instructions

### Prerequisites

- A C compiler (`cc`, as used by the Makefile)
- GNU Make
- A POSIX system (Linux, macOS or BSD)
- No external libraries: `libft` is bundled in the repository

### Building

```bash
make
```

This compiles `libft` with its own Makefile first, then links the `pipex` executable. The sources are compiled with `-Wall -Wextra -Werror` and the Makefile does not relink.

Available targets:

- `make` or `make all`: build the `pipex` executable
- `make clean`: remove object files (project and libft)
- `make fclean`: remove object files and the executable
- `make re`: rebuild everything from scratch

### Usage

```bash
./pipex file1 cmd1 cmd2 file2
```

This behaves exactly like the shell command:

```bash
< file1 cmd1 | cmd2 > file2
```

The program requires exactly four arguments; otherwise it prints `exactly 4 arguments needed` and exits.

### Parameters

- `file1`: input file to read from
- `cmd1`: first shell command (with its parameters); its stdin comes from `file1`
- `cmd2`: second shell command (with its parameters); its stdin comes from `cmd1`'s stdout
- `file2`: output file to write to (created with permissions `0644`, truncated if it already exists)

Commands with spaces or special characters must be quoted, as in the shell.

### Examples

From the subject:

```bash
./pipex infile "ls -l" "wc -l" outfile
```

Behaves like: `< infile ls -l | wc -l > outfile`

```bash
./pipex infile "grep a1" "wc -w" outfile
```

Behaves like: `< infile grep a1 | wc -w > outfile`

A few more:

```bash
./pipex input.txt "grep hello" "wc -l" output.txt
./pipex data.txt "cat" "tr 'a-z' 'A-Z'" uppercase.txt
./pipex input.txt "/bin/ls -l" "/usr/bin/head -n 5" output.txt
```

## Resources

- man pages: [pipe(2)](https://man7.org/linux/man-pages/man2/pipe.2.html), [fork(2)](https://man7.org/linux/man-pages/man2/fork.2.html), [execve(2)](https://man7.org/linux/man-pages/man2/execve.2.html), [dup2(2)](https://man7.org/linux/man-pages/man2/dup2.2.html), [waitpid(2)](https://man7.org/linux/man-pages/man2/waitpid.2.html)
- [GNU Bash manual — Pipelines](https://www.gnu.org/software/bash/manual/bash.html#Pipelines)
- 42 Pipex subject (version 3)

### AI usage

AI assistance was used for documentation: writing and updating this README, and for commit messages.

## Configuration

### Environment variables

- `PATH`: used to locate executable commands; each directory in `PATH` is searched to find `cmd1` and `cmd2`.

### File permissions

- Output files are created with permissions `0644` (owner read/write, group/others read-only) and truncated if they already exist.

### Exit codes

- `0`: successful execution
- `1`: general errors (bad arguments, file access issues)
- `126`: command found but execution failed
- `127`: command not found

## Troubleshooting

**"command not found" error**
- Verify the command exists in your `PATH`: `which <command>`
- Try using the absolute path to the command
- Ensure the command name is spelled correctly

**Input/output file errors**
- Check file permissions: `ls -l <filename>`
- Verify the input file exists and is readable
- Ensure you have write permissions in the directory for the output file

**"exactly 4 arguments needed" error**
- Verify you are passing exactly four arguments to pipex
- Use quotes around commands with spaces or special characters: `./pipex in.txt "grep -i test" "wc -l" out.txt`

**Compilation errors**
- Ensure `cc` and `make` are installed
- Check that all source files are present in the repository
- Try running `make fclean && make` to rebuild from scratch

**Program hangs or doesn't complete**
- Check that both commands are valid and can execute independently
- Verify the input file is not empty if commands expect input
- Ensure commands don't require interactive input

## Status

Completed — evaluated at 100/100 points.

