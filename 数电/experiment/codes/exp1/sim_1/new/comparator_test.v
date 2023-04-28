`timescale 1ns / 1ps
module comparator_test;
    reg CP;
    reg[1:0] DATA;
    wire[2:0] flags;
    
    initial CP = 1;
    always #2 CP = ~CP;

    Comparator com(CP, DATA, flags);

    initial begin
        DATA = 2'b00;
    #5  DATA = 2'b10;
    #5  DATA = 2'b01;
    #5  DATA = 2'b11;
    end
endmodule
