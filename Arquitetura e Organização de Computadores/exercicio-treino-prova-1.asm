.data
textonorm: .asciiz "^2 = "
novlinha: .asciiz "\n"
textoerro: .asciiz "Valor invalido."
.text
.globl main

finish:
li $v0, 10
syscall

invalido:
la $a0, textoerro
li $v0, 4
syscall

li $v0, 10
syscall

main:
li $v0, 5
syscall

move $t0, $v0
ble $t0, 5, invalido
bgt $t0, 99, invalido

li $t1, 2

loop:
bgt $t1, $t0, finish
mult $t1, $t1
mflo $t2

li $v0, 1
move $a0, $t1
syscall

li $v0, 4
la $a0, textonorm
syscall

li $v0, 1
move $a0, $t2
syscall

li $v0, 4
la $a0, novlinha
syscall

addi $t1, $t1, 2
j loop