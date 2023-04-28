`timescale 1ns / 1ps

module timer1HZ(
    input CP,
    output reg Clk = 0 
);
    
    reg [30: 0] state;
    always @ (posedge CP) begin
        if (state < 49999999) state <= state + 1'b1;
        else begin
            state <= 0;
            Clk <= ~Clk;
        end
    end
endmodule