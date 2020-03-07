# Question :
# Finding i st i! % x == 0

# To do :
# Loop over i, starting with i = 0
# Compute i! ( Different Function )
# Check if i! % x == 0
# Condition Jump to end

# Variable Storages :
# x in %rax
# i in %r9
# Ans in %rdi

.globl main
.type main, @function

.fac:
    movq %rcx, %rax
    xorq %rdx, %rdx # making sure rdx does not have junk value
    idivq %r11 # Remainder stored in rdx
    cmp $0, %rdx
    je .ans # If equal go to ans
    addq $1, %r9 # Else add 1 to multiplier
    imulq %r9, %rcx # Multipy it to loop variable
    jmp .fac


main:
    # Default instructions
    pushq %rbp
    movq %rsp, %rbp

    movq $1, %rcx # Multiplier
    movq $1, %r9 # Loop variable
    
    # User Input
    movq $8, %rax
    mov %rax, %r11
    jmp .fac

.ans:
    popq %rbp
    movq %r9, %rdi
    ret