
#include "Errors.h"
/*errors file-contains all the errors printing functions divided by the error type*/
/*print files related error */

void addError(int line,char *error)
{
	fprintf(stderr,"ERROR in line %d :%s\n",line,error);
}
void addErrorF(char *fileName,char *permission,int num)
{
    if(fileName ==NULL && permission ==NULL && num==0)
        fprintf(stderr,"Error,you did not entered any files to convert\n");
    else if(num ==-1)
	fprintf(stderr,"Errors detected in your source file, please check and try again\n");
    else    
        fprintf(stderr,"Error:cannot access  %s file! please check if the file is exist and you have %s privilege\n",fileName,permission);   
}
/*print first scan related errors*/
void addErrorFS(int line ,char *error)
{
    fprintf(stderr,"ERROR in line %d : %s\n",line,error);
}
/*print address method related errors*/
void addErrorAM(int line ,int method,char *operation)
{
    fprintf(stderr,"ERROR in line %d : invalid addressing method. can not use method %d for operand  %s\n",line,method,operation);
}
/*print origin operand related errors*/    
void addErrorO(int line,char *error,char *operation)
{
    if(error == NULL)
        fprintf(stderr,"ERROR in line %d: %s instruction cant have operands \n",line,operation);
    else
        fprintf(stderr,"ERROR in line %d: need %s operands for %s instruction \n",line,error,operation); 
}
/*print destination operand related errors*/
void addErrorD(int line,char *operation)
{
    fprintf(stderr,"ERROR in line %d: %s instruction cant have origin operand \n",line,operation);
}
/*print register number related errors*/
void addErrorR(int line)
{
    fprintf(stderr,"ERROR in line %d: reg number is missing/inncorect \n",line);
}
/*print numeric operand related errors*/
void addErrorN(int line ,char *type)
{
    fprintf(stderr,"ERROR in line %d: %s operand should contains only number\n",line,type);
}
/*print second scan related errors*/
void addErrorSF(line)
{
    fprintf(stderr,"ERROR in line %d : label is not exist\n",line);
}
