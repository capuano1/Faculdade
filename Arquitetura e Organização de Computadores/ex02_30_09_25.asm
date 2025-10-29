.data
par: .asciiz " valor(es) par(es)\n"
impar: .asciiz " valor(es) impar(es)\n"
pos: .asciiz " valor(es) positivo(s)\n"
negat: .asciiz " valor(es) negativo(s)"
.text
.globl main
main:
    # $t0 vai ser o contador do loop
    # $t1 vai ser o contador de positivos
    # $t2 vai ser o contador de pares
    # $t3 usado para verificar resto de div
    # $t4 usado com o numero carregado
    # $t5 usado como auxiliar
    move $t0, $zero
    move $t1, $zero
    move $t2, $zero
    
loopPos:
    beq $t0, 5, print
    li $v0, 5
    syscall
    move $t4, $v0
    add $t0, $t0, 1
    blt $t4, $zero, loopPar
    add $t1, $t1, 1
    j loopPar
    
loopPar:
    addi $t5, $zero, 2
    div $t4, $t5
    mfhi $t3
    beq $t3, 1, loopPos
    beq $t3, -1, loopPos
    addi $t2, $t2, 1
    j loopPos
    
print:
    # %t5 usado como auxiliar do numero maximo de valores lidos
    addi $t5, $zero, 5
    
    # par
    li $v0, 1
    move $a0, $t2
    syscall
    
    li $v0, 4
    la $a0, par
    syscall
    
    # impar
    sub $t2, $t5, $t2
    li $v0, 1
    move $a0, $t2
    syscall
    
    li $v0, 4
    la $a0, impar
    syscall
    
    # positivo
    li $v0, 1
    move $a0, $t1
    syscall
    
    li $v0, 4
    la $a0, pos
    syscall
    
    # negativo
    sub $t1, $t5, $t1
    li $v0, 1
    move $a0, $t1
    syscall
    
    li $v0, 4
    la $a0, negat
    syscall
    
    li $v0, 10
    syscall