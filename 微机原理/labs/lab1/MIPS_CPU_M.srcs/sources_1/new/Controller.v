`timescale 1ns / 1ps
module Controller (OpCode, RtFlag, Funct, J, B, RegDst, RegWr, ALUSrc, MemWr, Mem2Reg, ALUCtr);
// codes
  input [5: 0] Funct;
  input [4: 0] RtFlag;
  output [3: 0] ALUCtr;
  input [5: 0] OpCode;
  output J, B, RegDst, RegWr, ALUSrc, MemWr, Mem2Reg;
  wire [2: 0] ALUOp;
  
  MainCtr MainCtr(
	.OpCode	(OpCode),
	.RtFlag (RtFlag),
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
