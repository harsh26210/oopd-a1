#!/bin/bash
# Roll No: MT26210
# Name: Harsh Dubey

g++ -fno-stack-protector -c MT26210_hello.cpp -o hello.o
nasm -f elf64 syscall.S -o syscall.o
g++ -nostdlib -no-pie hello.o syscall.o -o q2
