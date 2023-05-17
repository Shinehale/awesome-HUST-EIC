`timescale 1ns / 1ps
module LeftShift (In, Out);
    parameter n=32,m=32,x=2;
// codes
  input [n - 1: 0] In;
  output reg [m - 1: 0] Out;
  
  reg [x - 1: 0] all_zero = 2'b0;
  always @(*) begin
	Out <= {In[m - x - 1: 0],  all_zero};
  end
endmodule
