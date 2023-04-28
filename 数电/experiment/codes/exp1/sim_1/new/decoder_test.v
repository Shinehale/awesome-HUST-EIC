`timescale 1ns / 1ps
module decoder_test;
    reg CP;
    reg[2:0] DATA;
    wire[7:0] outcomes;
    
    initial CP = 1;
    always #2 CP = ~CP;

    Decoder3_8 Unit(CP, DATA, outcomes);
    
    initial begin
         DATA = 3'b000;
    #10  DATA = 3'b001;
    #10  DATA = 3'b010;
    #10  DATA = 3'b011;
    #10  DATA = 3'b100;
    #10  DATA = 3'b101;
    #10  DATA = 3'b110;
    #10  DATA = 3'b111;
    end

endmodule;