`timescale 1ns / 1ps
module tb_stepper();
    reg  Sin,CLK,nCR;
    wire [2:0]Out;
     parameter PERIOD = 10;

   initial begin
      CLK = 1'b0;
      #(PERIOD/2);
      forever
         #(PERIOD/2) CLK = ~CLK;
   end

   initial begin
       nCR = 1'b0;
       Sin = 1'b0;
       #20 nCR = 1'b1;
   end

    always #120 Sin = ~Sin;

    stepper U0(
        .Sin    (Sin),
        .CP     (CLK),
        .nCR    (nCR),
        .Out    (Out));

                
endmodule
