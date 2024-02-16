
##  Branching Logic

label; goto; if-goto

label
- (LABEL) in assembly code

goto
- Go to label

if-goto
- pop topmost element from the stack
- if its not equal to zero, jump

## Function Calling

call; function; return

We first call "call fact(4)"
Then when the function finishes we call "return"

call f n
- Push return-address
- Push LCL, ARG, THIS, THAT
- Reposition ARG = SP-n-5 (number of args)
- LCL = SP; reposition LCL
- goto f; transfer control

function f k
- Declare a label for the function entry (f)
- Repeate k time; save local k for each variable
- Initialize them all to 0

return
- Set FRAME=LCL (FRAME is a temp variable)
- RET = put the return address in a temp variable
- *ARG=pop() // reposition the return value for the caller
- SP = ARG+1 // restore sp of the caller
- THAT = *(FRAME-1)
- THIS = *(FRAME-2)
- ARG = *(FRAME-3)
- LCL = *(FRAME-4)
- goto RET // go to return-address (in the caller's code)

