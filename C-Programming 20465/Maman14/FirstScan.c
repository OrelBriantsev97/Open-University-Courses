#include "FirstScan.h"


static operations op[16]={{"mov",0,0,2},{"cmp",1,0,2},{"add",2,10,2},{"sub",2,11,2},{"lea",4,0,2},{"clr",5,10,1},{"not",5,11,1}
,{"inc",5,12,1},{"dec",5,13,1},{"jmp",9,10,1},{"bne",9,11,1},{"jsr",12,2,1},{"red",12,0,1},{"prn",13,0,1},{"rts",14,0,0},{"stop",15,0,0}};

/*first scan method process each line according to the label and line kind:
.data,.string and instruction lines are proccesed in addData/addStringLine and anylyze command functions.
comment and entry lines are being skipped.
labels sent createSymbol function.*/
void firstScan(int *dcT,int *IC,int *DC,FILE *f2,FILE *object,int *error,int *externals,int *entries)
{
    char buff[MAX_LINE_LENGTH];
    char *label=NULL;
    char *token=NULL;
    int lineCounter=0;
    char colon[]=":";
    int instruction=0;
    char *attribute=NULL;
    char *code="code";
    int index=0;
    int dcTotal=0;


    rewind(f2);
    while (fgets(buff,MAX_LINE_LENGTH, f2)!=NULL)
    {
        lineCounter++;
        if(strlen(buff)==1) /**if line empty and contains only white spaces-> ignore*/
            continue;
        token=strtok(buff," ""\n\t");
        /*if line is a comment line or contains only white spaces->ignore*/
        if(isComment(token))
            continue; 
	    if(strstr(buff,colon))
	    {
	    	if(isLabel(token)==1)
	    	{
			/*if label detected - saves it in label variable*/
		    label=getLabel(token,lineCounter);
		    token=strtok(NULL," ""\n\t");
	    	}
		    else
		    {
		    addError(lineCounter,"invalid label declaration - colon should appear in the end of label name with no space between them");
			label=NULL;		    
			(*error)=1;
		    }
	    }
	    else label=NULL; 
        /*if label is not decleared correctly*/   
        if(token ==NULL)
            continue;
        /*checks if .data/.string line*/
 	    instruction=isStorageInstruction(token);
        if(instruction!=0)/*if line contains data storage instruction*/
	    {
		    attribute=(char*) malloc(sizeof(char)*4);
		    strcpy(attribute,code);
            if(label != NULL && validateLabel(label,lineCounter)!=-1)
			    createSymbol(label,DC,IC,attribute);
		    token=strtok(NULL," ""\n\t");
    	    fprintf(object,"%d\t",(*IC));
            if(instruction == 1)
                addDataLine(token,DC,IC,object,lineCounter,error,&dcTotal);
            if(instruction == 2)
                addStringLine(token,DC,IC,object,lineCounter,&dcTotal);
	    }
	    else if(isEntry(token))
		{
		  (*entries)++;
		    continue;   
		}
	    else if(isExtern(token))
        {/*adding label to symbol list as extern label*/
		    (*externals)++;
            token=strtok(NULL," ""\n\t");
		    if(token != NULL && validateLabel(token,lineCounter)!=-1)
			    createSymbol(token,DC,IC,"external");
	    }
   	    else
        {/*instruction line that is not entry or extern*/
            if(label != NULL && validateLabel(label,lineCounter)!=-1)
      		createSymbol(label,DC,IC,"code");
            index=searchOp(token);    
            if(index==-1)
            {
              	addError(lineCounter,"invalid command");
       	     	(*error)=1;
		        continue;
            }
       	    if(index !=14 && index!=15)
		        token=strtok(NULL," ""\n");
		    fprintf(object,"%d   ",(*IC));
        	analyzeCommand(index,IC,token,label,lineCounter,object,error);
	    }
	    label=NULL;
	}
 	(*dcT)=dcTotal;
}


/**checking each instruction line and finds the following information:
 * number of empty lines that need to be added for the second scan
 * addressing method (AM) for every operand.
 * for AM 2 and 3 - finds the register number
 * for AM 0 - find the number that's after the # char.
 * then,validating each line and adding empty line if needed*/
void analyzeCommand(int index,int *IC ,char *line,char *label,int lineCounter,FILE *object,int *error)
{
    char *token;
    int amOrigin=0;
    int amDest=0;
    int regOrigin=-1;
    int regDest=-1;
    int linesOrigin=0;
    int linesDest=0;
    int numOrigin=0;
    int numDest=0;
    int vc=0;
    int ARE=4;
    int temp_IC=(*IC);
    int i;
    char *labelOperandO=NULL;
    char *labelOperandD=NULL;
 
	char *s1=(char *)malloc(strlen(line));
	if(line!=NULL) strcpy(s1,line);

    token=strtok(line,",""\n\t");
    if(op[index].numOfOperands!=0)
    {
        /*instructions that receives one operand*/
        if(op[index].numOfOperands==1)
        {
            if(token != NULL)
            amDest=findAM(token,&regDest,&linesDest,&numDest);
		
		    if(amDest ==2 ||amDest==1)
		    {   /*if one of the operands is a label - keep the name*/ 
           	    labelOperandD=(char *)malloc(strlen(token)+1);
		        strcpy(labelOperandD,token);
		    }
        }
        /*instructions that receives two operand*/
        else if(op[index].numOfOperands==2)
        {
		    if(token!=NULL) 
                amOrigin=findAM(token,&regOrigin,&linesOrigin,&numOrigin);
            if(amOrigin==2||amOrigin==1)
		    {/*if one of the operands is a label - keep the name*/
		        labelOperandO=(char *)malloc(strlen(token)+1);
		        strcpy(labelOperandO,token);	
		    }
		    token=strtok(NULL, "\n\t");
            if (token!=NULL) 
                amDest=findAM(token,&regDest ,&linesDest,&numDest);
            if(amDest==2 ||amDest==1)
		    {/*if one of the operands is a label - keep the name*/
             	labelOperandD=(char *)malloc(strlen(token)+1);
			    strcpy(labelOperandD,token);
		    }            
	        
        }
        vc=validateCommand(s1,index,amOrigin,numOrigin,regOrigin,amDest,numDest,regDest,lineCounter);
        if(vc==-1)/*if errors found in the instruction line - skip */
	    {
		    (*error)=1;
            return;
        }
        processFirstWord(index,&temp_IC,object);
        if(regOrigin ==-1)
            regOrigin=0;
	    if(regDest ==-1) 
            regDest=0;
        /* for AM 1,2,3*/
        if(amOrigin!=4 && amDest!=4)
            processSecondWord(index,amOrigin,regOrigin,numOrigin,amDest,regDest,numDest,ARE,&temp_IC,object);
        if(amOrigin==4)
        {/*adding second word according to operation and AM*/
            processSecondWord(index,amOrigin,regOrigin,numOrigin,amDest,regDest,numDest,ARE,&temp_IC,object);
            linesOrigin--;
        }   
        if(amDest==4)
        {/*adding second word according to operation and AM*/
            processSecondWord(index,amOrigin,regOrigin,numOrigin,amDest,regDest,numDest,ARE,&temp_IC,object);
            linesDest--;
        }
        if(numOrigin!=0)
        {
            fprintf(object,"%d         ",temp_IC);
            addNewWord(numOrigin,4,&temp_IC,object);
        }
	    if(linesOrigin !=0)
	    { /*keeps line number of the empty lines*/
		    addLabelAddress(temp_IC,labelOperandO);
            for(i=1;i<=linesOrigin;i++)
	        {/*adding empty lines for the label base and offset addresses*/
	           processSecondWord(0,0,0,0,0,0,0,0,&temp_IC,object);
	        }     
        }  
	    if(numDest!=0)
        {
            fprintf(object,"%d         ",temp_IC);
            addNewWord(numDest,4,&temp_IC,object);
        }
        if(linesDest!=0)
        {/*keeps line number of the empty lines*/
            addLabelAddress(temp_IC,labelOperandD);
            for(i=1;i<=linesDest;i++)
            {/*adding empty lines for the label base and offset addresses*/
                processSecondWord(0,0,0,0,0,0,0,0,&temp_IC,object);
            }
        }      
    }
    else /*for instructions stop and rts */
	{
        vc=validateCommand(s1,index,amOrigin,numOrigin,regOrigin,amDest,numDest,regDest,lineCounter);
        if(vc==-1)
        {
            (*error)=1;
            return;
        }
        processFirstWord(index,&temp_IC,object);
    }
    (*IC)=temp_IC;
}


/*creating firstline object with instuction op code and send to binaryline for printing*/
void processFirstWord(int index,int *IC,FILE *object)
{
    unsigned int *firstwordp;
    int tempIC=(*IC);
    firstLine.ARE=4;
    /*turning on the n'th bit in the opcode*/
    firstLine.opcode=(1 << op[index].opcode);
    firstwordp=(unsigned int *) &firstLine;	
	binaryLine(*firstwordp,&tempIC,object);
    (*IC)=tempIC;
}

/*creating secondLine object with origin and destination AM,registers and numaric operand*/
void processSecondWord(int index,int amO,int regO,int numO,int amD,int regD,int numD,int ARE,int *IC,FILE *object)
{
    unsigned int *secondwordp=0;
    int tempIC=(*IC);
	/*adding the secondLine values*/
    secondLine.amDest=amD;
    secondLine.regDest=regD;
    secondLine.amOrign=amO;
    secondLine.regOrigin=regO;
    secondLine.funct=op[index].funct;
    secondLine.ARE=ARE;
    secondwordp=(unsigned int *) &secondLine;
	
    fprintf(object,"%d         ",tempIC);
	binaryLine(*secondwordp,&tempIC,object);
    (*IC)=tempIC;
}
