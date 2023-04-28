`timescale 1ns / 1ps
module SevenSegDis(
    input wire clk,
    input wire [15: 0] sw,
    output wire [7:0] an,
    output wire [6: 0] seg
);
    reg [1: 0] times;
    wire [3: 0] data;
    always @ ( posedge clk) begin
        if ( times == 2'b11 ) times <= 2'b00;
        else times <= times + 1; 
    end
    
    SelectNum sn(               // with time goes, select target data to display
        .sw (sw),
        .num (times),
        .data (data)
    );
    
    SevenSegDecoder ssd (
        .data (data),
        .segments (seg)
    );
    
    SelectAN sa(
        .num (times),
        .an (an)
    );
endmodule