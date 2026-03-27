# Minishell

**Made in cooperation with:**
[Paglia Francesco](https://github.com/francescoPagliaPersonal) - [Minishell Repository](https://github.com/francescoPagliaPersonal/minishell)

Group project developed during Common Core at [42 Vienna](https://42vienna.com).

The goal of the project is to create a simple shell, a "minishell", by referring to the [Bash manual](https://www.gnu.org/savannah-checkouts/gnu/bash/manual) as our main reference and documentation.

## Dependencies

This is a Linux environment-developed project and relies on specific libraries to compile and run properly.
In particular, the `readline` library is required for reading user input, handling history, and managing the terminal interface.

To install the necessary dependencies on Ubuntu/Debian-based systems:
```bash
sudo apt-get update
sudo apt-get install build-essential libreadline-dev
```

For Arch Linux:
```bash
sudo pacman -S base-devel readline
```

For macOS (using Homebrew):
```bash
brew install readline
```

## How to use

### Build
Compile the project by running:
```bash
make
```

### Start
Launch the minishell by executing:
```bash
./minishell
```

### Run-time
Type any command you want the shell to execute. It works similarly to `bash` (look at the Bash manual for extensive reference).

### Built-in Commands
The following built-in commands are implemented and behave as they would in `bash`:

*   **`echo`**: Prints the given arguments to standard output.
    *   `-n` flag is supported to suppress the trailing newline.
*   **`cd`**: Changes the current working directory. Works with relative or absolute paths.
*   **`pwd`**: Prints the absolute path of the current working directory.
*   **`export`**: Sets an environment variable. If run without arguments, prints all exported variables.
*   **`unset`**: Unsets an environment variable.
*   **`env`**: Prints all environment variables.
*   **`exit`**: Exits the shell. You can optionally provide an exit status code (e.g., `exit 0`).

### End
To finish your session, press `Ctrl-D` or run the `exit` command by typing:
```bash
exit
```

## Short overview of functions used:

Shells (like bash) use almost all of these functions in combination to operate:
*   **Input**: `readline` and `add_history` provide user-friendly input handling and command history.
*   **Standard I/O & Memory**: `printf`, `malloc`/`free` manage data representation and dynamic allocation, while `read`, `write`, `open`, `close` provide low-level I/O.
*   **Execution & Processes**: `fork` creates a new process, `execve` runs programs inside it, and `waitpid` monitors child processes.
*   **Redirection & Pipes**: `dup2` and `pipe` allow chaining commands and redirecting inputs/outputs (e.g. `ls | grep foo`).
*   **Files & Directories**: `stat`, `opendir`/`readdir`/`closedir` and `access` handle filesystem interactions.
*   **Signals**: `sigaction` integrates robust signal control (e.g., handling Ctrl-C).
*   **Terminal Handling**: `isatty`, `tcsetattr`, and termcap functions interact fine-grainedly with terminal state and attributes.
