`timescale 1ns / 1ps
module MainCtr (OpCode, J, B, RegDst, RegWr, ALUSrc, MemWr, Mem2Reg, ALUOp);
// codes
  input [5: 0] OpCode;
  output reg J, B, RegDst, RegWr, ALUSrc, MemWr, Mem2Reg;
  output reg [1: 0] ALUOp;
  
  always @(*) begin
	case (OpCode)
	  6'b000000:
		begin
		  J <= 1'b0;
		  B <= 1'b0;
		  RegDst <= 1'b1;
		  RegWr <= 1'b1;
		  ALUSrc <= 1'b0;
		  MemWr <= 1'b0;
		  Mem2Reg <= 1'b0;
		  ALUOp <= 2'b10;
		end
	  6'b100011:
		begin
		  J <= 1'b0;
		  B <= 1'b0;
		  RegDst <= 1'b0;
		  RegWr <= 1'b1;
		  ALUSrc <= 1'b1;
		  MemWr <= 1'b0;
		  Mem2Reg <= 1'b1;
		  ALUOp <= 2'b00;
		end
	  6'b101011:
		begin
		  J <= 1'b0;
		  B <= 1'b0;
		  RegDst <= 1'bx;
		  RegWr <= 1'b0;
		  ALUSrc <= 1'b1;
		  MemWr <= 1'b1;
		  Mem2Reg <= 1'bx;
		  ALUOp <= 2'b00;
		end
	  6'b000100:
		begin
		  J <= 1'b0;
		  B <= 1'b1;
		  RegDst <= 1'bx;
		  RegWr <= 1'b0;
		  ALUSrc <= 1'b0;
		  MemWr <= 1'b0;
		  Mem2Reg <= 1'bx;
		  ALUOp <= 2'b01;
		end
	  6'b000010:
		begin
		  J <= 1'b1;
		  B <= 1'b0;
		  RegDst <= 1'bx;
		  RegWr <= 1'b0;
		  ALUSrc <= 1'bx;
		  MemWr <= 1'b0;
		  Mem2Reg <= 1'bx;
		  ALUOp <= 2'bxx;
		end
	endcase
  end
  
endmodule

