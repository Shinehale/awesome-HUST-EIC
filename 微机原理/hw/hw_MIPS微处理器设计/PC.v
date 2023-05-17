`timescale 1ns / 1ps
module PC(D, Clk, Reset, Q);
  parameter n=32;
// codes
  input [n - 1: 0] D;
  input Clk, Reset;
  output reg [n - 1: 0] Q = 32'bx;
  always @ (Reset) begin
  if (Reset == 1'b1) Q <= 32'b0;
  end
  always @(posedge Clk) begin
  if (Reset == 1'b0) Q <= D;
  end
endmodule