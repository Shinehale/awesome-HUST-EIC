module decide3( a, b, c, f );
input a, b, c;
output f;
wire [1:0] sum;

assign sum = a + b + c;
assign f = sum[1];

endmodule
