# README

## Overview

This code is a simple model of the MIPS Instruction Set Architecture (ISA) implemented in C. This program simulates the execution of a MIPS binary program, providing operations of a MIPS CPU including fetch, decode, and execution of instructions, memory reads/writes, and register reads/writes.

## Key Features

1. Memory and Register Definitions: The program defines memory (`Mem`) of size `MEMSIZE` and a register file (`Reg`) of size `REGSIZE + 4`. Various registers including program counter (`PC`), status register, and special registers `LO` and `HI` are defined for operations.

2. Initialization: The `Init` function initializes registers to their starting values.

3. Instruction Fetch, Decode, and Execution: The `Step` function performs one step in the execution of the program, which includes instruction fetch, decode, reading registers, sign extension, ALU operations, memory read/write, register write, and updating the program counter. If any step fails, the execution halts.

4. Memory Dump: The `DumpMem`, `DumpMemHex` and `DumpHex` functions provide ways to inspect the contents of the memory in different formats (decimal and hexadecimal).

5. Register Dump: The `DumpReg` function allows you to see the current state of all registers.

6. Command Loop: The `Loop` function provides a command-line interface for controlling the execution of the program, including stepping through execution, viewing register and memory state, and other operations.

7. File Reading: In the `main` function, an input file is read into memory, which is expected to contain MIPS instructions. The file reading process also handles error checking and reporting.
