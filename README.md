# OOPD Monsoon 2026 - Assignment 1

This repository contains my implementation of Assignment 1 for Object-Oriented Programming and Design (OOPD), Monsoon 2026.

The main purpose of this assignment is to understand how a C++ program works at a lower level when the usual C/C++ runtime and standard libraries are not used. The programs are implemented using C++, NASM assembly and direct Linux system calls.

## Q2 - Basic C++ Program Without Standard Libraries

Q2 starts with a very simple C++ program, `MT26210_hello.cpp`, whose `main()` function only returns 0.

The purpose of this question is to understand how a C++ program can be compiled and linked without the normal C/C++ library files.

The build process is placed in `MT26210_build_q2.sh`.

The main options and commands used are:

- `g++ -c` compiles the C++ source into an object file.
- `nasm -f elf64` assembles the supplied `syscall.S` file.
- `-nostdlib` prevents the normal startup files and standard libraries from being used during linking.
- `-no-pie` is used so that the executable can be linked with the custom `_start` entry point provided by the assembly file.
- `-fno-stack-protector` prevents the compiler from generating a dependency on runtime functions such as `__stack_chk_fail`, which cannot be used when the standard libraries are excluded.

The supplied assembly file provides `_start`. It calls `main()` and then uses the Linux `exit` system call to terminate the program.

## Q3 - Input, Output and Confirmation

Q3 extends the basic program so that the user can enter their name and age and then confirm the entered information using `y` or `n`.

The main program is `MT26210_main.cpp` and its build process is provided in `MT26210_build_q3.sh`.

Standard C/C++ input and output libraries are not used. Instead, the `basicIO` class provides functions for input, output and error messages using direct Linux system calls.

Examples of the functions used include:

- `inputint()` for reading an integer.
- `inputstring()` for reading a string.
- `outputint()` for displaying an integer.
- `outputstring()` for displaying text.
- `errorstring()` for displaying error messages.

The supplied `syscall.S` file provides the assembly interface used by the C++ code to perform Linux system calls.

Input validation is included for the entered name, age and confirmation choice.

The `nasm` assembler is used to assemble the supplied `.S` file.

## Q4 - Dynamic Number of Names

Q4 extends the Q3 program so that the user first enters the number of names required.

The program is implemented in `MT26210_main2.cpp` and uses `MT26210_basicIO2.cpp`.

Instead of using C++ dynamic allocation through `new`, memory is allocated directly using the Linux `mmap` system call. The allocated memory is released using `munmap`.

Each name is given a fixed maximum size of 100 bytes. Therefore, the required memory is calculated using:

    numberOfNames * MAX_NAME_LENGTH

The number of names is also checked against a maximum limit before memory allocation.

The string input function ensures that a name cannot exceed its allocated space. If the user enters more characters than the allowed size, the extra characters are discarded until the end of the input line. This prevents overflow and prevents leftover input from affecting the next name.

The Q4 build process is provided in `MT26210_build_q4.sh`.

Q4 is committed on the separate `q4` branch as required by the assignment.

## Q5 - Changing the Number of Names

Q5 extends Q4 by allowing the user to change the number of names after the first set of names has been entered.

The program is implemented in `MT26210_main3.cpp` and its build process is provided in `MT26210_build_q5.sh`.

If the user chooses to change the number of names, the old memory allocation is released using `munmap`. A new memory region is then allocated using `mmap` according to the new number of names.

The new number of names is validated before the new memory allocation is performed.

Q5 is added as a new commit on the Q4 branch.

## Assembly System Call Interface

The supplied `syscall.S` file provides wrappers for Linux system calls.

`syscall3` is used for system calls requiring up to three arguments, while `syscall6` supports system calls requiring up to six arguments.

The assembly code places the system call number and its arguments into the registers required by the x86-64 Linux system-call convention and executes the `syscall` instruction.

This allows the C++ programs to perform input, output, memory allocation, memory deallocation and program termination without using the standard C/C++ libraries.

## Build Scripts

Separate shell scripts are provided for the different stages of the assignment:

- `MT26210_build_q2.sh` - builds Q2.
- `MT26210_build_q3.sh` - builds Q3.
- `MT26210_build_q4.sh` - builds Q4.
- `MT26210_build_q5.sh` - builds Q5.

The scripts contain the compilation, assembly and linking commands required to reproduce the corresponding programs.

A `Makefile` is also included to provide a standard way to build the programs.

Object files and generated executable files are not part of the repository because the assignment requires that binary or library files must not be committed.

## File Naming

The files written as part of the assignment follow the required roll-number naming convention:

    MT26210_NameOfTheFile.extension

The supplied files retain their original names. `README.md` and `Makefile` also retain their standard names.

The required roll number and name are included as comments at the beginning of the applicable files.

## Use of AI as a Learning Aid

AI tools were used as a learning and debugging aid during the development of this assignment. They were used to understand compiler and linker options, Linux system calls, assembly instructions, memory allocation concepts, Git/GitHub procedures and errors encountered during compilation and testing.

The concepts, commands and implementation were studied and tested during the development process. AI was used to understands concepts and errors and to help understand possible approaches.
