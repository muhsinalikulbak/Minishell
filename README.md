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

      git clone [your-repository-url]
      cd minishell

2. Compile the project:

      make

## Makefile Commands

- **`make`**: <span style="color: green;">Compiles the project and creates the `minishell` executable</span>
- **`make re`**: <span style="color: orange;">Recompiles the entire project from scratch (equivalent to `make fclean` + `make`)</span>
- **`make clean`**: <span style="color: yellow;">Removes all object files (`.o` files) but keeps the executable</span>
- **`make fclean`**: <span style="color: red;">Removes all object files and the executable (complete cleanup)</span>

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
- <span style="color: blue;">`echo [-n]`</span> - Display text
- <span style="color: blue;">`cd [path]`</span> - Change directory
- <span style="color: blue;">`pwd`</span> - Print working directory
- <span style="color: blue;">`export [var=value]`</span> - Set environment variable
- <span style="color: blue;">`unset [var]`</span> - Unset environment variable
- <span style="color: blue;">`env`</span> - Display environment variables
- <span style="color: blue;">`exit [code]`</span> - Exit the shell

#### External Commands:
- Any executable in `PATH`
- Support for absolute and relative paths

### Special Features:
- **Pipes**: `command1 | command2 | command3`
- **Redirections**: 
 - <span style="color: purple;">`command > file`</span> (output redirection)
 - <span style="color: purple;">`command >> file`</span> (append redirection)
 - <span style="color: purple;">`command < file`</span> (input redirection)
- **Environment Variables**: 
 - <span style="color: green;">`$VAR` or `${VAR}`</span> - Variable expansion
 - <span style="color: orange;">`$?`</span> - Exit status of last command
 - <span style="color: orange;">`$$`</span> - Process ID of shell
- **Command History**: Use arrow keys to navigate through previous commands

## Architecture

### 🔧 Parser/Lexer (State Machine)
The parsing system uses a finite state machine approach to tokenize and parse input:
- **Lexical Analysis**: Converts input string into tokens
- **Syntax Analysis**: Validates command structure and builds parse tree
- **State Management**: Handles quotes, escapes, and special characters

### ⚡ Executor (Multiprocess)
The execution system implements parallel processing for pipeline commands:
- **Process Creation**: Each pipeline segment runs in its own process
- **IPC Management**: Proper pipe setup and file descriptor handling
- **Synchronization**: Parent process waits for all child processes
- **Resource Cleanup**: Automatic cleanup of processes and file descriptors

### 🔄 Variable Expansion
The shell supports comprehensive variable expansion:
- **Environment Variables**: <span style="color: green;">`$HOME`, `$PATH`, `$USER`</span> etc.
- **Custom Variables**: Variables set with `export`
- **Special Variables**:
 - <span style="color: orange;">`$?`</span> - Exit status of the last executed command
 - <span style="color: orange;">`$$`</span> - Process ID of the current shell
- **Expansion in Quotes**: 
 - <span style="color: green;">Double quotes</span>: Variables are expanded
 - <span style="color: red;">Single quotes</span>: Variables are treated literally
- **Parameter Expansion**: <span style="color: blue;">`${VAR}`</span> syntax for complex cases

### 🚦 Signal Handling
The shell implements proper signal management:
- **SIGINT (Ctrl+C)**:
 - In interactive mode: <span style="color: green;">Displays new prompt on new line</span>
 - During command execution: <span style="color: red;">Terminates current command</span>
 - Exit status set to <span style="color: orange;">130</span>
- **SIGQUIT (Ctrl+\)**:
 - <span style="color: yellow;">Ignored in interactive mode</span>
 - During command execution: <span style="color: red;">Terminates with core dump</span>
 - Exit status set to <span style="color: orange;">131</span>
- **EOF (Ctrl+D)**:
 - <span style="color: blue;">Exits the shell gracefully</span>
 - Prints "exit" message
- **Signal Inheritance**: Child processes receive appropriate signal handling

## Error Handling

The shell handles various error conditions gracefully:
- <span style="color: red;">Invalid commands and syntax errors</span>
- <span style="color: orange;">File permission issues</span>
- <span style="color: red;">Memory allocation failures</span>
- <span style="color: yellow;">Signal interruptions</span>
- <span style="color: orange;">Pipe and redirection errors</span>

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

## License

This project is part of the **42 School** curriculum and follows the school's academic guidelines.
