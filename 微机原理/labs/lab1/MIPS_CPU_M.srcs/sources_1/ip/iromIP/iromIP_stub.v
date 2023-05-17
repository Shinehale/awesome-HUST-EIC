// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2018.3 (win64) Build 2405991 Thu Dec  6 23:38:27 MST 2018
// Date        : Wed Mar 29 18:40:08 2023
// Host        : Hale running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               D:/vivado-learning/MIPS_CPU_M/MIPS_CPU_M.srcs/sources_1/ip/iromIP/iromIP_stub.v
// Design      : iromIP
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7a100tcsg324-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* x_core_info = "blk_mem_gen_v8_4_2,Vivado 2018.3" *)
module iromIP(clka, addra, douta)
/* synthesis syn_black_box black_box_pad_pin="clka,addra[4:0],douta[31:0]" */;
  input clka;
  input [4:0]addra;
  output [31:0]douta;
endmodule
