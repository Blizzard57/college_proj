# Assignment 2

Subject : OS and Networks <br>
Roll No : 2018113003

## General

The code was tested out with Ubuntu 20.04 running on WSL2, thus hardware interrupts were not tested extensively. The newborn command 
does not work but the idea behind the command is given in the code (stack smashing occurs). Also all process related details are taken from /proc virtual filesystem and thus does not work on other operating systems.

## Main Shell

My shell is names hash, and does most of what was expected. The last requirement of process information on exiting of background process is not done.

## Coding style

The code was initially written by having each of them as sperate executables but was later changed and added to header files to be added to the shell function itself. The makefile is a simple gcc of all files with not a lot optimization done.