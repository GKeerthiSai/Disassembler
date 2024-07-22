#Code to finf the type of bits 
.data
.dword 0x00000000FCD18613

.text
lui x3, 0x10000
ld x4,0(x3)
andi x2, x4, 127

#R-type
addi x20,x0,51 #R
beq x20,x2,L1
#I-type
addi x20,x0,19 #I1
beq x20,x2,L2
addi x20,x0,3  #I2
beq x20,x2,L2
addi x20,x0,103 #I3
beq x20,x2,L2
addi x20,x0,115 #I4
beq x20,x2,L2
#B-type
addi x20,x0,99  #B
beq x20,x2,L3
#S-type
addi x20,x0,35  #S
beq x20,x2,L4
#J-type
addi x20,x0,111  #J
beq x20,x2,L5
#U-type
addi x20,x0,55  #U1
beq x20,x2,L6
addi x20,x0,23  #U2
beq x20,x2,L6


#Loops
L1: addi x10,x0,1
    beq x0,x0,Exit
    
L2: addi x10,x0,2
    beq x0,x0,Exit
    
L3: addi x10,x0,3
    beq x0,x0,Exit
    
L4: addi x10,x0,4
    beq x0,x0,Exit
    
L5: addi x10,x0,5
    beq x0,x0,Exit
    
L6: addi x19,x0,6
    beq x0,x0,Exit

Exit: 
      add x0,x0,x0