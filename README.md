# simMIPS
Simulates the MIPS Processor

The end goal is to simulate the MIPS Processor

But presently implements a simple non-pipelined version of the MIPS Processor including execution of very basic instructions sufficient to run a factorial prgram on it.

The assembler is implemented takes input the assembly instructions and produces 
the binary code. This has been done using regular expressions in c++ making it very flexible to accept
any instruction set and produce the corresponding binary output. The exact way to do this is in the code 
but a more detailed documentation is being developed.

The program takes Factorial.asm as input and using the pseudoMIPS.dict encodes every instruction and gives the output Factorial.bin. The pseudoMIPS.dict contains the regular expressions corresponding to the actual instructions which will be uploaded soon. 

For the non-pipelined simulator, another input is the name of memory file where each line in the file is treated as a memory location.
