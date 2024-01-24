// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen
// by writing 'black' in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen by writing
// 'white' in every pixel;
// the screen should remain fully clear as long as no key is pressed.

(RESTART)
@SCREEN
D=A
@0
M=D

/////////////////////
(INFINITE_LOOP)
@KBD            // A-instruction to set address to keyboard input
D=M             // D-register now holds the keyboard input value
@BLACKEN_SCREEN
D;JGT // Jump if any keyboard key is pressed
@WHITEN_SCREEN
D;JEQ // Else, whiten the screen

@INFINITE_LOOP
0;JMP

/////////////////////
(BLACKEN_SCREEN)
// Your code to set the screen pixels to black (all 1s)
@1
M=-1 // Setting screen to black where -1 = 1111...

@UPDATE
0;JMP

(WHITEN_SCREEN)
@1
M=0 // Setting screen to white where 0 = 0...

@UPDATE
0;JMP


/////////////////////
(UPDATE) // Updates all the screen pixels to the value in M
@1
D=M

@0
A=M
M=D

@0
D=M+1 // Next pixel

@KBD
D=A-D // KBD - SCREEN = A

@0
M=M+1
A=M

@UPDATE
D;JGT // IF A=0 EXIT

@RESTART
0;JMP
