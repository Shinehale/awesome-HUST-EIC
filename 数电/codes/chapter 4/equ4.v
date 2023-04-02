module equ4( a, b, f );
input [3:0] a, b;
output f;

assign f = !(a ^ b);

endmodule
