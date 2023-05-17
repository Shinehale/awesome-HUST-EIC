`timescale 1ns / 1ps
module DataRAM(Addr, DataIn, MemWR, Clk, DataOut);
  parameter n=5,m=32;
  input [n-1: 0] Addr;
  input [m-1: 0] DataIn;
  input MemWR, Clk;
  output reg [m-1: 0] DataOut;
  
  reg[m-1: 0] regs[2**n-1: 0];
  
  always @( posedge Clk, Addr) begin
	if (MemWR == 1'b1) regs[Addr] <= DataIn;
	DataOut <= regs[Addr];
  end
  
endmodule