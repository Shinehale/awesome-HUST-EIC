module mux2to1_df( 
	input D0, D1, S,
	output wire Y
);

assign Y = (~S & D0) | (S & D1);

endmodule