module demux1to4(D, Y0, Y1, Y2, Y3, A0, A1);
input A0, A1, D;
output Y0, Y1, Y2, Y3;

assign Y0 = ({A1, A0} == 2'b00) ? D : 1'b0; 
assign Y1 = ({A1, A0} == 2'b01) ? D : 1'b0; 
assign Y2 = ({A1, A0} == 2'b10) ? D : 1'b0; 
assign Y3 = ({A1, A0} == 2'b11) ? D : 1'b0; 

endmodule
