## 线上汇编代码汇总

#### 1.字数据装载

```assembly
lw $t0, 0($s0)
```

#### 2.符号字节数数据装载

```asm
lb $t1, 1($s0)
```

#### 3.无符号字节数据装载

```asm
lbu $t0 2($s0)
```

#### 4.字符半字装载

```asm
lh $t0 0($s0)
```

#### 5.无符号数半字数据装载

```asm
lhu $t0 2($s0)
```

#### 6.字数据存储

```asm
sw $t1 8($s0)
```

#### 7.半字存储

```asm
sh $t1 12($s0) 
```

#### 8.字节存储

```asm
sb $t1 12($s0)
```

#### 9.R型运算

```asm
add $t0, $a0, $a1
add $t1, $a2, $a3
add $v0, $t0, $t1
```

#### 10.I型运算

```asm
addi $t0, $a1, 5
add $v0, $a0, $t0
```

#### 11.I型运算

```asm
addi $t0, $a1, -5
add $v0, $a0, $t0
```

#### 12.乘法运算

```asm
mult $a0, $a1
mfhi $v0
mflo $v1
```

#### 13.无符号乘法运算

```asm
multu $a0, $a1
mfhi $v0
mflo $v1
```

#### 14.符号数除法

```asm
div $a0, $a1
mfhi $v1
mflo $v0
```

#### 15.数组运算

```asm
add $t0, $s1, $s2
lw $t1, 16($s7)
add $s0, $t0, $t1
```

#### 16.数组运算

```asm
lw $t0, 8($s6)
lw $t1, 4($s7)
add $t0, $t0, $s1
add $s0, $t0, $t1 
```

#### 17.数组运算

```asm
sll $t0, $s1, 2
add $t0, $t0, $s7
lw $t0, 0($t0)
add $t0, $t0, $s3
sll $t0, $t0, 2
add $t0, $t0, $s6
lw $s0, 0($t0)
```

#### 18.数组运算

```asm
sll $s0, $s4, 2
add $s0, $s0, $s7
lw $s0, 0($s0)
sll $s0, $s0, 2
add $s0, $s0, $s6
lw $t0, 0($s0)
sub $s0, $s1, $t0
```

#### 19.位运算

```asm
li $t2 31
sll $t2, $t2, 3
and $t2, $t2, $t0
sll $t2, $t2, 12
add $t1, $t2, 0
```

#### 20.位运算

```asm
li $t2, 31
sll $t2, $t2, 3
and $t1, $t2, $t0
srl $t1, $t1, 3
```

#### 21.位运算

```asm
li $t2, 1
sll $t2, $t2, 15
sub $t2, $t2, 1
sll $t2, $t2, 6
and $t1, $t2, $t0
srl $t1, $t1, 6
```

#### 22.位运算

```asm
li $t2, 1
sll $t2, $t2, 15
sub $t2, $t2, 1
sll $t2, $t2, 6
and $t1, $t2, $t0
sll $t1, $t1, 9
```

#### 23.程序控制for

```asm
	li $t0, 0
	li $t1, 10
loop:
	add $s0, $s0, $s1
	addi $t0, $t0, 1
	bne $t0, $t1, loop
```

#### 24.程序控制while

```asm
while_simu:
	addi $t1, $s0, -10
	bgez $t1, exit
	add $t3, $s0, $s1 			
	sll $t2, $s0, 2
	add $t2, $t2, $s2
	sw $t3, 0($t2)
	addi $s0, $s0, 1
	j while_simu
exit:
```

#### 25.程序控制for

```asm
	li $a0, 0
loop:
	sub $t0, $a0, $a1
	beqz $t0, break_loop
	sll $t0, $a0, 2
	add $t1, $t0, $s1
	lw $t1, 0($t1)
	add $t2, $t0, $s0
    sw $t1, 0($t2)
	addi $a0, $a0, 1
	j loop
break_loop:
```

#### 26.程序控制for以及if

```asm
	li $a0, 0
loop:
	sub $t0, $a0, $a1
	bgez $t0, break_loop
	
	sll $t0, $a0, 2
	add $t1, $t0, $s0
	lw $a2, 0($t1)
	add $t2, $t0, $s1
	lw $a3, 0($t2)
	
	bne $a2, $a3, next
	sw $0, 0($t1)
	
next:
	addi $a0, $a0, 1
	j loop

break_loop:
```

#### 27.子程序设计

```asm
.data
p: .space 32

.text
main: 
	la $a0,p
	add $a1, $0, $0
ag:
	slti $s0, $a1, 8
	beq $s0, $0, exit
	jal sub_proc
	addi $a1, $a1, 1
	j ag
exit:
	addi $v0,$0,10
	syscall

sub_proc:
	sll $t0, $a1, 2
	add $t0, $t0, $a0
	li $t1, 1
	sllv $t1, $t1, $a1
	sw $t1, 0($t0)
	li $v0, 0
	jr $ra
```

#### 28.程序控制while与if

```asm
.data
a:.word 8, 7, 6, 5, 4, 3, 2, 1
.space 0x20
b:.word 1, 2, 3, 4, 5, 6, 7, 8
.text
main:
	la $s0, a
	la $s1, b
	li $a0, 0

while_simu:
	sll $t0, $a0, 2
	add $s2, $t0, $s0
	lw $t1, 0($s2)
	beq $t1, $0, while_break
	
	add $s3, $t0, $s1
	lw $t2, 0($s3)
	slt $t3, $t2, $t1
	beq $t3, $0, else_branch
	li $t1, 1
	sw $t1, 0($s2)
	j next

else_branch:
	li $t1, 2
	sw $t1, 0($s2)

next:
	addi $a0, $a0, 1
	j while_simu

while_break:
```

#### 29.MIPS汇编语言完整程序设计

```asm
li $a0, 0
li $a1, 0
loop:
	slti $t0, $a0, 10
	beq $t0, $0, loop_exit
	sll $t1, $a0, 2
	add $t1, $t1, $s0
	lw $t1, 0($t1)
	add $a1, $a1, $t1
	addi $a0, $a0, 1
	j loop

loop_exit:
	sll $t1, $a0, 2
	add $t1, $t1, $s0
	sw $a1, 0($t1) 
```

#### 30.MIPS汇编语言完整程序设计

```asm
li $a0, 0
loop:
	sltiu $t0, $a0, 10
	beq $t0, $0, loop_exit

	sll $t1, $a0, 2
	add $s2, $t1, $s0
	lw $t2, 0($s2)
	add $s3, $t1, $s1
	sw $t2, 0($s3)

next:
	addi $a0, $a0, 1
	j loop

loop_exit:
```

#### 31.子程序-绝对值

```asm
.text
	lui $a0, 0xffff
	ori $a0, $a0, 0x8000
	jal ABS
	add $s0,$v0,$0
	add $a0,$0,$0
	ori $a0,$a0,0x8000
	jal ABS
	add $s1,$v0,$0
	add $v0,$0,10
	syscall
ABS:
	srl $t0, $a0, 30
	add $s0, $a0, 0
	beq $t0, $0, ABS_ret
	
	nor $s0, $a0, $a0
	addi $s0, $s0, 1 


ABS_ret:
	add $v0, $s0, 0
	jr  $ra
```

