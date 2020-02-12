.globl main
.text 

# n is stored in %rbx
# The final answer is stored in %rax at the end

main:
    pushq %rbp
    movq  %rsp,%rbp
    movq  $8,%r10 # n = 7, n --> %rbx
    movq  %r10,%r8  
    movq  $1,%r9
    call  fac
    syscall
    popq  %rbp


fac:
    pushq %rbp
    movq  %rsp,%rbp
    cmpq  $0,%r8
    je    base  
    imulq %r8,%r9
    subq  $1,%r8
    call  fac
    popq  %rbp            

base:
    movq  %r9,%rax
    movq  %rbp,%rsp
    popq  %rbp
#   popq  %rbp
    ret