
module stepper (Sin,CP,nCR,Out);
input Sin,CP,nCR;
output Out;
reg [2:0] Current_state,Next_state,Out;
parameter S0=3'b000,S1=3'b001,S2=3'b010,S3=3'b011,
          S4=3'b100,S5=3'b101,S6=3'b110,S7=3'b111;
wire clk;
timer1HZ Unit(CP, clk);
always@(posedge clk or negedge nCR)
begin
    if(~nCR)
        Current_state<=S7;
    else
    Current_state<=Next_state;
end
always@(Current_state) begin
case(Current_state)
    S0:begin
        Out=Current_state;
        Next_state=S6;
    end
    S1:begin
        Out=Current_state;
        Next_state=(Sin==1)?S3:S5;
    end
    S2:begin
        Out=Current_state;
        Next_state=(Sin==1)?S6:S3;
    end
    S3:begin
        Out=Current_state;
        Next_state=(Sin==1)?S2:S1;
    end
    S4:begin
        Out=Current_state;
        Next_state=(Sin==1)?S5:S6;
    end
    S5:begin
        Out=Current_state;
        Next_state=(Sin==1)?S1:S4;
    end
    S6:begin
        Out=Current_state;
        Next_state=(Sin==1)?S4:S2;
    end
    S7:begin
        Out=Current_state;
        Next_state=S0;
    end
endcase
end
endmodule

