`timescale 1ns / 1ps


module M_4(CP, CLR, EN, PE, D, flag, LED);
input CP, EN, PE, CLR, flag;
input [3:0] D;
output wire [3:0] LED;

reg [3: 0] led;
always @(posedge CP) begin
    if (PE == 1'b1) begin
        led <= D;
    end else
    if (CLR == 1'b1) begin
        led <= 4'b0000;
    end else
    if(EN == 1'b1) begin
        if(flag == 1'b0) begin
                if(led == 4'b0000) led <= 4'b1111; 
                else led <= led - 1;
        end else begin
                if(led == 4'b1111) led <= 4'b0000; 
                else led <= led + 1;
        end
     end 
end
assign LED = led;

endmodule
