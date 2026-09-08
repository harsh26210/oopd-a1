# OOPD Monsoon 2026 - Assignment 1

This repository contains my implementation of Assignment 1 for Object-Oriented Programming and Design (OOPD), Monsoon 2026.

The main purpose of this assignment was to understand how a C++ program works at a lower level when the usual C/C++ runtime and standard libraries are not used. The programs were built using C++, NASM assembly, and direct Linux system calls.

## Q2 - Basic C++ Program Without Standard Libraries

The first program is `hello.cpp`. It contains a minimal `main()` function which simply returns 0.

The main objective of this question was to understand how a C++ program can be compiled and linked without using the normal standard library files.

The build process uses:

- `g++ -c` to compile the C++ source into an object file.
- `nasm -f elf64` to assemble `syscall.S`.
- `-nostdlib` while linking, so the normal C/C++ standard libraries and startup files are not linked.
- `-no-pie` to build the executable without position-independent executable support, which keeps the linking process compatible with the custom `_start` entry point used in the assembly file.

The assembly file provides `_start`, which calls `main`, and then uses the Linux `exit` system call to terminate the program.

`-fno-stack-protector` is used for the programs that contain C++ functions because the compiler can otherwise insert stack-protection code which depends on runtime library functions such as `__stack_chk_fail`. Since the assignment does not allow the standard C/C++ libraries, this compiler-generated dependency is disabled.

## Q3 - Input and Confirmation Using Direct System Calls

In Q3, the program was extended to ask the user for their name and age and then ask for confirmation using `y` or `n`.

The program does not use `iostream`, `stdio`, `string`, or other standard C/C++ libraries. Instead, input and output are performed through Linux system calls.

The `basicIO` class provides functions such as:

- `inputint()` for reading an integer.
- `inputstring()` for reading a string.
- `outputint()` for displaying an integer.
- `outputstring()` for displaying text.
- `errorstring()` for displaying error messages.

The actual system-call interface is provided by `syscall.S`.

Input validation was also added. For example, the age is checked to make sure that it is within a valid range, and the confirmation input is checked for `y` or `n`.

The `nasm` assembler is required to build the `.S` file, as specified in the assignment.

## Q4 - Dynamic Number of Names and Overflow Prevention

Q4 extends the previous program so that the user first specifies how many names are required.

Instead of using C++ dynamic allocation through `new`, memory is allocated directly using the Linux `mmap` system call. This keeps the implementation independent of the standard C++ library.

Each name is given a fixed maximum size of 100 bytes. The total memory requested is calculated as:

    numberOfNames * MAX_NAME_LENGTH

A maximum limit on the number of names is also checked before allocation. This prevents an unreasonable number of names from being requested.

The input function was improved so that a name cannot overflow its allocated space. Only the allowed number of characters is stored, while any remaining characters from an excessively long input are consumed until the newline. This prevents leftover characters from interfering with the next input.

The allocated memory is released using the Linux `munmap` system call after it is no longer required.

Q4 was implemented in `main2.cpp` and was committed on a separate Git branch as required by the assignment.

## Q5 - Changing the Number of Names

Q5 extends Q4 by allowing the user to change the number of names after the first set of names has been entered.

If the user chooses `y`, a new number of names is requested. The previously allocated memory is first released using `munmap`, and a new memory region is then allocated using `mmap` based on the new number of names.

The new names are then entered into the newly allocated memory.

The program also validates the new number of names before performing the new allocation. This prevents invalid values from being used.

Q5 is implemented in `main3.cpp` as an additional commit on the Q4 branch.

## Assembly System Call Interface

The `syscall.S` file provides wrappers around Linux system calls.

`syscall3` is used when a system call requires up to three arguments, while `syscall6` supports system calls with up to six arguments.

The assembly code converts the C++ function arguments into the registers expected by the x86-64 Linux system-call convention and then executes the `syscall` instruction.

This allows the C++ programs to perform input, output, memory allocation, memory release, and program termination without relying on standard C/C++ libraries.

## Build Scripts

Separate shell scripts are provided for each stage:

- `build_q2.sh` - builds Q2.
- `build_q3.sh` - builds Q3.
- `build_q4.sh` - builds Q4.
- `build_q5.sh` - builds Q5.

The scripts contain the compilation, assembly, and linking commands required to reproduce each program.


## Use of AI as a Learning Aid

AI tools  were used during the development process as a learning and debugging aid. This was used to understand compiler and linker options, Linux system calls, assembly instructions, memory allocation concepts, Git/GitHub procedures, and errors encountered during compilation or testing.

The submitted programs were developed and understood through the implementation and understanding the commands of testing process by myself. AI was used to explain concepts, commands, errors, and possible approaches rather than simply generating the assignment solutions 
