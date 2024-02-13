#include "Utils.h"

static operations op[16]={{"mov",0,0,2},{"cmp",1,0,2},{"add",2,10,2},{"sub",2,11,2},{"lea",4,0,2},{"clr",5,10,1},{"not",5,11,1}
,{"inc",5,12,1},{"dec",5,13,1},{"jmp",9,10,1},{"bne",9,11,1},{"jsr",12,2,1},{"red",12,0,1},{"prn",13,0,1},{"rts",14,0,0},{"stop",15,0,0}};

 static registers reg[16]={{"r0",0},{"r1",1},{"r2",2},{"r3",3},{"r4",4},{"r5",5},{"r6",6},{"r7",7},{"r8",8},{"r9",9},{"r10",10},{"r11",11}
,{"r12",12},{"r13",13},{"r14",14},{"r15",15}};

static emptyLine *headL=NULL;

/*checks if the line is comment line according to the project requirments - if fisrt char is';' then comment line */
bool isComment(char *token)
{
    if(token[0] ==';')
        return true;
    return false;
}

/*checks if first token is a label according to project requirments - if char ':' found in the end of a word- then its label*/
int isLabel(char *token)
{
    int size=strlen(token);
    if(token[size-1] == ':')
		return 1;	
   return 0;
}

/* return label name without the char ":" in the end */
char * getLabel(char *token,int lineCounter)
{
    int size=strlen(token);
    token[size-1]='\0';
    return token;

}
/*removes spaces from a given string and returns it*/
char * removeSpaces(char * s) 
{
    int i,j=0;
    for(i=0;s[i];i++)
    {
     	s[i]=s[i+j];
     	if(s[i]==' '|| s[i]=='\t')
     	{
		  j++;
		  i--;
	    }
    }
    return s;
}

/**checks the .date lines commas.will print error in the foolowing cases:
 * comma before the fistr number,comma after the last number, misiing comma in between numbers,more than one commas in between numbers.*/
int countCommas(char *line,int lineCounter)
{
	int i;	
	int count=0;

	if(line[0]==',')
	{
		addError(lineCounter,"invalid Line - comma before number the first number");
		return -1;
	}
	if(line[strlen(line)-1]==',')
	{
		addError(lineCounter,"invalid Line - comma after the last number");
		return -1;
	}
	for(i=0;i<strlen(line);i++)
	{	
		if(line[i]==',')
			count++;
	}
	return count;
	
}	

/*check if the given token is equal to ".entry". if so, returns true*/
bool isEntry(char *token)
{
    char s1[]=".entry";
    char *s=malloc(strlen(token));
    s=removeSpaces(token);
    if(strcmp(s,s1)==0)
        return true;
   return false;
}
/*check if the given token is equal to ".extern". if so, returns true*/
bool isExtern(char *token)
{
    char s1[]=".extern";
    char *s=malloc(strlen(token));
    s=removeSpaces(token);
    if(strcmp(s,s1)==0)
        return true;
    return false;

}
/**checks if the given token is one of the 16 operation defined in the operations array.
 * if so, return the location in the array.else return -1*/
int searchOp(char *token)
{
    int i=0;
    for(i=0;i<=15;i++)
    {
        if(strcmp(op[i].str,token)==0)
            return i; 
    }
    return -1;
}

/**checks if the given token is one of the 16 registers defined in the operations array.
 * if so, return the register number.else return -1*/
int searchReg(char *token)
{
    int i=0;

    for(i=0;i<=15;i++)
    {
        if(strcmp(reg[i].str,token)==0)
            	return reg[i].num; 
    }
    return -1;
}
/* erasing the brackets from the third addresssing method operands and sends the register to searchreg function.*/
int findReg(char *line)
{
	int number=-1;	
	char *firstIndex=strchr(line,'[');
	firstIndex++;
	firstIndex[strlen(firstIndex)-1]='\0';
	number=searchReg(firstIndex);
	
	return number;

}
/*convert to binary and print in MemoryPicture file */ 
void binaryLine( int a,int *IC_t,FILE *object)
{
   int i;
	(*IC_t)++;
   for ( i = 19 ;i >= 0; i-- )
   {
	 if ( (a & (1<<i) ) != 0 )
	    fprintf(object,"%d",1);
	 else
	    fprintf(object,"%d",0);
   }
 	fprintf(object,"\n");
}
/*creating a newWord object with the given line and ARE and sends the object to binaryLine function */
void addNewWord(int line,int ARE,int *IC_T,FILE *object)
{

    int *p=0;
	int tempIC=(*IC_T);
    newWord.opcode=line;	
    newWord.ARE=ARE;	
	p=(int *) &newWord;	
	binaryLine(*p,&tempIC,object);
	(*IC_T)=tempIC;
}


/*check if line containes .string /.data instruction */
int isStorageInstruction(char *token)
{
    char s1[]=".data";
    char s2[]=".string";
    char *s=malloc(strlen(token));
    s=removeSpaces(token);
    if(strcmp(s,s1)==0)
        return 1;/*one represents data instruction*/
    else if(strcmp(s,s2)==0)
        return 2;/*two reprsents string instrucytion*/
    return 0;
}



/* check if each data line is valid and contains the correct number of commas.
if the is valid - sends each number to addNewWord function */
void addDataLine(char *numbers ,int *DC,int *IC,FILE *object,int lineCounter,int *error,int *dcTotal)
{
    char *token;
	int number;
    int ARE=4;
    int temp_IC=(*IC);
    int temp_DC=0;
    int commas=0;
    int numCounter=0;
   /*validate line of numbers*/
    commas=countCommas(numbers,lineCounter);
	if(commas ==-1)
	{
		(*error)=1;
		return;
	}
    if(numbers !=NULL) token=strtok(numbers,",");
	
    while(token !=NULL)
    {
	    numCounter++;
	    number=strtol(token,NULL,10);
	    /*validate number in line*/
	    if(number % 1 != 0)
		{
		addError(lineCounter,"invalid number - not an integer");
		(*error)=1;
		
		}
	    addNewWord(number,ARE,&temp_IC,object);
        token=strtok(NULL,",");
	    if(token!=NULL)
		fprintf(object,"%d      ",temp_IC);
	    temp_DC++;
	    (*dcTotal)++;
    }
	if(numCounter > commas+1)
    {
        addError(lineCounter," invalid Line - each number should be seperated from the other by cooma");
	    (*error)=1;
    }
	if(numCounter <commas+1)
    {
        addError(lineCounter,"invalid Line - more commas then numbers");
        (*error)=1;
    }
   	(*IC)=temp_IC;
	(*DC)=temp_DC;	
}


void addStringLine(char *string,int *DC,int *IC,FILE *object,int lineCounter,int *dcTotal)
{
   
    int i=0;
    int ARE=4;
    int temp_IC=(*IC);
    int temp_DC=0;
    /*for loop starts from 1 until string size -1 to avoid "" characters.*/
    for(i=1;i<strlen(string)-1;i++)
    {
	 
        addNewWord(string[i],ARE,&temp_IC,object);
 	fprintf(object,"%d         ",temp_IC);
	temp_DC++;
	(*dcTotal)++;      
    } 
    addNewWord(0,ARE,&temp_IC,object);

    temp_DC++;
    (*dcTotal)++;
	
	
	(*IC)=temp_IC;
	(*DC)=temp_DC;
}


/**finding the addressing merhod(AM) of each operand according to his contant and return it.also updates the value of the following variables:
 * @lines is the number of lines added to the encoding 
 * @reg is the reg number in the operand  - relevent only to methods 2 and 3
 * @num is the numaric operand- relevent only to method 0 */
int findAM(char *operand,int *reg,int *lines,int *number)
{
  char *s=(char *)malloc(strlen(operand));
	strcpy(s,operand); 
    /*for AM =0. return 4 for comfort*/
    if (s[0] == '#')
    {
	    s++;
    (*number)=strtol(s,NULL,10);
        (*lines)=1;
        return 4;
        
    }
    /*for AM =3*/
    else if(s[0] =='r')
    {
        (*lines)=0;
        (*reg)=searchReg(s);
        return 3;
    }
    /*for AM=2*/   
    else if(strstr(s,"["))
    {
        (*lines)=2;
        (*reg)=findReg(s);
        return 2;
	}
    else
    {/*for AM=2*/
        (*lines)=2;
        return 1;
    }
    
}
/*create node with the label name and the line number of the added empty line in firstscan function */
void addLabelAddress(int numLine,char * label)
{
	char * s1=NULL;
	emptyLine *newLine=(emptyLine*) malloc(sizeof(s1));
	if(strstr(label,"["))
		s1=strtok(label,"[");	
	else
	{
		s1=(char *)malloc(strlen(label)+1);
		strcpy(s1,label);
	}
	newLine->labelName=malloc(strlen(s1)+1);
	strcpy(newLine->labelName,s1);
	newLine->numLine=numLine;
	newLine->next=NULL;
	/*adding to linked list*/
	addLine(newLine);
}
/*adding the empty line address to list*/
void addLine(emptyLine * eLine)
{	
    emptyLine *ptr=NULL;
    if(headL==NULL)
    {
        headL=eLine;
    }    
    else
    {
        ptr=headL;
        while(ptr->next !=NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = eLine;
    } 
	
	
}

/*checking if the file pointer is one line above an empty line. if so return 1,else returns -1*/ 
int searchNum(int number)
{

	emptyLine * ptr=headL;
	while(ptr!=NULL)
	{
		if((number+1)==ptr->numLine)
			return 1;
		else
			ptr=ptr->next;
	}
	free(ptr);
	return -1;

}
/*if the file pointer is one line above an empty line - return the label name*/
char * searchMissingLabel(int number)
{

	emptyLine * ptr=headL;
	while(ptr!=NULL)
	{
		if((number+1)==ptr->numLine)
		{
			return ptr->labelName;
		}		
			ptr=ptr->next;
	}
	free(ptr);
	return NULL;

}



