`timescale 1ns / 1ps

module SelectAN(
    input wire [2: 0] NUM,
    output wire [7: 0] AN
);
    reg [7: 0] anr;
    always @(NUM) begin
        case (NUM)
            3'b000:  anr <= 8'b11111110;
            3'b001:  anr <= 8'b11111101;
            3'b010:  anr <= 8'b11111011;
            3'b011:  anr <= 8'b11110111;
            3'b100:  anr <= 8'b11101111;
            3'b101:  anr <= 8'b11011111;
            3'b110:  anr <= 8'b10111111;
            3'b111:  anr <= 8'b01111111;
        default:anr <= 8'b11111111;
        endcase
    end
    assign AN = anr;
    
endmodule