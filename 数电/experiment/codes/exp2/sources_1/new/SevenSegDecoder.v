module SevenSegDecoder(
    input wire [3:0]  DATA,
    output wire [6:0]  segments
);
    reg cg, cf, ce, cd, cc, cb, ca;
    always @(DATA) begin
            case(DATA)
                4'h0: {ca, cb, cc, cd, ce, cf, cg} = 7'b0000_001;
                4'h1: {ca, cb, cc, cd, ce, cf, cg} = 7'b1001_111;
                4'h2: {ca, cb, cc, cd, ce, cf, cg} = 7'b0010_010;
                4'h3: {ca, cb, cc, cd, ce, cf, cg} = 7'b0000_110;
                4'h4: {ca, cb, cc, cd, ce, cf, cg} = 7'b1001_100;
                4'h5: {ca, cb, cc, cd, ce, cf, cg} = 7'b0100_100;
                4'h6: {ca, cb, cc, cd, ce, cf, cg} = 7'b0100_000;
                4'h7: {ca, cb, cc, cd, ce, cf, cg} = 7'b0001_111;
                4'h8: {ca, cb, cc, cd, ce, cf, cg} = 7'b0000_000;
                4'h9: {ca, cb, cc, cd, ce, cf, cg} = 7'b0001_100;
                4'ha: {ca, cb, cc, cd, ce, cf, cg} = 7'b0001_000;
                4'hb: {ca, cb, cc, cd, ce, cf, cg} = 7'b0011_000;                       // b -> P
                default: {ca, cb, cc, cd, ce, cf, cg} = 7'b1111_111;
            endcase
    end
        
    assign segments = {ca, cb, cc, cd, ce, cf, cg};

endmodule