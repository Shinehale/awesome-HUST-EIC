`timescale 1ns / 1ps

module top(
    input wire CLK100MHZ,
    input wire [7: 0] SW,
    input wire CPU_RESETN,
    output wire[15: 0] LED
);
    // generate a 1Hz clock.    
    wire CLK1HZ;    
    Divider_1Hz timer(
        .rst (CPU_RESETN),
        .CLK (CLK100MHZ),
        .clk (CLK1HZ)
    );
    M_16 m_top(
        .CP (CLK1HZ),
        .CLR (SW[2]),
        .EN_0 (SW[0]),
        .flag (SW[1]),
        .D (SW[6: 3]),
        .Q (LED),
        .PE (SW[7])
    );
    
endmodule
    