.text

.global switchToUserMode

switchToUserMode:
    cli
    sti
    movq %rdi, %es
    movq %rdi, %fs
    movq %rdi, %gs
    movq %rdi, %ds
    movq %rdi, %ss
    movq %rsp,%rax
    pushq %rdi
    pushq %rax
    pushfq
    pushq %rsi
    pushq $1f
    iret
    1

