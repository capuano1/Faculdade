.data
str: .asciiz " valores positivos"
.text
.globl main
main:
    # $t0 vai ser o contador do loop
    # $t1 vai ser o contador de positivos
    move $t0, $zero
    move $t1, $zero
    
loop:
    beq $t0, 6, print
    li $v0, 5
    syscall
    add $t0, 1
    blt $v0, $zero, loop
    add $t1, 1
    j loop
    
print:
    li $v0, 1
    move $a0, $t1
    syscall
    
    li $v0, 4
    la $a0, str
    syscall