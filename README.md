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

## Usage

To run the simulator, follow these steps:

1. Ensure that you have the necessary input file. The input file should contain hexadecimal values, each representing a machine instruction in the MIPS instruction set. Each instruction should be on a new line.

2. Run the simulator using the following command:

```bash
./simulator <input_file> [-r]

Where `./simulator` is the executable built from this code, `<input_file>` is the name of the input file described in step 1, and `[-r]` is an optional argument that redirects all output to stdout, instead of the default behavior which is to output to the console.

Upon running the simulator, you will be presented with a command prompt. The following commands are supported:

- `'g' or 'G'`: Display the control signals.
- `'r' or 'R'`: Dump the register file.
- `'m' or 'M'`: Dump the contents of memory. If followed by two space-separated numbers, it dumps the memory contents between those two addresses.
- `'s' or 'S'`: Step the simulator forward by n steps, where n is an optional argument. If no argument is given, n defaults to 1.
- `'c' or 'C'`: Run the simulator continuously until it halts.
- `'h' or 'H'`: Display the halt flag.
- `'p' or 'P'`: Dump the instruction memory.
- `'i' or 'I'`: Display the size of the memory.
- `'d' or 'D'`: Dump the contents of memory between two hexadecimal addresses.
- `'x' or 'X'` or `'q' or 'Q'`: Quit the simulator.
