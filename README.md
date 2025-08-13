# Minishell

A simple shell implementation in C that mimics basic functionality of bash. This project implements a command-line interpreter with support for pipes, redirections, environment variables, and built-in commands.

## Features

- **State Machine Parser/Lexer**: Robust parsing system using finite state machine for tokenization and syntax analysis
- **Multiprocess Execution**: Parallel execution of pipeline commands for optimal performance
- **Built-in Commands**: Support for `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- **Redirections**: Input (`<`), output (`>`), and append (`>>`) redirections
- **Pipes**: Command chaining with pipe (`|`) operator
- **Environment Variables**: Variable expansion and management (`$VAR`, `${VAR}`, `$?`)
- **Signal Handling**: Proper handling of `Ctrl+C` (SIGINT), `Ctrl+D` (EOF), and `Ctrl+\` (SIGQUIT)
- **History**: Command history using readline library

## Prerequisites

Before compiling the project, you need to install the readline library:

### Ubuntu/Debian:

    sudo apt-get update
    sudo apt-get install libreadline-dev

### macOS (with Homebrew):

    brew install readline

### CentOS/RHEL/Fedora:

    # For CentOS/RHEL
    sudo yum install readline-devel
    
    # For Fedora
    sudo dnf install readline-devel

### Arch Linux:

    sudo pacman -S readline

## Installation

1. Clone the repository:

       git clone https://github.com/muhsinalikulbak/Minishell.git
       cd Minishell

2. Compile the project:

       make

## Makefile Commands

- **`make`**: Compiles the project and creates the `minishell` executable
- **`make re`**: Recompiles the entire project from scratch (equivalent to `make fclean` + `make`)
- **`make clean`**: Removes all object files (`.o` files) but keeps the executable
- **`make fclean`**: Removes all object files and the executable (complete cleanup)

## Usage

Run the shell:

    ./minishell

Once started, you can use it like a regular shell:

    minishell$ echo "Hello World"
    Hello World
    minishell$ ls -la | grep minishell
    -rwxr-xr-x 1 user user 45678 Dec 10 15:30 minishell
    minishell$ export MY_VAR=42
    minishell$ echo $MY_VAR
    42
    minishell$ echo "Exit status: $?"
    Exit status: 0
    minishell$ echo "Shell PID: $$"
    Shell PID: 12345
    minishell$ cat < input.txt > output.txt
    minishell$ ls | wc -l | cat -e
    15$
    minishell$ exit

### Supported Commands

#### Built-in Commands:
- `echo [-n]` - Display text
- `cd [path]` - Change directory
- `pwd` - Print working directory
- `export [var=value]` - Set environment variable
- `unset [var]` - Unset environment variable
- `env` - Display environment variables
- `exit [code]` - Exit the shell

#### External Commands:
- Any executable in `PATH`
- Support for absolute and relative paths

### Special Features:
- **Pipes**: `command1 | command2 | command3`
- **Redirections**: 
  - `command > file` (output redirection)
  - `command >> file` (append redirection)
  - `command < file` (input redirection)
- **Environment Variables**: 
  - `$VAR` or `${VAR}` - Variable expansion
  - `$?` - Exit status of last command
  - `$$` - Process ID of shell
- **Command History**: Use arrow keys to navigate through previous commands

## Architecture

### Parser/Lexer (State Machine)
The parsing system uses a finite state machine approach to tokenize and parse input:
- **Lexical Analysis**: Converts input string into tokens
- **Syntax Analysis**: Validates command structure and builds parse tree
- **State Management**: Handles quotes, escapes, and special characters

### Executor (Multiprocess)
The execution system implements parallel processing for pipeline commands:
- **Process Creation**: Each pipeline segment runs in its own process
- **IPC Management**: Proper pipe setup and file descriptor handling
- **Synchronization**: Parent process waits for all child processes
- **Resource Cleanup**: Automatic cleanup of processes and file descriptors

### Variable Expansion
The shell supports comprehensive variable expansion:
- **Environment Variables**: `$HOME`, `$PATH`, `$USER` etc.
- **Custom Variables**: Variables set with `export`
- **Special Variables**:
  - `$?` - Exit status of the last executed command
  - `$$` - Process ID of the current shell
- **Expansion in Quotes**: 
  - Double quotes: Variables are expanded
  - Single quotes: Variables are treated literally
- **Parameter Expansion**: `${VAR}` syntax for complex cases

### Signal Handling
The shell implements proper signal management:
- **SIGINT (Ctrl+C)**:
  - In interactive mode: Displays new prompt on new line
  - During command execution: Terminates current command
  - Exit status set to 130
- **SIGQUIT (Ctrl+\)**:
  - Ignored in interactive mode
  - During command execution: Terminates with core dump
  - Exit status set to 131
- **EOF (Ctrl+D)**:
  - Exits the shell gracefully
  - Prints "exit" message
- **Signal Inheritance**: Child processes receive appropriate signal handling

## Error Handling

The shell handles various error conditions gracefully:
- Invalid commands and syntax errors
- File permission issues
- Memory allocation failures
- Signal interruptions
- Pipe and redirection errors

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

## License

This project is part of the 42 School curriculum and follows the school's academic guidelines.
