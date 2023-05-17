`timescale 1ns / 1ps
module SignedExtend (In, Out);
    parameter n=16,m=32;
// 代码
  input [n - 1: 0] In;
  output reg [m - 1: 0] Out;
  reg [n - 1: 0] all_one = 16'hFFFF;
  reg [n - 1: 0] all_zero = 16'h0000;
  always @(*) begin
	if (In[n - 1] == 1'b0) Out <= {all_zero, In};
  	else Out <= {all_one, In};
  end
endmodule