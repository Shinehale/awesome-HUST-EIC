`timescale 1ns / 1ps
module InstrROM (Addr, Clk, Instr);
  parameter n = 5, m = 32;
  
  input [n - 1: 0] Addr;
  input Clk;
  output reg [31: 0] Instr;
  	
  reg[m - 1: 0] regs[2 ** n - 1: 0];
  
  always @(posedge Clk) begin
	Instr <= regs[Addr];
  end
  
// 代码
endmodule
