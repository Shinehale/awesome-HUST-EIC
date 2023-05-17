`timescale 1ns / 1ps
module ALU (In1, In2, ALUCtr, Res, Zero);
// codes
  input signed [31: 0] In1, In2;
  input [3: 0] ALUCtr;
  output reg [31: 0] Res;
  output reg Zero;
  
  always @(In1 or In2 or ALUCtr) begin
	case (ALUCtr)
	  4'b0010: //add
	  begin
	  	Res = In1 + In2;
	  	Zero = 0;
	  end
	  4'b0110: //sub
	  begin
		Res = In1 - In2;
		Zero = (Res == 0)? 1 : 0;
	  end
	  4'b0100:
	  begin   
	    Res = In1 - In2;
	    Zero = (Res != 0)? 1: 0; 
	  end
	  4'b1110:
	  begin
	    Zero = (In1 < 0) ? 1 : 0;
	  end
	  4'b1111:
	  begin
	    Zero = (In1 >= 0)? 1 : 0;
	  end
	  4'b0000: //and
	  begin
		Res = In1 & In2;
		Zero = 0;
      end
	  4'b0001: //or
	  begin
		Res = In1 | In2;
		Zero = 0;
	  end
	  4'b0111: //slt
	  begin
		  Res = (In1 < In2)?1:0;
		  Zero = 0;
	  end 
	  default:
	  begin
	      Zero = 0;
		  Res = 32'b0;
	  end
	endcase
  end
endmodule
