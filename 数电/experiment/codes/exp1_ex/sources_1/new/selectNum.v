`timescale 1ns / 1ps

module SelectNum(
    input wire [15: 0] sw,
    input wire [1: 0] num,
    output wire[3: 0] data
);
    reg [3: 0] dataReg;
    always @ (*) begin
        case (num)
            2'b00: dataReg <= sw[3: 0];
            2'b01: dataReg <= sw[7: 4];
            2'b10: dataReg <= sw[11: 8];
            2'b11: dataReg <= sw[15: 12];
         endcase
    end
    assign data = dataReg;
endmodule