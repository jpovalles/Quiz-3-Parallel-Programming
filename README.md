# Quiz-3-Parallel-Programming
# Compilation Instructions

To compile each program using `g++`, use the following commands:
## Standard compilation
```sh
g++ -o <exec_name> <program_name.c>
```

## OMP tagged programs:
```sh
g++ -fopenmp -o <exec_name> <program_name.c>
```

## Pthreads tagged programs:
```sh
g++ -pthread -o <exec_name> <program_name.c>
```
