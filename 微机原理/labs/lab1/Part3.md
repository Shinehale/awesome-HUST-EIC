## Part3 execuation

扩展实现如下指令：

- `bne`
- `bltz`
- `bgez`

能够运行如下的asm文件：

```asm
main:
	bne $t1 $t1 label1
	bne $t1 $t0 label1
label2:
	bltz $t1, label3
label1:	
	bltz $t0, label2
label3:
	bgez $t1, label2
	bgez $t0, label4
	bne $t1, $t1, label1
label4:	
	bgez $0, label4
```

为了完成想要支持的指令集，考虑将`ALUOp`信号进行扩展为三位，这一举动将会改变`MainCtr`、`ALUControl`和`ALU`文件，而对外信号zero保持不变，多种情况复用zero标志位即可, 即无论ALU内部怎么操作，保证zero信号对外时，高电平表示此情况可以跳转，低电平表示此情况不可跳转，

具体说明如下：

- `R`指令：`1001_000_10` ----> `1001_000_100`

- `sw` `lw`指令：`xxxx_xxx_00` ---->`xxxx_xxx_000` (其中x并不表示高阻态)

- `jmp`指令：`xxx0_001_xx` --->`xxx0_001_xxx` （其中x表示高阻态）

- `beq`指令`x0x0_010_01` ---> `x0x0_010_010`   --> `0110`

  `bnq` 指令`x0x0_010_011` ---> `0100`

  `bltz和`指令`x0x0_010_110` --- > `1110`

  `bgez`指令`x0x0_010_111`  ---->  `1111`



### bne的实现

举例：

$15290002  \rightarrow 000101\_01001\_01001\_0000 0000 0000 0010$ 

此类指令的格式为`Op Rs Rt Imm`

- `Op`为 `000101` 仅作为flag使用即可

### bltz的实现

举例：

$05200001 \rightarrow 000001\_01001\_00000\_0000000000000001$

此类指令格式借用了`Op Rs Rt Imm`

- `op` 为 `000001`
-  只是`Rt`的位置放置为0

### bgez的实现

$05210001 \rightarrow 000001\_01001\_00001\_0000000000000001$

此类指令格式借用了`Op Rs Rt Imm` 

- `op` 为 `000001`
- 只是`Rt`的位置放置为1



综上只需要，将`Rst`组线接入`MainCtr`即可判断