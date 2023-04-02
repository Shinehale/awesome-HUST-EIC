## chapter 8 FPGA and CPLD

### 概述

- 可编程逻辑器件(programmable logic device) （**PLD**）
- 出厂时不具备任何逻辑功能，由用户通过“编程”定义器件的逻辑功能
- 可多次擦除和反复编程

特点：

- 集成度高
- 电路尺寸小
- 功耗低
- 可靠性高
- 用户的专用电路
- 不改电路可变更系统功能

![](../../../../../%E6%9D%A8%E7%AD%A0%E6%9D%BE/Desktop/%E6%9C%9F%E6%9C%AB%E8%80%83%E8%AF%95/digital-circuit/notes/img/8-1.png)

### 组合可编程逻辑器件

![](../../../../../%E6%9D%A8%E7%AD%A0%E6%9D%BE/Desktop/%E6%9C%9F%E6%9C%AB%E8%80%83%E8%AF%95/digital-circuit/notes/img/8-2.png)

#### SPLD符号基本表示法

![](../../../../../%E6%9D%A8%E7%AD%A0%E6%9D%BE/Desktop/%E6%9C%9F%E6%9C%AB%E8%80%83%E8%AF%95/digital-circuit/notes/img/8-3.png)

##### 连接方式

- 硬线连接单元
- 被编程连通单元
- 被编程擦除单元

##### 基本门电路的表示方法

![](../../../../../%E6%9D%A8%E7%AD%A0%E6%9D%BE/Desktop/%E6%9C%9F%E6%9C%AB%E8%80%83%E8%AF%95/digital-circuit/notes/img/8-4.png)

![](../../../../../%E6%9D%A8%E7%AD%A0%E6%9D%BE/Desktop/%E6%9C%9F%E6%9C%AB%E8%80%83%E8%AF%95/digital-circuit/notes/img/8-5.png)

#### SPLD编程连接技术

![](../../../../../%E6%9D%A8%E7%AD%A0%E6%9D%BE/Desktop/%E6%9C%9F%E6%9C%AB%E8%80%83%E8%AF%95/digital-circuit/notes/img/8-6.png)

![](../../../../../%E6%9D%A8%E7%AD%A0%E6%9D%BE/Desktop/%E6%9C%9F%E6%9C%AB%E8%80%83%E8%AF%95/digital-circuit/notes/img/8-7.png)

![](../../../../../%E6%9D%A8%E7%AD%A0%E6%9D%BE/Desktop/%E6%9C%9F%E6%9C%AB%E8%80%83%E8%AF%95/digital-circuit/notes/img/8-8.png)

#### 举例

![](../../../../../%E6%9D%A8%E7%AD%A0%E6%9D%BE/Desktop/%E6%9C%9F%E6%9C%AB%E8%80%83%E8%AF%95/digital-circuit/notes/img/8-9.png)

### 时序可编程逻辑器件GAL

#### 基本结构

![](../../../../../%E6%9D%A8%E7%AD%A0%E6%9D%BE/Desktop/%E6%9C%9F%E6%9C%AB%E8%80%83%E8%AF%95/digital-circuit/notes/img/8-10.png)

##### GAL

![](../../../../../%E6%9D%A8%E7%AD%A0%E6%9D%BE/Desktop/%E6%9C%9F%E6%9C%AB%E8%80%83%E8%AF%95/digital-circuit/notes/img/8-11.png)

![](../../../../../%E6%9D%A8%E7%AD%A0%E6%9D%BE/Desktop/%E6%9C%9F%E6%9C%AB%E8%80%83%E8%AF%95/digital-circuit/notes/img/8-12.png)

##### GAL优点

- 采用电可擦除$E^2CMOS$工艺可以进行多次编程
- 输出端设置了可编程的输出逻辑宏单元（OLMC），通过编程可将OLMC设置成不同的工作状态，器件的通用性更强
- 工作速度快，功耗小

##### 缺点

- 电路规模仍显不足



### 复杂可编程逻辑器件（CPLD）

![](../../../../../%E6%9D%A8%E7%AD%A0%E6%9D%BE/Desktop/%E6%9C%9F%E6%9C%AB%E8%80%83%E8%AF%95/digital-circuit/notes/img/8-13.png)

编程技术：（1）$E^2PROM$  （2）快闪存储器

#### 逻辑块

![](../../../../../%E6%9D%A8%E7%AD%A0%E6%9D%BE/Desktop/%E6%9C%9F%E6%9C%AB%E8%80%83%E8%AF%95/digital-circuit/notes/img/8-14.png)

组成包括：

- 可编程乘积项阵列（与阵列）
- 乘积项分配
- 宏单元
  - 包括一个或门、一个触发器、一些可编程的数据选择器及控制门
  - 功能：
    - 组合逻辑输出
    - 寄存器输出
    - 清零或置位
  - 宏单元的输出去处
    - $I/O$块
    - 内部连线区

上述三个部分组成

- XC9500系列：
  - 90个36变量乘积项
  - 90个乘积项可以组合到一个宏单元中，产生90个乘积项的与或式
  - $n=36,m=18$
- MAX7000系列
  - $n=36，m=16$
  - 80个36变量乘积项
  - 还可以使同一个乘积项被多个宏单元共享

#### $I/O$块

主要由$I/O$单元组成

![](../../../../../%E6%9D%A8%E7%AD%A0%E6%9D%BE/Desktop/%E6%9C%9F%E6%9C%AB%E8%80%83%E8%AF%95/digital-circuit/notes/img/8-15.png)

#### 可编程内部连线

##### 作用

- 实现逻辑块与逻辑块之间
- 逻辑块与$I/O$快之间
- 全局信号到逻辑块和$I/O$块之间的连接

##### 连线方式

$E^2CMOS$单元编程实现



### 现场可编程逻辑门阵列（FPGA）

编程技术：

- SRAM（无限次编程）

- 反熔丝（只能编程一次，主要用于大批量定型产品）

  熔丝编程前呈现高阻态，相当于断开，加高压电编程后，熔丝电阻小，相当于导通。占用面积小

实现组合逻辑函数:查找表（数据选择器+存储单元）

##### 输入变量扩展

![](../../../../../%E6%9D%A8%E7%AD%A0%E6%9D%BE/Desktop/%E6%9C%9F%E6%9C%AB%E8%80%83%E8%AF%95/digital-circuit/notes/img/8-16.png)

#### 可编程逻辑块

##### 基本逻辑块

![](../../../../../%E6%9D%A8%E7%AD%A0%E6%9D%BE/Desktop/%E6%9C%9F%E6%9C%AB%E8%80%83%E8%AF%95/digital-circuit/notes/img/8-17.png)

![](../../../../../%E6%9D%A8%E7%AD%A0%E6%9D%BE/Desktop/%E6%9C%9F%E6%9C%AB%E8%80%83%E8%AF%95/digital-circuit/notes/img/8-18.png)

#### 可编程连线资源

主要包括：

- 通用连线资源
  - 纵向、横向连线、可编程开关

![](../../../../../%E6%9D%A8%E7%AD%A0%E6%9D%BE/Desktop/%E6%9C%9F%E6%9C%AB%E8%80%83%E8%AF%95/digital-circuit/notes/img/8-19.png)

- 进位链

- 时钟信号链

  ​	由于同步时序电路需要时钟同时驱动众多触发器，且要考虑不同时钟路径的时延和驱动，所以FPGA中专门设计了全局时钟网络。 

- 引脚分配连线资源

  I/O块外围的附加连线资源，称为万能环。它们使引脚的交换和锁定与内部逻辑无关。

**通过优化电路布局和连线，可以减小传输延迟时间，提高工作速度**

#### 可编程$I/O$块

![](../../../../../%E6%9D%A8%E7%AD%A0%E6%9D%BE/Desktop/%E6%9C%9F%E6%9C%AB%E8%80%83%E8%AF%95/digital-circuit/notes/img/8-20.png)

![](../../../../../%E6%9D%A8%E7%AD%A0%E6%9D%BE/Desktop/%E6%9C%9F%E6%9C%AB%E8%80%83%E8%AF%95/digital-circuit/notes/img/8-21.png)

![](../../../../../%E6%9D%A8%E7%AD%A0%E6%9D%BE/Desktop/%E6%9C%9F%E6%9C%AB%E8%80%83%E8%AF%95/digital-circuit/notes/img/8-22.png)

### 可编程逻辑开发简介

![](./)