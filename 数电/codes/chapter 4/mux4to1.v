module mux4to1(D0, D1, D2, D3, W, A0, A1);
input D0, D1, D2, D3, A0, A1;
output W;

assign W = ({A1, A0} == 2'b00) ? D0:
			(({A1, A0} == 2'b01) ? D1:
			(({A1, A0} == 2'b10) ? D2:
			(({A1, A0} == 2'b11) ? D3:
				1'b0)));

endmodule