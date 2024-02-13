#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX_LENGTH 80 /*string max length*/
void contract (char[],char[]);
int main ()
{
	char s1[MAX_LENGTH+1];
	char s2[MAX_LENGTH+1];
	

	printf("Please enter your String: \n");
	fgets(s1,MAX_LENGTH+1,stdin);
	contract(s1,s2);
	printf("Original String:\t%s\n",s1);
	printf("Shortened String:\t%s\n",s2);
	return 1;
}


void contract (char s1[], char s2[])
{
	int i,j=0;
	int counter=0;
    
	
		for(i=0;s1[i]!='\0';i++)
		{
        		if(isalnum(s1[i])) /* if alphnumeric char*/
			{
				if( s1[i+1]-s1[i] == 1 ) /*if ASCII value in s[i+1] =s[i]+1*/		
					counter++;
				else if (s1[i+1]-s1[i] != 1 )
				{	
					if(counter > 1)	/*puting the first char of the sequence,then the char '-' and then the last char of sequence*/
					{
						s2[j]=s1[i-counter];
						s2[j+1]= '-';
						s2[j+2]=s1[i];
						j=j+3;
						counter=0;
					}
					else if(counter == 1)
					{
						s2[j]=s1[i-counter];
						s2[j+1]=s1[i];
						j=j+2;
						counter=0;
					}
					else
					{
						s2[j]=s1[i];
						j++;
						counter=0;
					}
				}	
			}
          		else /*for non alfphnumeric char*/
         		{
              			s2[j]=s1[i];
              			j++;
            		}
        	} 
		s2[j]='\0'; /*ending s2*/
		
	
}
