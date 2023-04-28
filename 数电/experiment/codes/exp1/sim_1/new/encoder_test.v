`timescale 1ns / 1ps
module encoder_test;
    reg CP;
    reg[7:0] DATA;
    wire[2:0] outcomes;
    
    initial CP = 1;
    always #1 CP = ~CP;

    Encoder8_3 Unit(CP, DATA, outcomes);
    
    initial begin
         DATA = 8'h01;
    #10  DATA = 8'h02;
    #10  DATA = 8'h04;
    #10  DATA = 8'h08;
    #10  DATA = 8'h10;
    #10  DATA = 8'h20;
    #10  DATA = 8'h40;
    #10  DATA = 8'h80;
    end

endmodule;