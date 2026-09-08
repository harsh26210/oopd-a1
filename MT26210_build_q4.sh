#!/bin/bash
# Roll No: MT26210
# Name: Harsh Dubey

g++ -fno-stack-protector -c MT26210_main2.cpp -o main2.o
g++ -fno-stack-protector -c MT26210_basicIO2.cpp -o basicIO2.o
nasm -f elf64 syscall.S -o syscall.o
g++ -nostdlib -no-pie main2.o basicIO2.o syscall.o -o q4
