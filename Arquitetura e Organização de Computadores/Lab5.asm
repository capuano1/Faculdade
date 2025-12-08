.data
vetorA: .word 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
vetorB: .word 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
novLinha: .asciiz "\n"
.text
.globl main

main:
la $s0, vetorA
li $t0, 0

loop:
li $v0, 5
syscall

sw $v0, 0($s0)
addi $s0, $s0, 4
addi $t0, $t0, 1
beq $t0, 15, countingsort
j loop

finish_program:
la $s0, vetorB
li $t0, 0
j finish_loop

nova_linha:
la $a0, novLinha
li $v0, 4
syscall

finish_loop:
lw $a0, 0($s0)
li $v0, 1
syscall

addi $t0, $t0, 1
addi $s0, $s0, 4
blt $t0, 15, nova_linha

finish:
li $v0, 10
syscall

countingsort:
li $t3, 15
la $s0, vetorA

outer_counting:
ble $t3, 0, finish_program
la $s1, vetorA
la $s2, vetorB
li $t4, 0
li $t5, 0
lw $t0, 0($s0)

inner_counting:
lw $t1, 0($s1)
addi $s1, $s1, 4
addi $t4, $t4, 1

ble $t0, $t1, iteracao_counting
addi $t5, $t5, 1

iteracao_counting:
blt $t4, 15, inner_counting

salvar_valor:
li $t6, 4
mult $t6, $t5
mflo $t7
add $s2, $s2, $t7
sw $t0, 0($s2)
addi $t3, $t3, -1
addi $s0, $s0, 4
j outer_counting