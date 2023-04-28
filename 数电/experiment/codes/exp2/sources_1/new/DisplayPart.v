module DisplayPart(
    input wire CP,
    input wire [31:0] DATA,
    output wire [7:0] an,
    output wire [6:0] segs
);
    wire clk;
    timer1KHZ inner_clk(CP, clk);
    
    reg [2: 0] times;
    always @ (posedge clk) begin
        if (times < 3'b111) times <= times + 1;
        else times <= 3'b000;  
    end
    
    wire [3:0] inner_data;
    SelectAN Unit1(
        .NUM (times),
        .AN (an)
    );
    SelectNum Unit2(
        .DATA (DATA),
        .NUM (times),
        .data (inner_data)
    );
    SevenSegDecoder Unit3(
        .DATA (inner_data),
        .segments (segs)
    );
endmodule