# Question 4

## Bugs

Two bugs were found, which caused the code to not function. They are :

- In function F5, there was a branch selection be jg which had to be changed to jl, as the brached required for moving the hanoi ring from one tower to another. After comaring the heights of the two rings, if r10 > rax, then the code should take the branch that is greater_brach.

- In solve function, the stack was not set up, thus the code running into segmentation fault. Thus had to add an instruction that pushed rsp to rbp.

## Code function

The code is a tower of hanoi problem, with f1 initializing the problem, f2 knowing what the tower is, and f4 pushing and popping the tower. the pt functions print it and solve function has the actual logic.
