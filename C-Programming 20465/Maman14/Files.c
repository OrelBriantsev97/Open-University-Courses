#include "Files.h"

/*opens file according to the requested name and extention*/
FILE *openFile(char * fileName,char * extention,char * permissions)
{

	char* ext = extention;
	FILE *file;
	/*allocating memory to store file name+ ext*/
	char* filename = malloc(strlen(fileName) + strlen(ext) + 1);
	/*copy file name*/
	strcpy(filename,fileName);
	/*copy extention of file*/
	strcat(filename,ext);	
	file = fopen(filename, permissions);
	return file;	
}
/*converting each line from the txt file to hexadicimal value*/
void convert(FILE * object,FILE *f,int ic,int dc)
{
	char *token;
	char buff[MAX_LINE_LENGTH];
	char *a,*b,*c,*d,*g;
	int anum,bnum,cnum,dnum,gnum; 

	
	rewind(object);
	ic=ic-(100+dc);
	fprintf(f,"%d %d\n",ic,dc);
	while (fgets(buff,MAX_LINE_LENGTH, object)!=NULL)
	{		
		token=strtok(buff," ""\n\t");
		fprintf(f,"0%s\t",token); 
		token=strtok(NULL,"\n\t");
		token=removeSpaces(token);
		/*allocating memory to store 4 digit*/
		a=(char *) malloc (4);		
		strncat(a,token,4);
		anum=strtol(a,NULL,2);		
		fprintf(f,"A%x-",anum);
		token=token+4;
		/*allocating memory to store 4 digit*/
		b=(char *) malloc (4);		
		strncat(b,token,4);
		bnum=strtol(b,NULL,2);
		fprintf(f,"B%x-",bnum);
		token=token+4;
		/*allocating memory to store 4 digit*/
		c=(char *) malloc (4);		
		strncat(c,token,4);
		cnum=strtol(c,NULL,2);
		fprintf(f,"C%x-",cnum);
		token=token+4;
		/*allocating memory to store 4 digit*/
		d=(char *) malloc (4);		
		strncat(d,token,4);
		dnum=strtol(d,NULL,2);
		fprintf(f,"D%x-",dnum);
		token=token+4;
		/*allocating memory to store 4 digit*/
		g=(char *) malloc (4);		
		strncat(g,token,4);
		gnum=strtol(g,NULL,2);
		fprintf(f,"E%x\n",gnum);
	}
}


