#include "Assembler.h"
#include <errno.h>
#include <ctype.h>

/* main function opens the origin text file and sent is to preProcessor,firstScan and SecondScan function*?
if now error found - as file will be created*/

int main(int argc,char *argv[])
{
    int i;
    FILE *f1,*f2,*f3,*f,*mf,*ext,*ent;
    int IC=100,DC=0;
    int ICF=0,DCF=0;
	int dcT=0;
    int error=0,externals=0,entries=0;
	int ex,en;
    /*if only main decleared in the command line*/
    if(argc<2)
    {
        addErrorF(NULL,NULL,0);
        exit(0);
    }
    for(i=1;i<argc;i++)
    {
        f1=openFile(argv[i],".as","r");
        if(!f1)
        {
            addErrorF(argv[i],"Read",0);
            exit(0);
        }
        f2=openFile(argv[i],".am","w+");
        if(!f2)
        {
            addErrorF(argv[i],"Write",0);
            fclose(f1);
            exit(0);
        }
	    f3=openFile("temp",".txt","w+");
	    if(!f3)
    	{
            addErrorF("temp","Write",0);
            fclose(f2);
            exit(0);
	    }
        /*find macro decleration - more infromation in findMacro documentaion*/
        findMacro(f1,f2,f3);;
        remove("temp.txt");
	    mf=openFile("MemoryPicture",".txt","w+");
	    f=openFile(argv[i],".ob","w");	
        if(!mf)
        {
            addErrorF("MemoryPicture","Read and Write",0);
            fclose(f2);
            exit(0);
        }
        firstScan(&dcT,&IC,&DC,f2,mf,&error,&externals,&entries);
	/*if found errors in first scan - will print error and exit prog*/
	    if(error) 
	    {
		    addErrorF(NULL,NULL,-1);
		    exit(0);
	    }
	    ex=externals;
	    en=entries;
	    /*if externals found in file then open the ext file*/
	    if(ex)
		    ext=openFile(argv[i],".ext","w");	
	    /*if externals found in file then open the ext file*/
	    if(en)
		    ent=openFile(argv[i],".ent","w");
	    ICF=IC;
	    DCF=dcT;	
	    secondScan(mf,f2,ext,ent,&error);
	    convert(mf,f,ICF,DCF);
        remove("MemoryPicture.txt");
	}
    return 0;
}



