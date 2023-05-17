`timescale 1ns / 1ps
module MIPSCPU (Clk,Reset);
// codes
  input Clk;
  input Reset;
  wire [31: 0] NextPC, CurrentPC, Instr, SeqPC, jumpPC, BranPC;
  wire [31: 0] Imm32, Imm32_offset, MemDataOut;
  wire [31: 0] RegDataIn, RsData, RtData, ALUSrc2, ALUData;
  wire [27: 0] jmp_low_order;
  wire [4: 0] WrAddr;
  wire [3: 0] ALUCtr;
  wire [1: 0] sel;
  wire Reset, RegDst, Zero;
  wire J, B, RegWr, ALUSrc, MemWr, Mem2Reg;

  
  defparam PC.n = 32;
  PC PC(
		.D (NextPC), 
		.Clk (Clk),
		.Reset (Reset),
		.Q (CurrentPC)
  );
  
  defparam ROM_U0.n = 5;
  InstrROM ROM_U0(
		.Addr (CurrentPC[6: 2]),
		.Clk (~Clk),
		.Instr (Instr)
  );
  
  defparam adder1.n = 32;
  Adder adder1(
		.In2 (CurrentPC),
		.In1 (32'd4),
		.Out (SeqPC)
  );

  defparam adder2.n = 32;
  Adder adder2(
  	.In1 (SeqPC),
  	.In2 (Imm32_offset),
  	.Out (BranPC)
  );

  defparam left_shift1.n = 26;
  defparam left_shift1.m = 28;
  defparam left_shift1.x = 2;
  LeftShift left_shift1(
  	.In (Instr[25: 0]),
  	.Out (jmp_low_order)
  );

  defparam left_shift2.n = 32;
  defparam left_shift2.m = 32;
  defparam left_shift2.x = 2;
  LeftShift left_shift2(
  	.In (Imm32),
  	.Out (Imm32_offset)
  );

  defparam mux2_1_1.n = 5;
  Mux2_1 mux2_1_1(
  	.In1 (Instr[20: 16]),
  	.In2 (Instr[15: 11]),
  	.sel (RegDst),
  	.Out (WrAddr)
  );

  defparam mux2_1_2.n = 32;
  Mux2_1 mux2_1_2(
  	.In1 (RtData),
  	.In2 (Imm32),
  	.sel (ALUSrc),
  	.Out (ALUSrc2)
  );

  defparam mux2_1_3.n = 32;
  Mux2_1 mux2_1_3(
  	.In1 (ALUData),
  	.In2 (MemDataOut),
  	.sel (Mem2Reg),
  	.Out (RegDataIn)
  );

  defparam  mux3_1.n = 32;
  Mux3_1 mux3_1(
  	.In1 (SeqPC),
  	.In2 (BranPC),
  	.In3 (jumpPC),
  	.sel (sel),
  	.Out (NextPC)
  );


  defparam concat1.n = 4;
  defparam concat1.m = 28;
  Concat concat1(
  	.In1 (SeqPC[31:28]),
  	.In2 (jmp_low_order),
  	.Out (jumpPC)
  );

  defparam concat2.n = 1;
  defparam concat2.m = 1;
  Concat concat2(
  	.In1 (J),
  	.In2 (B & Zero),
  	.Out (sel)
  );


  defparam signEx.n = 16;
  defparam signEx.m = 32;
  SignedExtend signEx(
  	.In (Instr[15: 0]),
  	.Out (Imm32)
  );

  Controller controller(
  	.OpCode (Instr[31: 26]),
  	.Funct (Instr[5: 0]),
  	.J (J),
  	.B (B),
  	.RegDst (RegDst),
  	.RegWr (RegWr),
  	.ALUSrc (ALUSrc),
  	.Mem2Reg (Mem2Reg),
  	.ALUCtr (ALUCtr)
  );

  RegFile RegFile_U1(
  	.DataIn (RegDataIn),
	.RsAddr (Instr[25: 21]),
  	.RtAddr (Instr[20: 16]),
  	.WrAddr (WrAddr),
  	.RegWr (RegWr),
  	.Clk (Clk),
  	.RsData (RsData),
  	.RtData (RtData)
  );

  ALU alu(
  	.In1 (RsData),
  	.In2 (ALUSrc2),
  	.ALUCtr (ALUCtr),
  	.Res (ALUData),
  	.Zero (Zero)
  );

  defparam RAM_U3.n = 5;
  defparam RAM_U3.m = 32;
  DataRAM RAM_U3(
  	.DataIn (ALUData),
  	.Addr (ALUData[6: 2]),
	.MemWR (MemWr),
  	.Clk (Clk),
  	.DataOut (MemDataOut)
  );
endmodule
