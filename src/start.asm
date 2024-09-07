section .text.start
global _start
extern stack_top
extern main

_start:
    ; Set up the stack
    mov rsp, stack_top
    
    ; Call the main function
    call main
    
    ; Exit the program
    mov rax, 60 ; sys_exit syscall number
    xor rdi, rdi ; exit status 0
    syscall

