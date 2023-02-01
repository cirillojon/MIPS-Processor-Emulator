//Jonathan cirillo
//CDA/3101 - Sarah Angell 
//MySPIM project
//4/19/2021           
          
#include "spimcore.h"
#include <stdio.h>

/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{
    switch(ALUControl)
    {
        //Addition
        case 0:
            *ALUresult = A + B;
            break;

        //Subtraction  
        case 1:
            *ALUresult = A - B;
            break;

        //Less than
        case 2:
            if( A < B)
            {
                *ALUresult = 1;
            }
                
            else
            {
                 *ALUresult = 0;
            }
               
       //Unsigned less than
        case 3:
            if(A < B)
            {
                *ALUresult = 1;
            }
                
            else
            {
                 *ALUresult = 0;
            }
               
            break;
        
        //And
        case 4:
            *ALUresult = A & B;
            break;

        //Or
        case 5:
            *ALUresult = A | B;
            break;

        //Shift left 16 bits
        case 6:
            *ALUresult = B << 16;   
            break;

        //NOR
        case 7:
            *ALUresult = ~A;
            break;
    }
    
   
    //IF 0, set to 1; otherwise set to 0
    if(*ALUresult == 0)
    {
        *Zero = 1;
    }
        
    else
    {
        *Zero = 0;
    }
        
}

/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction) {
    
    //Check to to see if instructions are word-aligned, returns 1 if not
	if( PC % 4 != 0 )
    {
        return 1;
      
    } 					

	if( PC % 4 == 0 )
    {
        //Fetches the instructions addressed by PC from Mem 
        //and writea to instruction
        *instruction = Mem[PC >> 2];		
    }								
		
	return 0;
}


/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, 
unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec) 
{
    //31-26
	*op	= (instruction >> 26) & 0x3F;	
    //25-21
	*r1 = (instruction >> 21) & 0x1F;
    //20-16
	*r2	= (instruction >> 16) & 0x1F;	
    //15-11
	*r3 = (instruction >> 11) & 0x1F;
    //5-0
	*funct = instruction & 0x3F;		
    //15-0
	*offset = instruction & 0xFFFF; 
    //0-25
	*jsec = instruction & 0x3FFFFFF;	
   
}


/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{

    //Decodes instructions using opcode
	switch(op){
            
        //R-Type Instruction
		case 0x0: 
		 	controls->RegDst = 1;
            controls->Jump = 0;
            controls->Branch = 0;
            controls->MemRead = 0;
            controls->MemtoReg = 0;
            controls->ALUOp = 7;
            controls->MemWrite = 0;
            controls->ALUSrc = 0;
            controls->RegWrite = 1;
			break;

        //addi
		case 0x8: 
			controls->RegDst=0;			
			controls->Jump=0;			
			controls->Branch=0;			
			controls->MemRead=0;	
			controls->MemtoReg=0;		
			controls->ALUOp=0;			
			controls->MemWrite=0;	
			controls->ALUSrc=1;			
			controls->RegWrite=1;		
			break;
        //lw
		case 0x23: 
			controls->RegDst = 0;
            controls->Jump = 0;
            controls->Branch = 0;
            controls->MemRead = 1;
            controls->MemtoReg = 1;
            controls->ALUOp = 0;
            controls->MemWrite = 0;
            controls->ALUSrc = 1;
            controls->RegWrite = 1;
			break;

        //sw
		case 0x2b:
			controls->RegDst = 2;
            controls->Jump = 0;
            controls->Branch = 0;
            controls->MemRead = 0;
            controls->MemtoReg = 2;
            controls->ALUOp = 0;
            controls->MemWrite = 1;
            controls->ALUSrc = 1;
            controls->RegWrite = 0;
            break;
        
        //lui
		case 0xf:  
			controls->RegDst=0;			
			controls->Jump=0;			
			controls->Branch=0;			
			controls->MemRead=0;		
			controls->MemtoReg=0;		
			controls->ALUOp=6;			
			controls->MemWrite=0;		
			controls->ALUSrc=1;			
			controls->RegWrite=1;		
			break;

        //beq 
		case 0x4:  
			controls->RegDst = 2;
            controls->Jump = 0;
            controls->Branch = 1;
            controls->MemRead = 0;
            controls->MemtoReg = 2;
            controls->ALUOp = 1;
            controls->MemWrite = 0;
            controls->ALUSrc = 2;
            controls->RegWrite = 0;
			break;
        
        //slti
		case 0xa: 
			controls->RegDst = 0;
            controls->Jump = 0;
            controls->Branch = 0;
            controls->MemRead = 0;
            controls->MemtoReg = 0;
            controls->ALUOp = 2;
            controls->MemWrite = 0;
            controls->ALUSrc = 1;
            controls->RegWrite = 1;
			break;
            
        //sltiu
		case 0xb:  
			controls->RegDst=0;			
			controls->Jump=0;
			controls->Branch=0; 
			controls->MemRead=0; 
			controls->MemtoReg=0;
			controls->ALUOp=3;
			controls->MemWrite=0; 
			controls->ALUSrc=1;
			controls->RegWrite=1;
			break;
        
        //jump
		case 0x2:  
			controls->RegDst = 2;
            controls->Jump = 1;
            controls->Branch = 2;
            controls->MemRead = 2;
            controls->MemtoReg = 2;
            controls->ALUOp = 0;
            controls->MemWrite = 0;
            controls->ALUSrc = 2;
            controls->RegWrite = 0;
            break;
            
		default:
		return 1;
	}
    
	return 0;
}
/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2) 
{
    //Read the registers addressed by r1 and r2 from Reg, and write the read values
    //to data1 and data2 respectively.
	*data1 = Reg[r1];	
	*data2 = Reg[r2];	
}

/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{
 //Assigns the sign-extended value of offset to extended_value.
  
  //Checks if 16th bit is 1 (meaning offset is negative and needs to be sign extended)
   if((offset >> 15) == 1) 						
		*extended_value = offset | 0xffff0000;		

	if((offset >> 15) == 0) 	
    {
       *extended_value = offset & 0x0000ffff;
    }
		
}
/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,
char ALUSrc,unsigned *ALUresult,char *Zero)
{

    //Apply ALU operations on data1, and data2 or extended_value (determined byALUSrc).

   unsigned ALUnum = ALUOp;

   int haltCode = 0;


//Operations 0 - 6
if((ALUnum < 7 ) ) 
{
    if(ALUSrc==1)
    data2 = extended_value;

	ALU(data1, data2, ALUnum, ALUresult, Zero);
    return 0;
}

    //R-type
    if(ALUSrc == 0)
    {
        switch (funct) {
            //Addition
            case 32: 
                ALUnum = 0;
                break;
            //Subtraction
            case 34: 
                ALUnum = 1;
                break;
            //And
            case 36: 
                ALUnum = 4;
                break;
            //Or
            case 37:	
				ALUnum = 5;
                break;
            //NOR
            case 39: 
			    ALUnum = 7;
			    break;

            //slt
            case 42: 
                ALUnum = 2;
                break;

            //sltu
            case 43:
                ALUnum = 3;
                break;

            default: 
            {
                haltCode = 1;
                break; 
            }
          
        }
        
        ALU(data1, data2, ALUnum, ALUresult, Zero);
    }
    
    return haltCode;
}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{

//Based on the value of MemWrite or MemRead, determines memory write operation or memory read operation.
//Reads the contents of the memory location addressed by ALUresult to memdata.
//Writes the value of data2 to the memory location addressed by ALUresult.

//Returns 1 if halt condition occurs

	if (MemRead == 1)
	{
        if(ALUresult < 0 || ALUresult % 4 != 0)
        {
            return 1;
        }
        else
        {
            *memdata = Mem[ALUresult >> 2];	    
        }
		
	}
    
	if (MemWrite == 1)
	{
         if(ALUresult < 0 || ALUresult % 4 != 0)
        {
            return 1;
        }
        else
        {
            Mem[ALUresult >> 2] = data2;
        }   
	
	}
	
	return 0;
    
}

/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,
char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{
    
    //Writes the data (ALUresult or memdata) to a register (Reg) addressed by r2 or r3.

    if (RegWrite == 1 )
     {

          if (MemtoReg == 0)
           {
            if (RegDst == 1)
            {
                Reg [r3] = ALUresult; 
            }
                
            else    
            {
                Reg [r2] = ALUresult; 
            }
                
             }
        if (MemtoReg == 1) 
        {
            if (RegDst == 1) 
            {
                Reg[r3] = memdata; 
            }
                
            else 
            {
                Reg[r2] = memdata; 
            }       
        }
    }
}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{
    //Updates the program counter (PC)

    *PC = *PC + 4;

	if (Branch == 1 && Zero == 1)
    {
	    *PC += (extended_value << 2);
	}

	if(Jump == 1) 
    {
		*PC = (jsec << 2) | (*PC & 0xf0000000);
	}

}