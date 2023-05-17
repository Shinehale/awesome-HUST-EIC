`timescale 1ns / 1ps
module ALUControl (ALUOp, Funct, ALUCtr);
// codes
  input [2: 0] ALUOp;
  input [5: 0] Funct;
  output reg [3: 0] ALUCtr;
  
  always @(*) begin
	case (ALUOp)
	  3'b000:
		ALUCtr <= 4'b0010;
	  3'b010:
		ALUCtr <= 4'b0110;            // beq
	  3'b011:
	    ALUCtr <= 4'b0100;
	  3'b110:
	    ALUCtr <= 4'b1110;
	  3'b111:
	    ALUCtr <= 4'b1111;
	  3'b100:
		begin
		  case (Funct)
			6'b100000:
			  ALUCtr <= 4'b0010;
			6'b100010:
			  ALUCtr <= 4'b0110;
			6'b100100:
			  ALUCtr <= 4'b0000;
			6'b100101:
			  ALUCtr <= 4'b0001;
			6'b101010:
			  ALUCtr <= 4'b0111;
		  endcase
		end
	endcase
  end
  
endmodule
