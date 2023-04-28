`timescale 1ns / 1ps

module Hour(
	input wire CP,
	input wire RST,
	input wire CARRY,
	input wire ADJMODE,
	input wire CH,
	input wire STYLE,
	output wire[15:0] data,
	output wire [4:0] hourdata
);
    reg [5:0] inner_data;
    reg [3:0] U0 = 0, U1 = 0, U2 = 4'hc;
    assign data[15:12] = U2;
    assign data[11:8] = 4'hc;
    assign data[7:0] = {U1, U0};
    assign hourdata[4:0] = inner_data[4:0];
    reg adjreg = 0, carryreg = 0;
    
    always @ (posedge CP or negedge RST) begin
        if (~RST) inner_data <= 0;
        else begin
            if (CARRY) begin
                if (carryreg == 0) begin
                    if (inner_data == 23) inner_data <= 0;
                    else inner_data <= inner_data + 1;
                    carryreg <= 1;
                end 
            end else if (CH) begin
                carryreg <= 0;
                if (adjreg == 0) begin
                    if ({CH, ADJMODE} == 2'b10) begin
                        if (inner_data == 23) inner_data <= 0;
                        else inner_data <= inner_data + 1;
                    end else if ({CH, ADJMODE} == 2'b11) begin
                        if (inner_data == 0) inner_data <= 23;
                        else inner_data <= inner_data - 1;
                    end 
                    adjreg <= 1;
                end 
            end else begin
                carryreg <= 0;
                adjreg <= 0;
            end
        end
    end
    
    always @ (posedge CP) begin
        if (STYLE == 1'b1) begin
            if (inner_data > 12) begin
                U2 = 4'hb;
                U1 = (inner_data - 12) / 10;
                U0 = (inner_data - 12) - U1 * 10; 
            end else begin
                if (inner_data == 12) U2 = 4'hb; 
                else U2 = 4'ha;
                U1 = inner_data / 10;
                U0 = inner_data - U1 * 10; 
            end
        end else begin
            U2 = 4'hc;
            U1 = inner_data / 10;
            U0 = inner_data - U1 * 10; 
        end
    end

endmodule