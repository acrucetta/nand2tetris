## Overview
This folder contains the HDL (Hardware Description Language) files and test scripts for a series of logic chips. These implementations are part of a project to understand and build fundamental digital components. The chips are designed and tested in a specific order, starting from basic gates to more complex multiplexers and demultiplexers.

## Contents
The folder includes HDL files and their corresponding test scripts for each of the following chips:

1. **Not**: Implements a simple NOT gate.
2. **And**: Implements an AND gate.
3. **Or**: Implements an OR gate.
4. **Xor**: Implements an XOR gate.
5. **Not16**: A 16-bit NOT gate, operating on 16-bit inputs.
6. **And16**: A 16-bit AND gate, working with two 16-bit inputs.
7. **Or16**: A 16-bit OR gate, for two 16-bit inputs.
8. **Or8Way**: An 8-way OR gate, outputting true if any of the 8 inputs is true.
9. **Mux**: A basic multiplexer, selecting between two inputs based on a selector bit.
10. **DMux**: A basic demultiplexer, directing an input to one of two outputs based on a selector bit.
11. **Mux16**: A 16-bit multiplexer.
12. **Mux4Way16**: A 4-way 16-bit multiplexer, selecting one of 4 16-bit inputs.
13. **Mux8Way16**: An 8-way 16-bit multiplexer.
14. **DMux4Way**: A 4-way demultiplexer, directing a single input to one of four outputs.
15. **DMux8Way**: An 8-way demultiplexer.

Each HDL file defines the logic for the respective chip. The test scripts verify the correctness of the implementation against predefined test cases.

## How to Use
To use these HDL files, you will need a simulator that can run and test HDL scripts. Follow these steps for each chip:

1. Open the HDL file in your simulator.
2. Load the corresponding test script.
3. Run the test script to verify the implementation.
