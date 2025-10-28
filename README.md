# minishell

## minimal shell interpreter

_Project version : 9.0_

This project aims to create a shell interactive interpreter that mimics the behavior of the [Bourne Again Shell](https://www.gnu.org/software/bash/). It has the following features :

+ command history (with `readline`)
+ Environment variables expansion (\$VAR) and exit status (\$?)
+ Redirections (<, >, <<, >>)
+ Pipes (|)
+ Signal handling for Ctrl-C (new prompt), Ctrl-D (exit), Ctrl-\ (ignore / quit).
+ Built-ins: `echo` (-n option), `cd` (relative/absolute paths), `pwd`, `export`, `unset`, `env`, `exit`.

The goal of the `minishell` project is to deepen one's understanding of Unix system calls, inter-process communication, file descriptors, and to improve C skills. Built at [42 School](42.fr), the project focuses on low-level system programming in C, and has a strong emphasis on error handling and memory management.

### requirements

This project was made on and for **x86** systems running **Linux**. 
Additionally, `make` and a C compiler (`cc`) are needed to build the project from source.

### installation

1. Clone the repository :
```bash
git clone https://github.com/ki-ba/minishell minishell
cd minishell
```

2. Compile with `make` :
```bash
make all
```

this builds the `minishell` executable. It can then be launched with `./minishell`.

### License

[MIT License](https://mit-license.org/)
