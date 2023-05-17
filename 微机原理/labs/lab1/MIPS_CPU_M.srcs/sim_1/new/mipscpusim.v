`timescale 1ns / 1ps

module mipscpusim();
    
    reg Clk, Reset;
    
    CPUMips Unit(
        .Clk (Clk),
        .Reset (Reset)
    );
    parameter PERIOD = 10;
    always begin
        Clk = 1'b0;
        # (PERIOD/2) Clk = 1'b1;
        # (PERIOD/2);
    end
    initial begin
            Reset = 1;
        #20 Reset = 0;
    end
endmodule