// Multiply from 1 to N
// N = value in register
//
//   int i = R1
//   int n = R0
//   int sum = 0; // r2
//   While (i <= n){
//          sum += i;
//          i++; }


// Initialize sum to 0
@R2
D=0

// Copy R1 to R3
@R1
D=M

@R3
M=D

(LOOP)

    @R3 // d = i
    D=M

    @END
    D;JEQ // if i-N > 0 go to end

    // Add RO to R2
    
    @R0
    D=M
    
    @R2
    M=D+M  // sum=sum+i
    
    @R3
    M=M-1  // i=i-1
    
    @LOOP
    0;JMP  // Goto LOOP

(END)
    @END
    0;JMP  // Infinite loop

