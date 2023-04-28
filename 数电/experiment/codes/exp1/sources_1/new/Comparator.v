`timescale 1ns / 1ps
module Comparator(
    input wire CP,
    input wire[1:0] DATA,
    output reg[2:0] out
);
    always @(posedge CP) begin
        if (DATA[1] > DATA[0]) 
            out <= 3'b100;
        else if (DATA[1] == DATA[0]) 
            out <= 3'b010;
        else 
            out <= 3'b001; 
    end
endmodule