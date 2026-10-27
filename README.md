# pipex

A C project developed as part of the 42 curriculum, reproducing the behavior of shell pipes and redirections.

## Features

- Command execution with input and output redirection.
- Handling multiple pipes to connect several commands in a single pipeline.
- Heredoc support (`here_doc`) to read input until a specified delimiter is reached.
- Process creation and management using `fork()`, `execve()`, and `waitpid()`.
- Inter-process communication using pipes.
- File descriptor management and error handling.

## Technologies

- C
- Processes and process management
- Pipes and file descriptors
- Input/output redirection
- Shell command execution

## Build

```bash
make
```

## Usage

### Basic pipeline

```bash
./pipex infile "cmd1" "cmd2" outfile
```

Equivalent shell command:

```bash
< infile cmd1 | cmd2 > outfile
```

### Multiple pipes

```bash
./pipex infile "cmd1" "cmd2" "cmd3" "cmd4" outfile
```

Equivalent shell command:

```bash
< infile cmd1 | cmd2 | cmd3 | cmd4 > outfile
```

### Here-document

```bash
./pipex here_doc LIMITER "cmd1" "cmd2" outfile
```

Equivalent shell command:

```bash
cmd1 << LIMITER | cmd2 >> outfile
```

The program reads input until the specified delimiter is entered, then executes the pipeline and appends the output to the destination file.

## Technical Highlights

This project focuses on process creation, inter-process communication, file descriptor management, and input/output redirection. Implementing multiple pipes requires coordinating several processes and ensuring that each command receives the correct input and sends its output to the appropriate destination.

The heredoc implementation adds another input-handling mechanism, with delimiter detection and output redirection in append mode.

## Author

Developed as part of the 42 curriculum.
