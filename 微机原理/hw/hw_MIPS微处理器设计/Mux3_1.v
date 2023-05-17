`timescale 1ns / 1ps
module Mux3_1 (In1, In2,In3, sel, Out);
  parameter n=32;
// codes
  input [n - 1: 0] In1, In2, In3;
  input [1: 0] sel;
  output reg [n - 1: 0] Out;
  
  always @(*) begin
	if (sel[1] == 1) Out <= In3;
	else if (sel[0] == 1) Out <= In2;
	else if (sel[0] == 0) Out <= In1;
  end
endmodule