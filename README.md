# OurShell
Implementation of a basic shell in C.


## Basic Information

1. As a project work of our Operating System curriculum we have implemented this basic shell program for Linux / Unix like operating system. The program is written entirely in C language. 

1. Following functionalities have been implemented so far
	1. program runs in an infinite loop in which it prints a command prompt, accepts a command, executes the command, and prints the prompt for the 	next command.
	1. Handling user interrupt signal (SIGINT)
	1. Command line editing (with TAB completion)
	1. command cd (to change directory),date, ls
	1. Command history (typing "history" will give entire command history), Uparrow and Downarrow key for command history navigation

## Installation and Execution Guidelines


1. There shall be following four files in the extracted directory
	1. shell.c: C source code of our Shell program
	1. run.sh: Shell script to compile and execute the source code
	1. README.txt: The one you are currently reading

(4) Open the extracted directory in terminal and run the follwoing command once. This will give execution permission to the shellscript.

		$ chmod +x run.sh

(5) The run using the following command in terminal:

		$ ./run.sh
