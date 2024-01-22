// Add 1+...100.
// C language
// Adds 1+...+100.
//   int i = 1;
//   int sum = 0;
//   While (i <= 100){
//          sum += i;
//          i++; }

@i
M=1

@sum
M=0

(LOOP)
    @i // d = i
    D=M

    @100 // d = i-100
    D=D-A

    @END
    D;JGT // if (i-100) > 0 goto END

    @i
    D=M    // D=i

    @sum
    M=D+M  // sum=sum+i

    @i
    M=M+1  // i=i+1

    @LOOP
    0;JMP  // Goto LOOP

(END)
    @END
    0;JMP  // Infinite loop

