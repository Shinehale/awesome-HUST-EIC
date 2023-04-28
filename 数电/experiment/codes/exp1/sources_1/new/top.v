`timescale 1ns / 1ps

module top(
    input CLK100MHZ,
    input wire[15:0] SW,
    output wire[14:0] LED
);
    mux2_1 Unit1(CLK100MHZ, SW[1:0], LED[0], SW[2]);
    Comparator Unit2(CLK100MHZ, SW[4:3], LED[3:1]);
    Decoder3_8(CLK100MHZ, SW[7:5], LED[11:4]);
    Encoder8_3(CLK100MHZ, SW[15:8], LED[14:12]);
endmodule