`timescale 1ns / 1ps
module M_16(CP, CLR, EN_0, PE, flag, D, Q);
input CP, CLR, EN_0, PE, flag;
input [3:0] D;
output wire [15:0] Q;

wire [3:0]LED; 

M_4 U0(
    .CP (CP),
    .CLR (CLR),
    .EN (EN_0),
    .PE (PE),
    .D (D),
    .flag (flag),
    .LED (LED)
);
T_4_16 U1(
    .A(LED),
    .EN(EN_0),
    .Q(Q)
);
endmodule

