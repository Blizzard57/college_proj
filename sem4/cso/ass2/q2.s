.globl main
.type main, @function

checkinit:
    cmp   $0,   %rbx   # n <= 0
    jle   ans
    addq  $1,   %r10
    cmp   $1,   %rbx   # n = 1
    jle   ans
    addq  $2,   %r10   # n = 2
    cmp   $2,   %rbx
    je    ans
    
check:
    cmp   %rbx, %rdi  # n>=fib(i)
    jle   facinit
    jg    ans

facinit:
    movq  $1,   %r14  # factorial variable
    movq  $1,   %r15  # loop variable

fac:
    cmp   %rdi, %r15  # fib(i) > loop var
    jg    sum
    imul  %r15, %r14  # fac = fac * i
    xorq  %rdx, %rdx  # rdx = 0
    movq  %r14, %rax  # rax = r14
    idivq %rcx        # rdx = rax % rcx
    movq  %rdx, %r14  # r14 = rdx(r14%k)
    addq  $1,   %r15  # i = i + 1
    jmp   fac

sum:
    addq  %r14, %r10  # Ans = Ans + fib(i)%k
    jmp   fib

fib:
    movq  %r9,  %r8   # fib(i-2) = fib(i-1)
    movq  %rdi, %r9   # fib(i-1) = fib(i)
    addq  %r8,  %rdi  # fib(i) = fib(i-1) + fib(i-2)
    jmp   check

ans:
    movq  %r10, %rax  # rax = r10
    xorq  %rdx, %rdx  # rdx = 0
    idivq %rcx        # ans = ans % k
    ret

main:
    movq  $100,   %rbx  # Value of n
    movq  $150,  %rcx  # Value of k
    movq  $1,   %r8   # Fib(i-2)
    movq  $2,   %r9   # Fib(i-1)
    movq  $3,   %rdi  # Fib(i)
    movq  $0,   %r10  # Final Ans in r10

    xorq  %r11, %r11  # Factorial in r11
    
    jmp   checkinit

# Python code
#
# n = 100
# k = 150
# ans = 0
# val = 0
# 
# def fac(v,m):
#     p = 1
#     for j in range(1,v+1):
#         p = (p * j) % m
#     return p
# 
# def fib(i):
#     if i < 2:
#         return 1
#     else:
#         return fib(i-1) + fib(i-2)
# 
# i = 1
# while True:
#     q = fib(i)
#     if q > n:
#         break
#     val = fac(q,k)
#     #print(q,val)
#     ans = ans + val
#     i+=1
# 
# print(ans % k)
