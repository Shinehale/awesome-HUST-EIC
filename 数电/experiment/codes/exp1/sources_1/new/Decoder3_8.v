`timescale 1ns / 1ps
module Decoder3_8(CP, DATA, out);
    input wire CP;
    input wire [2:0] DATA;
    output reg [7:0] out;
    
    always @(posedge CP) begin
        case (DATA)
            3'b000: out <= 8'h01;
            3'b001: out <= 8'h02;
            3'b010: out <= 8'h04;
            3'b011: out <= 8'h08;
            3'b100: out <= 8'h10;
            3'b101: out <= 8'h20;
            3'b110: out <= 8'h40;
            3'b111: out <= 8'h80;
        endcase
    end
endmodule