#!/bin/bash

g++ -fno-stack-protector -c main3.cpp -o main3.o
g++ -fno-stack-protector -c basicIO2.cpp -o basicIO2.o
nasm -f elf64 syscall.S -o syscall.o
g++ -nostdlib -no-pie main3.o basicIO2.o syscall.o -o q5
