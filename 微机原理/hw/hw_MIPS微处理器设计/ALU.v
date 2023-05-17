`timescale 1ns / 1ps
module ALU (In1, In2, ALUCtr, Res, Zero);
// codes
  input signed [31: 0] In1, In2;
  input [3: 0] ALUCtr;
  output reg [31: 0] Res;
  output reg Zero;
  
  always @(*) begin
	case (ALUCtr)
	  4'b0010: 
	  	Res <= In1 + In2;
	  4'b0110:
		Res <= In1 - In2;
	  4'b0000:
		Res <= In1 & In2;
	  4'b0001:
		Res <= In1 | In2;
	  4'b0111:
		begin
		  if (In1 < In2) Res <= 1;
		  else Res <= 0;
		end 
	  default:
		  Res <= 32'b0;
	endcase
	if (Res == 1'b0) Zero <= 1'b1;
	else Zero <= 1'b0;
  end
endmodule
