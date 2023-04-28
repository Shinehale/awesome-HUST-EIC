`timescale 1ns / 1ps
module  mux_test;
    reg CP;
    reg[1:0] DATA;
    wire outcome;
    
    initial CP = 1;
    always #5 CP = ~CP;
    
    mux2_1 Unit(CP, DATA, outcome);
    
    initial begin
        DATA = 2'b00;
    #5  DATA = 2'b10;
    #5  DATA = 2'b01;
    #5  DATA = 2'b11;
    end

endmodule