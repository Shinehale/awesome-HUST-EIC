`timescale 1ns / 1ps
module Encoder8_3(CP, DATA, out);
    input wire CP;
    input wire[7:0] DATA;
    output reg[2:0] out;
    
    always @ (posedge CP) begin
        case (DATA)
            8'h01: out <= 3'b000;
            8'h02: out <= 3'b001;
            8'h04: out <= 3'b010;
            8'h08: out <= 3'b011;
            8'h10: out <= 3'b100;
            8'h20: out <= 3'b101;
            8'h40: out <= 3'b110;
            8'h80: out <= 3'b111;
        endcase
    end 

endmodule