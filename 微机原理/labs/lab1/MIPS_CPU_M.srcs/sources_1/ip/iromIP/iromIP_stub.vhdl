-- Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2018.3 (win64) Build 2405991 Thu Dec  6 23:38:27 MST 2018
-- Date        : Wed Mar 29 18:40:08 2023
-- Host        : Hale running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode synth_stub
--               D:/vivado-learning/MIPS_CPU_M/MIPS_CPU_M.srcs/sources_1/ip/iromIP/iromIP_stub.vhdl
-- Design      : iromIP
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xc7a100tcsg324-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity iromIP is
  Port ( 
    clka : in STD_LOGIC;
    addra : in STD_LOGIC_VECTOR ( 4 downto 0 );
    douta : out STD_LOGIC_VECTOR ( 31 downto 0 )
  );

end iromIP;

architecture stub of iromIP is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "clka,addra[4:0],douta[31:0]";
attribute x_core_info : string;
attribute x_core_info of stub : architecture is "blk_mem_gen_v8_4_2,Vivado 2018.3";
begin
end;
