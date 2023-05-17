`timescale 1ns / 1ps
module RegFile (RsAddr, RtAddr, WrAddr, DataIn, RegWr,Clk, RsData, RtData);
// codes
  input [31: 0] DataIn;
  input [4: 0] RsAddr, RtAddr, WrAddr;
  input RegWr, Clk;
  output reg [31: 0] RsData, RtData;
  
  reg [31: 0] regs[31:0];
  
  always @(posedge Clk, RtAddr, RsAddr)begin
	if (RegWr == 1'b1) regs[WrAddr] <= DataIn;
	RsData <= regs[RsAddr];
	RtData <= regs[RtAddr];
  end
  
  
endmodule