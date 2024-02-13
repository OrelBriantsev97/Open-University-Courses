#include "PreProcessor.h"

static macroNode *headM=NULL;
/*
 * Scaning the input files to find macro decleration.
 * if macro decleration exist-store the macro information in linked list and replace every macro calling line with his macro data instead. 
 * information on how each function works - above each function*/
 /* Scaning file to find macro decleration using char m.
 * if found- sends buffer and files pointer to createMacroNode file
 *  f1 source file, f2 and f3 empty at this point */

void findMacro(FILE *f1,FILE *f2,FILE *f3)
{
    char buff[MAX_LINE_LENGTH];
    char *m = "macro";  	
    while (fgets(buff,MAX_LINE_LENGTH, f1)!=NULL)
    {
        /*Finding macro secleration*/
   	    if(strstr(buff,m))
            createMacroNode(f1,f2,buff);
        else
            fputs(buff,f2);   
    }
    rewind(f1);
    rewind(f2);
    addRest(f3,f2,buff);
    secondPass(f2,f3,buff);
}
/* Seperate buffer to tokens in order to delete the word "macro" in the file and return only the macro name */
char * deleteFirstWord(char *buff)
{
    char *token;
    char delim[]=" ";
    token=strtok(buff,delim);
    if(token!=NULL)
        token=strtok(NULL,delim);
    return token;
}
/* Adding the macro data to a string and returning the string */
char * getLine(char *buff,FILE *f1)
{
    /*According to course forum - maximun macro data is six line with maximum 80 characters each line*/
    char *s=malloc(MAX_LINE_LENGTH*6);
    char *word = "endm";
    /*While loop runs from the line after macro decleration until endm found in file*/
    while(fgets(buff,MAX_LINE_LENGTH, f1) != NULL && !strstr(buff,word))
        strcat(s,buff);
    return s;
}

void createMacroNode(FILE *f1,FILE *f2,char * buff)
{
    char *macroName;
    char *macroData;
    struct macroNode *newNode = (struct macroNode*) malloc(sizeof(macroNode));
    /*Memory allocating to store macro name and data */
    macroName=deleteFirstWord(buff);
	newNode->name=malloc(strlen(macroName)+1);
    strcpy(newNode->name,macroName);

    macroData=getLine(buff,f1);
    newNode->data=malloc(strlen(macroData)+1);
    strcpy(newNode->data,macroData);

    newNode->next=NULL;
    addMacroNode(newNode);
  }
/*Adding node to linked list*/
void addMacroNode (macroNode * node)
{
	macroNode *ptr=NULL;
    if(headM==NULL)
    {
        headM=node;
    }    
    else
    {
        ptr=headM;
        while(ptr->next !=NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = node;
    }   
}

macroNode * getPointer()
{
    macroNode * ptr;
    ptr = headM;
    return ptr;
}
/*Second scan to f2 file-now f2 dont contains macro declaration but contains macro calling
*if macro name is found then replace it with macro data instead*/
void secondPass(FILE *f2,FILE *f3,char *buff)
{
	long int pos;
    macroNode * ptr=getPointer();
    char *s=malloc(strlen(buff));
    while(ptr!=NULL )
    {
        while(fgets(buff,MAX_LINE_LENGTH, f3)!=NULL)
        {
            s=removeWhiteSpaces(buff);
            if(strcmp(s,ptr->name)==0)
	        { 
                fseek(f2,pos,SEEK_SET);
			    fprintf(f2,"%s", ptr->data);
			    addRest(f2,f3,buff);
                		return;
		    }
		    pos=ftell(f3); 	
	    }
	    ptr=ptr->next;
    }
}
/*adds file 2 lines to file1*/
void addRest(FILE *file1,FILE *file2,char *buff)
{
	while(fgets(buff,MAX_LINE_LENGTH, file2)!=NULL)
	{
		fputs(buff,file1);
	}
	rewind(file1);
	rewind(file2);

}
/*Remove white spaces from buffer*/ 	
char * removeWhiteSpaces(char* s) 
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

