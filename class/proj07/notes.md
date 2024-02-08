
# Tasks
- Review one from stack and two from stack logic
- Try out building the arithmetic module
- Try making each set of commands variables so they can be used across the entire program

**References**:
https://github.com/dvirberlo/nand2tetris_project/blob/main/07/VMtranslator.py
https://github.com/pcjun97/nand2tetris/tree/main/VMTranslator

# Memory Segments

pop (memory segment) (index)
push (memory segment) (index)

Where memory segment is one of the following:
- local
- argument
- this
- that
- constant
- static
- pointer

static, constant, temp, pointer: these are all global segments. They can be accessed from any function.

local, argument, this, that: these are local segments. They can only be accessed from the function they are in.

We need to represent all of the above in the same single physical address space, the host RAM.

To do this, we divide the Host RAM into seperate segments for each range of memories.
- The stack ranges from 256 to 2047.
- Static ranges from 16 to 255.
- local, argument, this, that: are mapped somewhere from address 2048 onwards. In an area called the heap.
Access to them is implemented by RAM[segment_base + index].
- consant: a virtual segment. Access to constant i is implemented by the constant i.

# Assembly Notes

## Memory Access

// D = 17
@17
D=A

// RAM[100] = 17
@17
D=A
@100
M=D

## Branching

// goto 29
@29
0;JMP


# Notes 

E.g., push local 2 needs to be translated to Hack assembly.
We're recommended to draw a trace table that records
the values of, say SP and LCL and init these vars
to arbitrary memory addresses.

Then we track on paper the assembly code we think
realizes it. Does the code impact the stack and the local segements correctly?
Did we use the tack pointer? And so on.

```hack
push local 2
```

```assembly


```
