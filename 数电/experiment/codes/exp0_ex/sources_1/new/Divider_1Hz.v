`timescale 1ns / 1ps
module Divider_1Hz(
    input wire rst,
    input wire CLK,
    output wire clk
);  
    parameter n = 50000000;
    reg [31: 0] cnt;
    reg nclk;
    always @ (posedge CLK) begin
        if (rst == 1'b0) begin
            cnt <= 32'b0;
            nclk <= 1'b0;
        end
        if (cnt >= n) begin
            cnt <= 32'b0;
            nclk = ~nclk;
        end 
        else begin
            cnt <= cnt + 1;
        end
    end
    assign clk = nclk;
endmodule