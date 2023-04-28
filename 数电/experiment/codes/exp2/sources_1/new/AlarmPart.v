`timescale 1ns / 1ps
module AlarmPart(
    input wire CP,
    input wire [5:0] HSET,
    input wire [5:0] MSET,
    input wire [4:0] HDATA,
    input wire [7:0] MDATA,
    output wire [3:0] puncshow,
    output wire [3:0] alarmshow
    );
    // punctual show
    wire clk, puncset, outEN, Clk;
    wire [4:0] hdata;
    reg p = 1, EN = 0;
    reg[15:0] state = 0;
    
    wire [5:0] mdata;
    timer1HZ Unit(CP, clk);
    timer1KHZ Unit0(CP, Clk);
    assign puncset = (MDATA == 8'h0) ? 1 : 0;
    assign hdata = (HDATA == 0) ? 24 : HDATA;
    assign mdata = MDATA[7:4] * 10 + MDATA[3:0];
    assign outEN = EN&p;
    assign puncshow = {outEN, outEN, outEN, outEN};
    
    
    reg [3:0] hregs,mregs;
    reg rst_state, rst_p;
    always @(posedge Clk) begin          
        if (HDATA != hregs || mdata != mregs) begin
            EN = 0;
            if (puncset == 1) begin
                EN = 1;
                rst_state = 0;
                rst_p = 0; 
            end
            hregs = HDATA;
            mregs = mdata;
        end else if (state >= hdata) begin
            EN = 0; 
            rst_state = 0;
        end else begin
            rst_p = 1;
            rst_state = 1;
        end
    end
    always @(posedge clk or negedge rst_p) begin         // generating a 0.5HZ signal
        if (~rst_p) p = 0;
        else p = ~p;
    end 
    always @(posedge p or negedge rst_state) begin
        if (~rst_state) state <= 0;
        else begin
            state <= state + 1;
        end
    end
        
    wire cp;
    timer8HZ Unit1(CP, cp);
    reg rstState = 1, en = 0, re = 0;
    wire outen;
    reg [15:0] State = 0;
    assign outen = cp & en;
    assign alarmshow = {outen, outen, outen, outen};
    
    always @(posedge cp or negedge rstState) begin
        if (~rstState) State <= 0;
        else begin
            State <= State + 1;
        end
    end
    always @(posedge Clk) begin
        if (mdata == MSET && HDATA == HSET) begin
            if (re == 0 && en == 0) begin
                rstState = 0;
                en = 1;
                re = 1;
            end else if (State >= 60) begin
                en = 0;
                rstState = 0;
            end else rstState = 1; 
        end else begin
            en = 0;
            re = 0;
        end
    end
    
endmodule