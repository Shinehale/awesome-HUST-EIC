`timescale 1ns / 1ps
module Mux2_1 (In1, In2, sel, Out);
parameter n=32;
// codes
  input [n - 1: 0] In1, In2;
  output reg [n - 1: 0] Out;
  input sel;
  
  always @ (*) begin
	if (sel == 1'b0) Out <= In1;
	else Out <= In2;
  end
endmodule
