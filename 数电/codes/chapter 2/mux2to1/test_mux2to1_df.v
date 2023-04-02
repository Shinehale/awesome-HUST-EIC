`timescale 1ns/1ns
module test_mux2to1_df;
	reg PD0, PD1, PS;
	wire PY;

	mux2to1_df t_mux(PD0, PD1, PS, PY);

	initial begin
			PS = 0; PD1 = 0; PD0 = 0;
	#5		PS = 0; PD1 = 0; PD0 = 1;
	#5		PS = 0; PD1 = 1; PD0 = 0;
	#5		PS = 0; PD1 = 1; PD0 = 1;
	#5		PS = 1; PD1 = 0; PD0 = 0;
	#5		PS = 1; PD1 = 0; PD0 = 1;
	#5		PS = 1; PD1 = 1; PD0 = 0;
	#5		PS = 1; PD1 = 1; PD0 = 1;
	#5  	PS = 0; PD1 = 0; PD0 = 0;
	#5 		$stop;
			end
	initial begin
		$monitor( $time, ":\tS = %b\tD1 = %b\tD0 = %b\tY = %b",
									PS, PD1, PD0, PY);
			end
endmodule