main:
	bne $t1 $t1 label1	%比较t1寄存器和t1寄存器的值如果不等_跳转到label即PC为12
	bne $t1 $t0 label1	%比较t1寄存器和t0寄存器的值如果不等_跳转到label即PC为12
label2:
	bltz $t1, label3		%比较t1寄存器和0如果小于_跳转到label即PC为16
label1:	
	bltz $t0, label2		%比较t0寄存器和零值如果小于_跳转到label即PC为8
label3:
	bgez $t0, label2	        %比较t0寄存器和零值如果大于等于跳转到PC为8
	bgez $t0, label4        %比较t0寄存器和零值如果大于等于跳转到PC为28
	bne $t1, $t1, label1 	      %比较t1寄存器和t1寄存器的值如果不等_跳转到label即PC为12  
label4:	
	bgez $0, label4
	
