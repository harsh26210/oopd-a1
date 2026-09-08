#!/bin/bash

g++ -fno-stack-protector -c main.cpp -o main.o
g++ -fno-stack-protector -c basicIO.cpp -o basicIO.o
nasm -f elf64 syscall.S -o syscall.o
g++ -nostdlib -no-pie main.o basicIO.o syscall.o -o q3
