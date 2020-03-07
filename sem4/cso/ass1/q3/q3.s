.globl main
.type main, @function

Loop:
    # Loops till end Condition
    cmp $0, %r9 # If b == 0
    jle Ans # Get Ans
    test $1, %r9 # If b != 1
    jne Mult # Go for multiplication

Add:
    # Does 
    shrq $1, %r9 # b/2
    movq %r8, %rax # (a*a)%n
    imulq %rax, %rax
    xor %rdx, %rdx # Making sure rdx where remainder stored is zero 
    idivq %r10
    movq %rdx, %r8 # a = a % n
    jmp Loop

Mult:
    movq %r8, %rax
    imulq %r11, %rax 
    xor %rdx, %rdx
    idivq %r10
    movq %rdx, %r11 
    jmp Add


main:
    # initial setup
    pushq %rbp
    movq %rsp, %rbp
    xorq %rdx, %rdx
    xorq %r8, %r8
    xorq %r9, %r9
    xorq %r10, %r10
    mov $1, %r11 # Looping variable
    movq $2, %r8 # a
    movq $5, %r9 # b
    movq $30, %r10 # n 
    movq %r8, %rax
    idivq %r10
    jmp Loop
Ans:
    popq %rbp
    movq %r11, %rdi # Answer in rdi
    ret