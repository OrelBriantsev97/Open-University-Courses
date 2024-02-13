#include "SymbolTable.h"

static symbol *headS=NULL;

/*creates a new symbol node with name,value ,base and offset address */
void createSymbol(char *label,int *DC,int *IC,char *attribute)
{
   
    char s1[]="external";

		 
    symbol *newSymbol = (symbol*) malloc(sizeof(symbol));
    if(label != NULL)
    {   /*Memory allocating to store symbol name*/
        newSymbol->symbolname=malloc(strlen(label)+1);
        strcpy(newSymbol->symbolname,label);
    }
    /*if label defined as external-value,base and offset address will be 0*/
    if(strcmp(s1,attribute)==0)
    { 
	    newSymbol->value=0;  
	    newSymbol->base=0;        
	    newSymbol->offset=0;
    }
    else
    {
        newSymbol->value=(*IC);
	    newSymbol->base=findBase(newSymbol->value);      
	    newSymbol->offset=newSymbol->value-newSymbol->base;
    }

    if(attribute !=NULL)
    { /*Memory allocating to store attributes*/
        newSymbol->attributes=malloc(strlen(attribute)+1);
        strcpy(newSymbol->attributes,attribute);
    }
    newSymbol->next=NULL;
    addSymbol(newSymbol);
}
/*adding symbol node to linked list*/
void addSymbol(symbol * Symbol)
{	
    symbol *ptr=NULL;
    if(headS==NULL)
    {
        headS=Symbol;
    }    
    else
    {
        ptr=headS;
        while(ptr->next !=NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = Symbol;
    } 
	
}
/*checks if the symbol label is already exist*/
int searchSymbolList(char *label)
{
	symbol *ptr=headS;

	
    while(ptr!=NULL)
    {
        if(strncmp(ptr->symbolname,label,strlen(label)==0))
            return -1; /*we found another kabaek with this name*/      
	ptr=ptr->next;
    }
    free(ptr);
    return 1;
    
}

/*finds the closest number to value that is smaller than the value and can be divided by 16 with no reminder
if no such number/value is amaller than 16- return 0*/
int findBase(int value)
{
    int i;
    if(value < 16)
        return 0;
    for(i=value;i>=16;i--)
    {
        if(i%16==0)
	{
            return i;
	}
    }
	return 0;
}

/*returns pointer to symbol list head*/
symbol * getHeadS()
{
	symbol * tmp=headS;
	return tmp;
}

/*check is the given label exist in the symbol list. if so returns label base address.else return -1*/
int getBaseAddress(char * label)
{
	symbol *ptr=headS;
	while (ptr!=NULL)
	{
		if(strcmp(label,ptr->symbolname)==0)
		{
			return ptr->base;
		}
		ptr=ptr->next;
	}
	free(ptr);
	return -1;
	

}

/*check is the given label exist in the symbol list. if so returns label offset address.else return -1*/
int getOffAddress(char * label)
{
	symbol *ptr=headS;
	while (ptr!=NULL)
	{
		if(strcmp(label,ptr->symbolname)==0)
		{
			return ptr->offset;
		}
		ptr=ptr->next;
	}
	free(ptr);
	return -1;

}
/*check is the given label listed as external. if so returns 1.else return -1*/
int externLabel(char *token)
{
	symbol *ptr=headS;
	while (ptr!=NULL)
	{
		if(strcmp(token,ptr->symbolname)==0)
		{
			if(strstr(ptr->attributes ,"external"))
				return 1;
		}
		ptr=ptr->next;
	}
	free(ptr);
	return 0;

}
