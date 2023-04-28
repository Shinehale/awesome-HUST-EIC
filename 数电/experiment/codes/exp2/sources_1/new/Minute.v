`timescale 1ns / 1ps

module Minute(
    input wire CP,
    input wire RST,
    input wire CARRY,
    input wire ADJMODE,
    input wire CH,
    output wire[7:0] data,
    output reg carry
);
    reg [3:0] U0 = 0, U1 = 0;
    reg adjreg = 0, carryreg = 0;
    always @ (posedge CP or negedge RST) begin
        if (~RST) begin
            U0 <= 4'b0;
            U1 <= 4'b0;
            carry <= 1'b0;
        end else if (CARRY) begin
            if (carryreg == 0) begin
                if (U0 < 9) begin
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
                carryreg <= 1;
            end 
        end else if (CH) begin 
            carryreg <= 0;
            if (adjreg == 0) begin
                if ({CH, ADJMODE} == 2'b10) begin
                    if (U0 < 9) begin
                        U0 <= U0 + 1'b1;
                        carry <= 0;
                    end else if (U1 < 5 && U0 == 9) begin
                        U0 <= 0;
                        U1 <= U1 + 1'b1;
                    end else begin
                        U1 <= 0;
                        U0 <= 0; 
                        carry <= 1;
                    end
                end else if ({CH, ADJMODE} == 2'b11) begin
                    if (U0 > 0) begin
                        U0 <= U0 - 1;
                        carry <= 0;
                    end else if (U1 > 0 && U0 == 0) begin
                        U0 <= 9;
                        U1 <= U1 - 1;
                    end else begin
                        U0 <= 9;
                        U1 <= 5;
                    end
                end
                adjreg <= 1;
            end
        end else begin
            adjreg <= 0;
            carryreg <= 0;
        end            
    end
    assign data[7:0] = {U1[3:0], U0[3:0]};
endmodule