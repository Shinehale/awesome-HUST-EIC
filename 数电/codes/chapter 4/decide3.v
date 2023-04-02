module decide3( a, b, c, f );
input a, b, c;
output f;

nand u1( t1, a, b );
nand u2( t2, a, c );
nand u3( t3, b, c );
nand u4( f, t1, t2, t3 );

endmodule

