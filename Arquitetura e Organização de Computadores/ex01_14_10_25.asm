.data
invvalue: .asciiz ": valor invalido."
invvel: .asciiz ": velocidade invalida\n"
finprint: .asciiz "Maior nivel: velocidade "
.text
.globl main
main:
    # $t0 sera o numero de lesmas/contador
    # $t1 sera o maior valor valido lido
    # $t2 vai ser o resultado final
    # $t3 sera auxiliar para valor lido
    move $t1, $zero
    li $v0, 5
    syscall
    move $t0, $v0
    bgt $t0, 30, printerror
    blt $t0, 1, printerror
    j loopprin

printvelinvalid:
    li $v0, 1
    move $a0, $t3
    syscall
    
    li $v0, 4
    la $a0, invvel
    syscall

loopprin:
    beq $t0, $zero, finalproc
    li $v0, 5
    syscall
    move $t3, $v0
    
    sub $t0, $t0, 1
    bgt $t3, 50, printvelinvalid
    blt $t3, 1, printvelinvalid
    
    blt $t3, $t1, loopprin
    move $t1, $t3
    j loopprin
    
finalproc:
    blt $t1, 10, velfraca
    blt $t1, 20, velmedia
    li $t2, 3
    j finalprint
    
velfraca:
    li $t2, 1
    j finalprint
    
velmedia:
    li $t2, 2
    j finalprint
    
finalprint:
    li $v0, 4
    la $a0, finprint
    syscall
    
    li $v0, 1
    move $a0, $t2
    syscall
    
    li $v0, 10
    syscall
    
printerror:
    li $v0, 1
    move $a0, $t0
    syscall
    
    li $v0, 4
    la $a0, invvalue
    syscall
    
    li $v0, 10
    syscall