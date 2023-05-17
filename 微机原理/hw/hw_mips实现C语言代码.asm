.data
STR:.asciiz "This is a string"
CHR:.byte 's'
.text
.globl main
main:
	la $a0, STR
	la $t0, CHR
	lb $a1, 0($t0)
	jal STRRCHR
	sub $a0, $v0, $a0
	addi $a0, $a0, 1
	li $v0, 1
	syscall
	li $v0, 10
	syscall
STRRCHR:
	add $t0, $zero, $a0
	add $t1, $zero, $a0
LOOP:	
	lb $t2, 0($t0)
	beq $t2, $zero, RETURN
	bne $t2, $a1, NEXT
	add $t1, $zero, $t0
NEXT:
	addi $t0, $t0, 1
	j LOOP
RETURN:
	add $v0, $zero, $t1
	jr $ra
	
	
