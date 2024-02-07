
# Tasks

- Figure out how to represent the RAM; either as a stack or with memory cell structs.
- Figure out the difference between loca, this, that, and argument.
- Figure out how to translate the VM code to assembly instructions.

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
