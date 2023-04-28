`timescale 1ns / 1ps
module Timer(
    input wire rst,
    input wire CLK,
    output wire clk
);  
    parameter n = 500000;
    reg [30: 0] cnt;
    reg nclk;
    always @ (posedge CLK or posedge rst) begin
        if (rst) begin
            cnt <= 1'b0;
            nclk <= 1'b0;
        end
        else  if (cnt == n) begin
            cnt <= 1'b0;
            nclk = ~nclk;
        end 
        else begin
            cnt <= cnt + 1;
        end
    end
    assign clk = nclk;
endmodule