`timescale 1ns / 1ps

module CPUMips(
    input Clk,
    input Reset,
    output t
);
    wire [31:0] TempPC, MuxPC, JumpPC, BranchPC, SquencePC, Imm32, ImmL2, RegWD, RsData, RtData, ALUIn2, ALURes, MemRD, Instr;
    wire [4:0] RegWA;
    wire [27:0] PsudeoPC;
    wire BranchZ, J, B, Zero, RegDst, RegWr, ALUSrc, MemWR, Mem2Reg;
    wire [1:0] ALUOp;
    wire [3:0] ALUCtr;
    reg [31:0] PC;

    
    assign PsudeoPC = {Instr[25:0], 2'b00};
    assign JumpPC = {SquencePC[31:28], PsudeoPC};
    assign SquencePC = PC + 4;
    assign BranchPC = ImmL2 + SquencePC;
    assign MuxPC = BranchZ?BranchPC:SquencePC;
    assign TempPC = J?JumpPC:MuxPC;
    assign BranchZ = B&Zero;
    
    assign ImmL2 = {Imm32[29:0], 2'b00};
    assign Imm32 = {Instr[15]?16'hffff:16'h0, Instr[15:0]};
    assign ALUIn2 = ALUSrc?Imm32:RtData;
    
    assign RegWA = RegDst?Instr[15:11]:Instr[20:16];
    assign RegWD = Mem2Reg?MemRD:ALURes;
    
    ALU UnitALU (RsData, ALUIn2, ALUCtr, ALURes, Zero);
    dramIP Unitdram(~Clk, MemWR, ALURes[6:2], RtData, MemRD);
    iromIP Unitirom(~Clk, PC[6:2], Instr);
    RegFile UnitRegFile(Instr[25:21], Instr[20:16], RegWA, RegWD, RegWr, ~Clk, Reset, RsData, RtData);
    Controller UnitController(Instr[31:26], Instr[20:16], Instr[5:0], J, B, RegDst, RegWr, ALUSrc, MemWR, Mem2Reg, ALUCtr);

    always @(posedge Clk) begin
        if (Reset)
            PC <= 0;
        else
            PC <= TempPC;
    end

endmodule