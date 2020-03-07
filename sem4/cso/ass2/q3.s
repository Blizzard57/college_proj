.globl main
.type main, @function

.section .data
    .outputstring:
        .ascii "%lld\n\0"
        .text

main:
    movq  $7, %rbx           # n stored in rbx
    movq  %rbx, %r9          # r9 = n
    subq  $1, %r9            # Indexing starts from 0
    imulq $-8, %r9, %r8      # r8 sores the index of the last value
    
inputstack:
    push  %rcx               # Pushing rcx into stack
    movq  %rsp, %rcx
    
    movq  $4, (%rcx)
    movq  $4, -8(%rcx)
    movq  $5, -16(%rcx) 
    movq  $2, -24(%rcx)
    movq  $10,-32(%rcx)
    movq  $8, -40(%rcx)
    movq  $15,-48(%rcx)
    # push  %rdx
    
outputinit:
    movq  $0, %r10           # Iteration over all values <=r11
    movq  $8, %r11           # Current location
    movq  %r8,%r15           # Location of output array  
    subq  $8, %r15 
    movq  $-1, %r14          # Default answer
    
loop1:                       # i(r11) in range(0,6)
    subq $8, %r11
    movq %r11, %r10          # j = current location
    cmp %r8, %r11            # r11 <= index of last value
    jl  ans
    movq (%r11,%rcx), %r13   # r13 = arr[i]

loop2:                       # j(r10) in range(i,-1,-1)
    addq $8, %r10            # r10 += 8 (Going back one index)
    cmp $0, %r10             # Checking if first index reached
    jg setans
    movq (%r10,%rcx), %r12   # r12 = arr[j]
    cmp %r12, %r13           # r13(i) > r12(j)
    jle loop2
    movq %r12, %r14   # r14 = ans

setans:
    # movq %rsp, %rdx          # Stack pointer ==> rdx
    movq %r14, (%r15,%rcx) 
    movq $-1, %r14
    subq $8, %r15               # Pointing to next index
    # movq %rsp, %rcx          # Stack pointer ==> rcx
    jmp loop1

ans:
    # Print the values
    imulq $-8, %rbx, %r9   # r9 = -8*n 
    movq $0, %r10          # r10 = 0
    push %rdx         # Stack pointer ==> rdx 
    movq %rsp, %rdx

ansloop:
    movq (%r9,%rcx), %rax
    movq %rax, (%r10,%rdx)
    subq $8, %r9
    subq $8, %r10
    cmp %r8, %r10
    jl end
    jmp ansloop
    # lea .outputstring(%rip), %rdi
    # movq (%rdx), %rsi
    # call printf@PLT
    
end:
    pop   %rdx
    pop   %rcx
    ret
