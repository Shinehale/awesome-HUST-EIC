`timescale 1ns / 1ps

module SelectNum(
    input wire [31: 0] DATA,
    input wire [2: 0] NUM,
    output wire[3: 0] data
);
    reg [3: 0] dataReg;
    always @ (*) begin
        case (NUM)
            3'b000: dataReg <= DATA[3: 0];
            3'b001: dataReg <= DATA[7: 4];
            3'b010: dataReg <= DATA[11: 8];
            3'b011: dataReg <= DATA[15: 12];
            3'b100: dataReg <= DATA[19: 16];
            3'b101: dataReg <= DATA[23: 20];
            3'b110: dataReg <= DATA[27: 24];
            3'b111: dataReg <= DATA[31: 28];
          default: dataReg <= 4'b0000;
         endcase
    end
    assign data = dataReg;
endmodule