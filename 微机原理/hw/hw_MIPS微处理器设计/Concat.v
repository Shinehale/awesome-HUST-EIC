`timescale 1ns / 1ps
module Concat (In1, In2, Out);
    parameter n=4,m=28;
// codes
  input [n - 1: 0] In1;
  input [m - 1: 0] In2;
  output reg [n + m - 1: 0] Out;
  
  always @(*) begin
	Out <= {In1, In2};
  end
endmodule