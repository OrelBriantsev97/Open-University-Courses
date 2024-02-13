#include "SecondScan.h"


/**finding the entry lines and send them to updateATT function.
 * then asnd to addAddress function*/
void secondScan(FILE *object,FILE *f2,FILE *ext,FILE *ent,int * errors)
{

    char buff[MAX_LINE_LENGTH];
    char *token=NULL;
    int instruction;
    int lineCounter=0;
    rewind(f2);
    rewind(object);
  

    while (fgets(buff,MAX_LINE_LENGTH, f2)!=NULL)
    {
        lineCounter++;
	    if(strlen(buff)==1) /**if line empty and contains only white spaces then ignore*/
            continue;        
	    token=strtok(buff," ""\n\t"); 	
	    if(isComment(token))/*if comment line then ignore*/
		    continue;
   	    if(isLabel(token))/*if line starts with label skips*/
		    continue;         
        instruction=isStorageInstruction(token);
        if(isExtern(token)|| instruction!=0)/*if instruction line or extern line , ignore*/
            continue;

        if(isEntry(token))
        {
            token=strtok(NULL,"\n\t");
            updateAtt(token,lineCounter,ent);
		
        }
	
    }
	
  	
    addAddress(object,ext);
}
/*adding each entry symbol in the symbol list the attribute - .entry*/
void updateAtt(char *label,int lineCounter,FILE *ent)
{
    int replaced=0;
    symbol * head=getHeadS();
    while(head != NULL)
    {
        if(strcmp(head->symbolname,label)==0)
        {
		    head->attributes=realloc(head->attributes,sizeof(char)*6);
		    strcat(head->attributes,".entry");
		    /*writes each entry symbol name,base and offset address in entries file*/ 
            fprintf(ent,"%s,%d,%d\n",head->symbolname,head->base,head->offset);
            replaced=1;
        }
        head=head->next;
    }
    if(replaced==0)
        addError(lineCounter,"label is not exist");
}
/*overwriting the empty lines with labels base and offset addresses
writing every extern label in the externals file*/
void addAddress(FILE *object,FILE * ext)
{
	char *token;
	char buff[MAX_LINE_LENGTH];
	int line=0;
	int base=0;
	int offset=0;
	char *label;
 	int ARE=0;
	int lineNum;;

	while (fgets(buff,MAX_LINE_LENGTH,object))
	{
		token=strtok(buff," " "\n\t");
		line=strtol(token,NULL,10);

		if(searchNum(line)==1)
		{			
			label=searchMissingLabel(line);
			if(label ==NULL) 
				addErrorSF(line);	
			base=getBaseAddress(label);
			if(base!=-1)
			{
				fprintf(object,"%d         ",line+1);
				if(externLabel(label))
				{/*printing base and offset addresses of extern labels*/
					fprintf(ext,"%s BASE %d\n",label,line+1);
					lineNum=line+2;
					fprintf(ext,"%s OFFSET %d\n",label,lineNum);
					fprintf(ext,"\n");
					ARE=1;		
				}
				else ARE=2;
				addNewWord(base,ARE,&line,object);
				offset=getOffAddress(label);
				if(offset!=-1)
				{
					fprintf(object,"%d         ",line+1);
					addNewWord(offset,ARE,&line,object);
				}				
			}			
		}	
	} 
}


