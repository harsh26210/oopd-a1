#!/bin/bash

g++ -fno-stack-protector -c hello.cpp -o hello.o
nasm -f elf64 syscall.S -o syscall.o
g++ -nostdlib -no-pie hello.o syscall.o -o q2
