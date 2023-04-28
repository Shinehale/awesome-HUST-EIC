`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/03/23 23:31:19
// Design Name: 
// Module Name: text
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module test;
reg CP, EN_0, PE, CLR, flag;
reg [3:0] D;
wire [15:0] Q;

M_16 M1(CP, CLR, EN_0, PE, flag, D, Q);


initial
	CP = 1;
always
	#5 CP = ~CP;
initial 
begin
    EN_0 = 0; PE = 0; CLR = 0; D = 4'b1001; flag = 0;
    #10
    EN_0 = 1; PE = 0; CLR = 1; D = 4'b1001; flag = 1;
    #10
    EN_0 = 1; PE = 0; CLR = 0; D = 4'b1001; flag = 1;
    #150
    EN_0 = 1; PE = 0; CLR = 0; D = 4'b1001; flag = 0;
    #100
    EN_0 = 1; PE = 1; CLR = 0; D = 4'b1001; flag = 1;
    #10 
    EN_0 = 1; PE = 0; CLR = 0; D = 4'b1001; flag = 1;
    #100
  $stop;
end
endmodule
