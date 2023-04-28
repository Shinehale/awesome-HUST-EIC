`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/03/16 10:12:09
// Design Name: 
// Module Name: mux2_1
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


module mux2_1(cp, DIn, DOut, S);
    input wire cp;
    input [1:0] DIn; 
    output reg DOut;
    input S;
   
    always @ (posedge cp) begin
        if (S == 1'b0) DOut = DIn[0];
        else DOut = DIn[1];
    end
endmodule
