# 42sh

{EPITECH.} first year project.

C shell that can execute commands as well as interpreting pipes, redirections, separators...

This is an evolution of [Minishell1](https://github.com/ronanboiteau/Minishell1).

This shell is based on [tcsh](https://en.wikipedia.org/wiki/Tcsh).

## Requirements

 - [A Linux distribution](https://en.wikipedia.org/wiki/Linux_distribution) or [Apple's macOS](https://en.wikipedia.org/wiki/MacOS)
 - [Make](https://www.gnu.org/software/make/)
 - [GCC](https://gcc.gnu.org/)

## Compilation

Navigate to the root of the repository from your Terminal and run `make` to build the `42sh` executable file.

## Features
 - Execute basic commands
 - Execute complex commands:
   - Separators
   - Pipes
   - Redirections
 - Can manage its own environment
 - Builtin commands:
   - `builtins`
   - `cd / chdir`
   - `echo`
   - `env [-0] [--null] [-u]`
   - `printenv`
   - `pwd`
   - `setenv`
   - `unsetenv`
 - Prompt based on last exit status
 - Support for non-interactive mode
