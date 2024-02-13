#include "Validation.h"


static operations op[16]={{"mov",0,0,2},{"cmp",1,0,2},{"add",2,10,2},{"sub",2,11,2},{"lea",4,0,2},{"clr",5,10,1},{"not",5,11,1}
,{"inc",5,12,1},{"dec",5,13,1},{"jmp",9,10,1},{"bne",9,11,1},{"jsr",12,2,1},{"red",12,0,1},{"prn",13,0,1},{"rts",14,0,0},{"stop",15,0,0}};

 static registers reg[16]={{"r0",0},{"r1",1},{"r2",2},{"r3",3},{"r4",4},{"r5",5},{"r6",6},{"r7",7},{"r8",8},{"r9",9},{"r10",10},{"r11",11}
,{"r12",12},{"r13",13},{"r14",14},{"r15",15}};
 

/**validate label name and length according to project requirements.
 * will print error in the following cases : 
 * label name is register/instruction name,label length more than 31,fist char of name is not a letter,label name already exist.*/
int validateLabel(char *label,int lineCounter)
{
	int i;
    if(strlen(label) > MAX_LABEL_LENGTH)
    {
        addError(lineCounter,"invalid label length - more them 31 characters");
        return -1;
    }  
    if(!isalpha(label[0]))
    {
        addError(lineCounter,"invalid label name - first character should be a letter");
        return -1;
    }
    if(searchSymbolList(label)==-1)
    {
        addError(lineCounter,"invalid label name - label name already exist");
        return -1;
    }
    for(i=0;i<16;i++)
	{
		if(strcmp(label,op[i].str)==0)
		{
			addError(lineCounter,"invalid label name - label name cant be named as an operation");
			return -1;		
		}	
		if(strcmp(label,reg[i].str)==0)
		{
			addError(lineCounter,"invalid label name - label name cant be named as a register");
			return -1;		
		}
	}	
    return 0;
}

	
/**validate each line according to the instruction,addressing methon and the given operands:
 * checks if instruction recives the exact number of operand it should (according to page 34 in project)
 * chacks if operands fit the addressing method
 * checks if numaric operan is a num */ 
int validateCommand(char *s1,int index,int amO,int numO,int regO,int amD,int numD,int regD,int lineCounter)
{
	char *token;
	
	if(amO==4)
		amO=0;
	if(amD==4)
		amD=0;
	/*checking op +2 operand*/
	if(op[index].numOfOperands==2)
	{
		if(strcmp(op[index].str,"lea")==0)
		{
    		if(amO !=1 &&amO !=2)
		    {
            	addErrorAM(lineCounter,amO,op[index].str);
                return -1;
		    }            
		    if(amD ==0)
            {  
                addErrorAM(lineCounter,amD,op[index].str);
                return -1;
            }    
		}
        if(strcmp(op[index].str,"cmp")!=0)
        {
		
            if(amD==0)
            {
                addErrorAM(lineCounter,amD,op[index].str);
                return -1;
            }
        }
        token=strtok(s1,",");
	
        if(token ==NULL)
        {
            addErrorO(lineCounter,"more",op[index].str);
            return -1;
        }
        else
        {
            token=strtok(NULL,"\n\t");
            if(token ==NULL)
            {
                addErrorO(lineCounter,"more",op[index].str);
                return -1;
            } 
	    }
    }
    if(op[index].numOfOperands==1)
    {
        if(amO!=0)
        {
            addErrorD(lineCounter,op[index].str);
            return -1;
        }
        if(op[index].opcode == 9)
        {
            if(amD==0 ||amD==3)
            {
                addErrorAM(lineCounter,amD,op[index].str);
                return -1;
            } 
        }
        else if(op[index].opcode != 13)
        {
            if(amD==0)
            {
                addErrorAM(lineCounter,amD,op[index].str);
                return -1;
            }
        }
	
        if(s1!=NULL) token=strtok(s1," \n\t");

        if(token ==NULL)
        {
            addErrorO(lineCounter,"more",op[index].str);
            return -1;
        }
        else
        {
            token=strtok(NULL," ""\n\t");
            if(token !=NULL)
            {	
                addErrorO(lineCounter,"less",op[index].str);
                return -1;
            }
        }        
	
    }
    if(op[index].numOfOperands==0)
    {
	
        if(s1!=NULL) token=strtok(s1," ""\n\t");
	    if(token !=NULL) 
        	{
            token=strtok(NULL," ""\n\t");
            if(token !=NULL)
            {
                addErrorO(lineCounter,NULL,op[index].str);
                return -1;
            }
        }     
    }
    if((amO==3 ||amO==2) && validateReg(regO) ==-1)
    {
        addErrorR(lineCounter);
        return -1;
    }
    if((amD==3||amD==2) && validateReg(regD)==-1)
    {
        addErrorR(lineCounter);
        return -1;
    }
    if(numO<INT_MIN)
    {
        addErrorN(lineCounter,"Origin");
        return -1;
    } 
   if(numD>INT_MAX)
    {
        addErrorN(lineCounter,"Destonation");
        return -1;
    }
    return 0;   
}


/*check is the given register number is one of the 16 defined registers*/
int validateReg(int regNum)
{
	 int i=0;

    for(i=0;i<=15;i++)
    {
        if(reg[i].num==regNum)
            	return 1; 
    }
    return -1;

}
