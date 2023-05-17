`timescale 1ns / 1ps
module RegFile (RsAddr, RtAddr, WrAddr, DataIn, RegWR, Clk, Reset, RsData, RtData);
// codes
  input [31: 0] DataIn;
  input [4: 0] RsAddr, RtAddr, WrAddr;
  input RegWR, Clk, Reset;
  output wire [31: 0] RsData, RtData;
  
  reg [31: 0] regs[31:0];
  assign RsData = (RsAddr == 5'b0)? 32'b0: regs[RsAddr];
  assign RtData = (RtAddr == 5'b0)? 32'b0: regs[RtAddr];
  integer i;
  
  always @(posedge Clk)begin
	if (!Reset & RegWR) 
	   regs[WrAddr] = DataIn;
	else if (Reset) 
	   for (i = 0; i < 32; i = i + 1)
	   begin
	       if (i == 8) regs[i] = 32'h0;
	       else if (i == 9) regs[i] = 32'b0; 
	       else regs[i] = i;
	   end
  end  
endmodule