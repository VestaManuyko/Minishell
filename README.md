# minishell
42 Vienna assignment: reproduce a subset of the functionalities of a shell

Some interesting starting points:

** Git 42 guide ** \
Quick overview of the minishell \
https://42-cursus.gitbook.io/guide/3-rank-03/minishell

**Abstract syntax tree (AST)** \
A method to parse content based on lexical tokens: \
https://en.wikipedia.org/wiki/Abstract_syntax_tree.

**Bash Manual** \
https://www.gnu.org/savannah-checkouts/gnu/bash/manual/

# Summary overview of the allowed functions:

## **Readline and History Functions**

readline: Reads a line of input from the user with line-editing features (arrows, history navigation).

rl_clear_history: Clears all the lines stored in the Readline history.

rl_on_new_line: Tells Readline that the cursor is on a new line (helps keep display consistent).

rl_replace_line: Replaces the current input line buffer with a given string.

rl_redisplay: Redraws the current input line on the terminal.

add_history: Adds a line to the input history (so it can be recalled later with ↑).

👉 These work together: readline gathers input, you can add_history to save it, and functions like rl_replace_line or rl_redisplay manipulate what the user sees.

## **Standard I/O and Memory**

printf: Prints formatted output to stdout.

malloc: Allocates memory dynamically.

free: Frees memory previously allocated by malloc.

write: Low-level function to write raw data to a file descriptor.

👉 printf is built on top of write. malloc/free are often used to handle strings or buffers for I/O.

## **File and Process Management**

access: Checks if a file can be accessed with certain permissions.

open: Opens a file and returns a file descriptor.

read: Reads raw bytes from a file descriptor.

close: Closes a file descriptor.

👉 These form the basic workflow: check existence (access), open it, read or write, then close.

## **Process Control**

fork: Creates a new process (child is a copy of the parent).

wait, waitpid, wait3, wait4: Wait for child processes to change state (exit, stop, etc.).

execve: Replaces the current process image with a new program.

exit: Terminates the current process with a status code.

kill: Sends a signal to a process.

👉 Typical flow: fork → child calls execve to run another program → parent calls wait/waitpid to monitor it. kill is used to control processes via signals.

## **Signals**

signal: Assigns a handler for a given signal (simpler but less portable).

sigaction: More powerful, preferred way to define signal handlers.

sigemptyset: Initializes an empty signal set.

sigaddset: Adds a signal to a signal set.

👉 Used for handling events like Ctrl-C (SIGINT). sigaction replaces signal for robust control.

## **File System Info**

getcwd: Gets current working directory.

chdir: Changes working directory.

stat, lstat, fstat: Get file metadata (permissions, size, timestamps).

unlink: Removes a file (like rm).

👉 Often used together to implement shell-like behavior (cd, ls -l, rm).

## **File Descriptors and Pipes**

dup: Duplicates a file descriptor.

dup2: Duplicates one descriptor into another specific one.

pipe: Creates a pair of file descriptors for inter-process communication (read/write ends).

👉 Shells use these for redirection and pipelines (ls | grep foo).

## **Directories**

opendir: Opens a directory stream.

readdir: Reads entries in a directory (like ls).

closedir: Closes the directory stream.

## **Error Handling**

strerror: Returns human-readable string for an error code (errno).

perror: Prints the last error message automatically with context.

## **Terminal and TTY**

isatty: Checks if a file descriptor is a terminal.

ttyname: Gets the name of the terminal device.

ttyslot: Returns the slot number of the terminal in the utmp file.

ioctl: Generic interface to control device parameters (often terminals).

👉 Useful for programs that behave differently when run interactively vs piped.

## **Environment**

getenv: Fetches the value of an environment variable (like $PATH).

Terminal Attributes (termios)

tcsetattr: Sets terminal attributes (echo, raw mode, etc.).

tcgetattr: Gets current terminal attributes.

Termcap (legacy terminal control)

tgetent: Loads terminal entry from termcap database.

tgetflag: Gets a boolean capability (e.g., terminal supports auto-wrap).

tgetnum: Gets numeric capability (e.g., number of columns).

tgetstr: Gets string capability (e.g., clear screen sequence).

tgoto: Computes cursor movement escape sequence.

tputs: Outputs a control string to the terminal with padding.

👉 These functions are used for low-level terminal control (before curses/ncurses). They relate closely to readline which builds on terminal capabilities.


## **How They Correlate**

Readline + History: Provides user-friendly input handling, built on top of terminal/termcap.

Standard I/O + Syscalls: printf, malloc/free manage data; read, write, open, close are the low-level building blocks.

Processes + Signals: fork, execve, wait*, and kill are the backbone of process management. Signals (sigaction) integrate with them.

File system + Directories: stat, lstat, fstat, opendir/readdir/closedir handle filesystem operations.

Terminal Control: isatty, ioctl, tcsetattr/tcgetattr, and termcap functions allow fine-grained terminal interaction.


In short:

Shells (like bash) use almost all of these:

readline for input

add_history to remember commands

fork + execve to run programs

waitpid to manage them

dup2 + pipe for redirection/pipelines

stat, opendir for file operations

isatty, tcsetattr, tgetstr for terminal handling
