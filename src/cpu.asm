section .text
global asm_init_cpu
global asm_reset_memory

; void asm_init_cpu(uint64_t *registers, uint64_t *pc, uint64_t *sp, uint64_t *bp)
asm_init_cpu:
    ; RDI contains the pointer to registers array
    ; RSI contains the pointer to program counter
    ; RDX contains the pointer to stack pointer
    ; RCX contains the pointer to base pointer
    
    push rbp
    mov rbp, rsp

    ; Initialize general-purpose registers
    xor rax, rax
    mov qword [rdi], rax      ; R0
    mov qword [rdi + 8], rax  ; R1
    mov qword [rdi + 16], rax ; R2
    mov qword [rdi + 24], rax ; R3
    mov qword [rdi + 32], rax ; R4
    mov qword [rdi + 40], rax ; R5
    mov qword [rdi + 48], rax ; R6
    mov qword [rdi + 56], rax ; R7
    mov qword [rdi + 64], rax ; R8
    mov qword [rdi + 72], rax ; R9
    mov qword [rdi + 80], rax ; R10
    mov qword [rdi + 88], rax ; R11
    mov qword [rdi + 96], rax ; R12
    mov qword [rdi + 104], rax ; R13
    mov qword [rdi + 112], rax ; R14
    mov qword [rdi + 120], rax ; R15

    ; Initialize program counter
    mov qword [rsi], 0

    ; Initialize stack pointer and base pointer
    mov rax, 0xFFFFF ; Assuming 1MB memory
    mov qword [rdx], rax
    mov qword [rcx], rax

    pop rbp
    ret

; void asm_reset_memory(uint8_t *memory, size_t size)
asm_reset_memory:
    ; RDI contains the pointer to memory
    ; RSI contains the size of memory
    
    push rbp
    mov rbp, rsp

    xor rax, rax
    mov rcx, rsi
    shr rcx, 3  ; Divide by 8 to get number of 64-bit words
    rep stosq   ; Fill memory with 0

    pop rbp
    ret

