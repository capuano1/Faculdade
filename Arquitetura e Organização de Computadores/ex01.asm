.data
maior: .asciiz "Maior: "
.text
.globl main
main:
    li $v0, 5
    syscall
    move $t0, $v0
    
    li $v0, 5
    syscall
    move $t1, $v0
    
    bge $t1, $t0, changeBit
    
    j third

changeBit:
    move $t0, $t1
    j third

third:
    li $v0, 5
    syscall
    move $t1, $v0
    
    bge $t1, $t0, lastChange
    
    j print
    
lastChange:
    move $t0, $t1
    
print:
    li $v0, 4
    la $a0, maior
    syscall
    
    li $v0, 1
    move $a0, $t0
    syscall