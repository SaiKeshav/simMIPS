#Registers and the variables they represent
#R1 'n'
#R2 'fact'
#R3 'i'
#R0 is always 0(like in MIPS)
load R1,0(R0);                 #'n' is present in first location of memory
add R0,I1,R2;                  #'fact = 1'
add R0,I2,R3;                  #'i=2'
Loop : bgt R3,R1,Exit;         #if 'i>n' then Exit the loop
mul R2,R3,R2;                  #'fact=fact*i'
add R3,I1,R3;                  #'i=i+1'
jump Loop;                     #Iterate again
Exit : store R2,0(R0);         #The result is stored in first location of memory
 
