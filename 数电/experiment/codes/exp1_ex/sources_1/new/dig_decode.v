`timescale 1ns / 1ps

module Top(
    /****************************** Input **********************************************/
    input wire CLK100MHZ,
    input wire CPU_RESETN,
    input wire [15: 0] SW,
    /****************************** Output *******************************************/
    output wire CA, CB, CC, CD, CE, CF, CG,
    output wire [7: 0] AN
);    
    wire clk, rst, nclk;
    assign rst = !CPU_RESETN;
    wire [6: 0] assignment;
    wire [7: 0] an;
    
    defparam timer.n = 250000;      // timer ==> make the time to target frequency
    Timer timer(
        .rst (rst),
        .CLK (CLK100MHZ),
        .clk (nclk)
    );
    
    SevenSegDis ssd(            // SevenSegDis ==> have the target segment display
        .sw (SW),
        .clk (nclk),
        .an (an),
        .seg (assignment)
    );
    
    assign AN = an;
    assign {CA, CB, CC, CD, CE, CF, CG} = assignment;
  
endmodule