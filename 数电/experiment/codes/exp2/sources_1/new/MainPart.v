module MainPart(
    input wire CP,
    input wire RST,
    input wire HMODE,
    input wire ADJMODE,
    input wire SELMODE,
    input wire CH,
    output wire [31:0] data,
    output wire [4:0] hourdata
);  
    wire clk, CLK;
    timer1HZ Unit0_0(CP, clk);
    timer1KHZ Unit0_1(CP, CLK);
    wire sectomin, mintohour;
    wire minsel, hoursel;
    
    assign minsel = ~SELMODE&CH;
    assign hoursel = SELMODE&CH;
    
    Second Unit1(clk, RST, data[7:0], sectomin);
    Minute Unit2(CLK, RST, sectomin, ADJMODE, minsel, data[15:8], mintohour);
    Hour Unit3(CLK,RST, mintohour, ADJMODE, hoursel, HMODE, data[31:16], hourdata);
endmodule