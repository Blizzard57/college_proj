.globl main
.type main, @function

preloop1:             # Check if X > A
    cmp   %rbx, %r8   # rbx(A), r8(X)
    jle   loop1
    jg    ans

loop1:                # Loop over X till X = A
    movq  %rbx, %rax  # Division takes operand as rax
    addq  $1,   %r8   # X = X + 1
    xorq  %rdx, %rdx  # Making sure rdx = 0
    idivq %r8         # Division of rax by r8
    cmp   $0,   %rdx  # Check if remainder is zero
    je    pregcd      # if A%X == 0, then check if gcd(B,X) == 1
    jne   preloop1    # if A%x != 0, then X = X + 1

pregcd:               # rax = X, r9 = B
    movq  %r8,  %rax  # X(a) stored in rax
    movq  %rcx, %r9   # B(b) stored in r9

gcd:                  # gcd(a = rax, b = r9)
    cmp   $0,   %r9   # if b == 0
    je    gcdtest
    jne   gcdnext

gcdnext:
    xorq  %rdx, %rdx  # Making sure rdx = 0
    idivq %r9         # rax(a) / r9(b)
    movq  %r9,  %rax  # a = b
    movq  %rdx, %r9   # b = a%b
    jmp   gcd         # gcd(b,a%b)

gcdtest:
    cmp   $1,   %rax  # if a == 1 (GCD is 1)
    je    setans
    jne   preloop1

setans:
    movq  %r8,  %r11  # Storing temp ans in r11
    jmp   preloop1    # Going back to loop

ans:
    movq  %r11, %rdx  # Moving final ans in rdx
    ret

main:
    xorq  %r11, %r11  # Making sure r11 = 0

    movq  $100,  %rbx  # Value of A
    movq  $17,   %rcx  # Value of B
    movq  $0,   %r8   # Initial Value of X
    
    jmp   preloop1    # Jump to condition Loop
    
# Python Code
#
# def gcd(a,b):
#     if b == 0:
#         return a
#     else:
#         return gcd(b,a%b)
# 
# for x in range(1,p+1):
#     if p%x == 0 and gcd(q,x) == 1:
#         ans = x
