`timescale 1ns / 1ps
module MainCtr (OpCode, RtFlag, J, B, RegDst, RegWr, ALUSrc, MemWr, Mem2Reg, ALUOp);
// codes
  input [5: 0] OpCode;
  input [4: 0] RtFlag;
  output J, B, RegDst, RegWr, ALUSrc, MemWr, Mem2Reg;
  output [2: 0] ALUOp;
  
  reg [9: 0] outregs;
 
  always @(*) begin
	case (OpCode)
	  6'b000000: outregs <= 10'b1001_000_100;    //R
	  6'b100011: outregs <= 10'b0111_000_000;    //lw
	  6'b101011: outregs <= 10'bx1x0_100_000;    //sw
	  6'b000100: outregs <= 10'bx0x0_010_010;    //beq
	  6'b000010: outregs <= 10'bxxx0_001_xxx;    //jmp
	  // extention parts
	  6'b000101: outregs <= 10'bx0x0_010_011;    //bne
	  6'b000001: begin
	      if (RtFlag == 5'b00000) outregs <= 10'bx0x0_010_110;
	      else outregs <= 10'bx0x0_010_111;
	  end
	  default: outregs <= 10'b0000_000_000;
	endcase
  end
  assign {RegDst, ALUSrc, Mem2Reg, RegWr, MemWr, B, J, ALUOp} = outregs;
endmodule

