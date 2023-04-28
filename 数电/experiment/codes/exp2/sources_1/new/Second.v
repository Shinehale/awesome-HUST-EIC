`timescale 1ns / 1ps

module Second(
    input wire CP,
    input wire RST,
    output wire[7:0] data,
    output reg carry
);
    reg [3:0] U0, U1;
    always @(posedge CP or negedge RST) begin
         if (~RST) begin
            U0 <= 0;
            U1 <= 0;
            carry <= 0;
         end else if (U1 < 6 && U0 < 9) begin
            U0 <= U0 + 1'b1;
            carry <= 0;
         end else if (U1 < 5 && U0 == 9) begin
            U0 <= 0;
            U1 <= U1 + 1'b1;
         end 
         else begin
            U1 <= 0;
            U0 <= 0; 
            carry <= 1;
        end
    end
    assign data[7:0] = {U1[3:0], U0[3:0]};
endmodule