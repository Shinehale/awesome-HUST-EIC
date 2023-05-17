`timescale 1ns / 1ps
module Adder (In1,In2,Out);
  parameter n=32;
// codes
  input [n - 1: 0] In1, In2;
  output reg [n - 1: 0] Out;
  
  always @(*) begin
	Out <= In1 + In2;
  end
endmodule
