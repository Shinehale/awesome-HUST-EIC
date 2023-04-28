module Clock(
    input wire CLK100MHZ,
    input wire CPU_RESETN, BTNU,
    input wire [15:0] SW,
    output wire [7:0] AN,
    output wire [15:0] LED,
    output wire CA, CB, CC, CD, CE, CF, CG
);
    /*
        Input signal Summary:
           1. CLK100MHZ: the input the CP which is used for the generation of 1kHz, 1Hz signal.
           2. AN:   for the group of selecting of sevenseg display.
           3. SW:
                    1) SW[0]: take control of the hour model.
                    2) SW[1]: take control of the up or down model.
                    3) SW[2]: take control of the up/down for the minute(0) or hour(1) 
                    4) SW[3]: take control of the on/off for the alarm model
                    5) SW[15:10]: for setting the alarm of the hour
                    6) SW[9:4]: fot setting the alarm of the minute
           4. CA, CB, CC, CD, CE, CF, CG: for the single sevenseg display.
           5. CPU_RESETN(default: 1): as the second Enable button.
           6. BTNU(default: 0) as the a signal for the up/down.
           7. LED[3:0]: for the punctually alarm display.
    */  
    
    wire rst;
    wire [31:0] data;
    wire [6:0] segs;
    wire [4:0] hourdata;
    wire clk;
    wire [5:0] hset, mset;
    timer1HZ Unit(CLK100MHZ, clk);
    assign LED[15] = clk;
    
    assign rst = CPU_RESETN; 
    assign {CA, CB, CC, CD, CE, CF, CG} = segs;
    assign hset = {SW[3],SW[3],SW[3],SW[3],SW[3],SW[3]}&SW[15:10];
    assign mset = {SW[3],SW[3],SW[3],SW[3],SW[3],SW[3]}&SW[9:4];
    MainPart Unit1(CLK100MHZ, rst, SW[0], SW[1], SW[2], BTNU, data, hourdata);
    DisplayPart Unit2(CLK100MHZ, data, AN, segs);    
    AlarmPart Unit3(CLK100MHZ, hset, mset, hourdata, data[15:8], LED[11:8], LED[3:0]);
    
endmodule