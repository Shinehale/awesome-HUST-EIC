.data
a:.space 4
b:.space 4
c:.space 160
stra:.asciiz "Please input the value of a:\n"
strb:.asciiz "Please input the value of b:\n"
straplusb:.asciiz "the value of a + b = "
stratimesb:.asciiz "the value of a * b = "
straddress:.asciiz "the address of c[a+b] is  "
another:.asciiz "\n"

.text 
li $v0, 4
la $a0, stra
syscall 
# output the hint of 'a' variable
la $s0, a 
li $v0, 5
syscall 
sw $v0, 0($s0) 
# acquire the value of the variable 'a'


li $v0, 4
la $a0, strb
syscall 
# output the hint of 'b' variable
la $s0, b 
li $v0, 5
syscall 
sw $v0, 0($s0) 
# acquire the value of the variable 'b'

la $s0, a
la $s1, b
lw $t0, 0($s0)
lw $t1, 0($s1)
add $t2, $t0, $t1
li $v0, 4
la $a0, straplusb
syscall 
li $v0, 1
add $a0, $t2, 0
syscall 
# output the value of 'a + b'

add $t0, $t2, 0 				## at this time, $t0 is a + b

li $v0, 4
la $a0, another
syscall 

la $s0, a
la $s1, b
lw $t1, 0($s0)
lw $t2, 0($s1)
mult $t1, $t2	
mflo $t1					## at this time, $t1 = a  * b
li $v0, 4
la $a0, stratimesb
syscall 
li $v0, 1
add $a0, $t1, 0
syscall 	
# output the value of 'a*b'

la $s2, c
sll $t3, $t0, 2
add $t3, $t3, $s2
sw $t1, 0($t3) 					# finish the storage

li $v0, 4
la $a0, another
syscall 

li $v0, 4
la $a0, straddress
syscall 
li $v0, 1
add $a0, $t3, 0
syscall

li $v0, 4
la $a0, another
syscall

li $v0, 1
lw $t2, 0($t3)
add $a0, $t2, 0
syscall

li $v0, 10
syscall 
	