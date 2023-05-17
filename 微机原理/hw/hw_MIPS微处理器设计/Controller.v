`timescale 1ns / 1ps
module Controller (OpCode, Funct, J, B, RegDst, RegWr, ALUSrc, MemWr, Mem2Reg, ALUCtr);
// codes
  input [5: 0] Funct;
  output [3: 0] ALUCtr;
  input [5: 0] OpCode;
  output J, B, RegDst, RegWr, ALUSrc, MemWr, Mem2Reg;
  wire [1: 0] ALUOp;
  
  MainCtr MainCtr(
	.OpCode	(OpCode),
	.J	(J),
	.B	(B),
	.RegDst	(RegDst),
	.RegWr	(RegWr),
	.ALUSrc	(ALUSrc),
	.MemWr	(MemWr),
	.Mem2Reg	(Mem2Reg),
	.ALUOp	(ALUOp)
  );
  
  ALUControl ALUControl(
	ALUOp, Funct, ALUCtr
  );
endmodule
