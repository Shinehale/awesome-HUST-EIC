`timescale 1ns / 1ps

module SelectAN(
    input wire [1: 0] num,
    output wire [7: 0] an
);
    reg [7: 0] anr;
    always @(num) begin
        case (num)
            2'b00:  anr <= 8'b11111110;
            2'b01:  anr <= 8'b11111101;
            2'b10:  anr <= 8'b11111011;
            2'b11:  anr <= 8'b11110111;
        endcase
    end
    assign an = anr;
    
endmodule