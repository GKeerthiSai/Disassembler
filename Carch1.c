#include<stdio.h>
#include<stdlib.h>                          // addi, andi, ori, xori, slli, srli, srai, ld, lw, lh, lb, lwu, lhu, lbu, beq, bne, blt, bge, bltu, bgeu
#include<stdint.h>
#include<stdbool.h>
void Rfunction( uint32_t input);
void Ifunction( uint32_t input);
void Sfunction( uint32_t input);
void Ufunction(uint32_t input);  
void Bfunction(uint32_t input ,int* labelcount ,uint32_t addr );
void Jfunction( uint32_t input , int* labelcounter , uint32_t addr);

void Rfunction( uint32_t input){ 
 uint32_t opcode = (input & 0x7F);
 uint32_t rd = (input >> 7 ) & 0x1F;       //as opcode takes 7 bits and rd requires 5 bits so 1F(11111)
 uint32_t funct3 = (input >> 12 ) & 0x7;   // as funct3is after 12 bits from left and takes 3 bits as 7(0111)
 uint32_t rs1 = (input >> 15 ) & 0x1F;
 uint32_t rs2 = (input >> 20 ) & 0x1F;
 uint32_t funct7 = (input >> 25 ) & 0x7F;
   
 char* operation = NULL;
 switch (funct3) {
  
  case 0x0 : switch (funct7) {
                case 0x00:
                    operation = "add";
                    break;
                case 0x20:
                    operation = "sub";
                    break;
                default:
                    printf("Invalid funct7 for funct3=0\n");
                    break;
            }
            break;          
  case 0x1 : if(funct7 ==0x0 ){
             operation = "sll";
             }
             break;
  case 0x2 : if(funct7 ==0x0 ){
             operation = "slt";
             }
           break;
  case 0x3 : if(funct7 ==0x0 ){
             operation = "sltu";
             } 
           break;
  case 0x4 : if(funct7 ==0x0 ){
             operation = "xor";
             }
           break;
  case 0x5 : switch (funct7){
            case 0x0 :
                    operation = "srl";
                     break;
            case 0x20 : 
                    operation = "sra";         
                      break;
            }          
           break; 
  case 0x6 : if(funct7 ==0x0 ){
             operation = "or";
             }
           break;
  case 0x7 : if(funct7 ==0x0 ){
             operation = "and";
             }
           break;
  
  default : printf("NO operation matching!! \n");
            break;
 }           
 if(operation!=NULL){
  printf("%s x%d, x%d x%d\n", operation, rd, rs1,rs2);
 }           
     
}




void Ifunction(uint32_t input){
 uint32_t opcode = (input & 0x7F);
 uint32_t rd = (input >> 7 ) & 0x1F;       
 uint32_t funct3 = (input >> 12 ) & 0x7;   
 uint32_t rs1 = (input >> 15 ) & 0x1F;
 uint32_t immediate =(int32_t) (input >> 20 ) ;
  char* operation = NULL;
  
      if (opcode == 0x67) {
        operation = "jalr";
        if (operation != NULL) {
  printf("%s x%d, x%d,%d,\n", operation, rd, rs1, immediate);
    }
    }
if(opcode==0x13){ 
 switch(funct3){
 case 0 : operation = "addi";
          break;
 case 4 : operation = "xori";
          break;
 case 6 : operation = "ori";
          break;         
 case 7 : operation = "andi";
          break;
 case 2 : operation = "slti";
          break;
 case 3 : operation = "sltiu";
          break;          
 case 5 : if ((input >> 30) & 1) {
          operation = "srai";
          immediate |= 0xFFFFF000; // Sign-extend imm[11:0]
            } else {
             operation = "srli";
            }
            break;
 case 1 : if ((input >> 30) & 1) {
          operation = "slli";
          immediate |= 0xFFFFF000; // Sign-extend imm[11:0]
          }
 default : break;         
                                   
 }
 if (operation != NULL) {
  printf("%s x%d, x%d,%d\n", operation, rd, rs1, immediate);
 }
}else if (opcode == 3){
switch(funct3){
 case 0 : operation = "lb";
          break;
 case 1 : operation = "lh";
          break;
 case 2 : operation = "lw";
          break;         
 case 3 : operation = "ld";
          break;
 case 4 : operation = "lbu";
          break;
 case 5 : operation = "lhu";
          break; 
 case 6 : operation = "lwu";
          break; 
 default : break; 
}
if (operation != NULL) {
  printf("%s x%d, x%d(%d)\n", operation, rd, rs1, immediate);

 } 

}

 
}


void Sfunction(uint32_t input){
  uint32_t opcode = (input & 0x7F);
 //uint32_t imm1 = (input >> 7 ) & 0x1F;   
 uint32_t funct3 = (input >> 12 ) & 0x7; 
 uint32_t rs1 = (input >> 15 ) & 0x1F;
 uint32_t rs2 = (input >> 20 ) & 0x1F;
 //uint32_t imm2 = (input >> 25 ) & 0x7F;
 int32_t imm = ((input >> 25) << 5) | ((input >> 7) & 0x1F);
 
 char* operation = NULL;
 switch (funct3) {
  case 0x0 : operation = "sb";
             break;
  case 0x1 : operation = "sh";
             break;
  case 0x2 : operation = "sw";
             break;
  case 0x3 : operation = "sd";
             break;
  default : printf("No option matching!!\n");
            break;           
 }
 
if (operation != NULL) {
   printf("%s x%d, %d(x%d)\n", operation, rs2, imm, rs1);
 }
 
}



void Bfunction(uint32_t input, int* labelCounter ,uint32_t addr){
 uint32_t opcode = (input & 0x7F);
 //uint32_t imm1 = (input >> 7 ) & 0x1F;       //as opcode takes 7 bits and rd requires 5 bits so 1F(11111)
 uint32_t funct3 = (input >> 12 ) & 0x7;   // as funct3is after 12 bits from left and takes 3 bits as 7(0111)
 uint32_t rs1 = (input >> 15 ) & 0x1F;
 uint32_t rs2 = (input >> 20 ) & 0x1F;
     int32_t imm =
        ((input >> 31) << 12) | (((input >> 7) & 0x1) << 11) | (((input >> 25) & 0x3F) << 5) | (((input >> 8) & 0xF) << 1);
// uint32_t imm2 = (input >> 25 ) & 0x7F;
  
 char* operation = NULL;
  char label[16];
  
 switch (funct3) {
  
  case 0 : operation ="beq";         
           break;           
  case 1 : operation ="bne";
             break;
  case 4 : operation ="blt";
           break;
  case 5 : operation ="bge"; 
           break;
  case 6 : operation ="bltu";
           break;
  case 7: operation ="bgeu";
          break;

default : break;
}

    (*labelCounter)++;
    snprintf(label, sizeof(label), "L%d", *labelCounter);

    if (operation != NULL) {
        printf("%s x%d, x%d, %s\n", operation, rs1, rs2, label);
    }

}


void Ufunction(uint32_t input){
 uint32_t opcode = (input & 0x7F);   
 uint32_t rd = (input >> 7 ) & 0x1F;   
 uint32_t immediate = (input >> 12);
 char* operation = NULL; 
  if(opcode == 0x37){                      // 55 and 23  in decimal 37 and 17 in hex
   operation = "lui"; 
  } else if(opcode == 0x17){              // If we want to represent in it;s binary form them put 0x in front of any number otherwise compiler thinks it is a decimal number
   operation = "auipc";
  }
  
  printf("%s x%d, 0x%x\n",operation , rd, immediate);                      
 
}



void Jfunction(uint32_t input, int* labelcode, uint32_t addr) {
 uint32_t opcode = (input & 0x7F);  
 uint32_t rd = (input >> 7) & 0x1F;
 //uint32_t immediate = (input >> 12);
 int32_t immediate =((input >> 31) << 20) | (((input >> 21) & 0x3FF) << 1) | (((input >> 20) & 0x1) << 11) | (((input >> 12) & 0xFF) << 12);
 char* operation = NULL;
 char label[16];
switch (opcode){
 case 0x6F: operation = "jal";
            (*labelcode)++;
            snprintf(label, sizeof(label), "L%d", *labelcode);
            break;
 default:
         break;
}
if (operation != NULL) {
 printf("%s x%d, %s\n", operation, rd, label);
 }
}

 

int main(){
 //uint32_t                                                             //for guarenteed 32-bits
 uint32_t instructions[] = {0x007201b3,0x00720863,0x00c0006f,0x00533623,0x100004b7,0x00c50493};
int totalinputs= sizeof(instructions) / sizeof(instructions[0]);
 uint32_t address = 1000;
   bool T=true;
   int j=0;
      uint32_t PC[20] ;
 int label[20];
 for(int i=0;i<totalinputs;i++){
 uint32_t input = instructions[i];
 uint32_t opcode = (input & 0x7F); 
 
    PC[i]= address;
 
        if (opcode == 0x63 ) {
   int32_t imm=  ((input >> 31) << 12) | (((input >> 7) & 0x1) << 11) | (((input >> 25) & 0x3F) << 5) | (((input >> 8) & 0xF) << 1);

         for(int i=0;i<j;i++){
           if(label[i] == label[j]){
             T=false;
           }
         
         }
         if(T){
         label[j]=address+imm;
                  
         j+=1; 
        } }
       //j
if (opcode == 0x6F ) {
     int32_t imm =((input >> 31) << 20) | (((input >> 21) & 0x3FF) << 1) | (((input >> 20) & 0x1) << 11) | (((input >> 12) & 0xFF) << 12);

         for(int i=0;i<j;i++){
           if(label[i] == label[j]){
             T=false;
           }
         
         }
         if(T){
         label[j]=address+imm;
                  
         j+=1; 
        } }   
        
       address+=4; 
 }
 
 
for (int i = 0; i < totalinputs; i++) { //printf("0x%x: ", address);
 int labelcount = 0;
 uint32_t input = instructions[i];
 uint32_t opcode = (input & 0x7F);  
  
 int labelCounter = 0;
 // Check if the opcode requires a label
  for(int k=0;k< j;k++){
   if(PC[i]==label[k]){
    printf("L%d :",(k+1));
    break;}
  }
 
//Even opcode it visible as 55 or something compiler stores all values in binary format only to memory
 switch(opcode){
  case 0x33: Rfunction(input);                //compiler converts case labels to binary so we can use them in case labels. 
             break; 
 case 0x13: Ifunction(input);   
             break;
 case 0x3: Ifunction(input);   
             break;                      //1 R 
 case 0x23: Sfunction(input);            //4 I 
             break;                      //1 S
 case 0x63: Bfunction(input , &labelCounter , address );   
             break;                     // 1 B
 case 0x37: Ufunction(input);   
             break;                     // 2 U
 case 0x6F: Jfunction(input , &labelCounter , address );          //1 J
             break;                           
 default: printf("Please enter correct/valid instruction\n");
          break;
     
   }  address+=4; 
}   
 return 0;
}

                   
