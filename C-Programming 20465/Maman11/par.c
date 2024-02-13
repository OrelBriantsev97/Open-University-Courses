    
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define QUOTES 34
#define OPENING_ROUND 40
#define CLOSING_ROUND 41
#define ASTERISK 42
#define SLASH 47
#define OPENING_SQUARE 91
#define CLOSING_SQUARE 93
#define MAX_LINE_LENGTH 100
#define OPENING_CURLY 123
#define CLOSING_CURLY 125
#define SPECIAL_LINE_OPEN -1
#define SPECIAL_LINE_CLOSE -2
#define NOT_BALANCED_LINE -3

int balance(char [],int);
int isSpecialLine(char[],int,int);
int  getLine(char[]);
void printLine(int,int);
void summary(int,int,int);
int check(char line[],int,int);
int checkLine(char[],int,int,int);
int counter(char[]);
int isComment(char[]);
int outOfComment(char[],int);

enum status {OUT,IN_COMMENT,CURLY_C,CURLY_O,ROUND_O,ROUND_C,SQUARE_O,SQUARE_C,LEFT_SLASH,IN_STRING,STAR };

int main()
{

    int open = 0;
    int close = 0;
    int check=0;
    int comment=0;
    int NonBalancedLine=0;
    char line[MAX_LINE_LENGTH+1];
    printf("Please enter your program: \n");
    while(getLine(line))   
    {
        printf("\n\n%s\n",line);
        comment=isComment(line);
        if(comment == 1)/*if line is a comment then skip it*/
            break;
        else
        /*check stores checkLine method return value.if the line is special,counter open/close increasing by one accordingly.*/
        check=checkLine(line,open,close,comment);    
        if(check == SPECIAL_LINE_OPEN)
            open++;
        else if(check== SPECIAL_LINE_CLOSE)
            close++;
        else if(check==NOT_BALANCED_LINE)
            NonBalancedLine++;
    }
    summary(open,close,NonBalancedLine);
    return 1;

}

int isComment(char line[])/*checks if the line containes notes.if so,we skip this line so it wont enter to the balance method*/
{
    int outOfComments=0;
    int i;
    int inComment = 0;
    for(i=0;line[i]!='\0';i++)
    {
        if(line[i]==SLASH && line[i+1]==ASTERISK)
        {
            inComment=1;
            outOfComments = outOfComment(line,i+2);
        }
    }   if(outOfComments > 2)
            inComment=outOfComments;
        
    return inComment;
}

int outOfComment(char line[],int j)/*check when are we out of the comment and return tne char after the note ends.*/
{
    int k;
    int outComment=0;
    for(k=j;line[k] != '\0';k++)
    {
        if(line[k]==ASTERISK && line[k+1]==SLASH)
            outComment=k+2;
    }
    return outComment;
}   

int getLine(char line[])/*gets a line from user code*/
{  
    while(fgets(line,MAX_LINE_LENGTH+1,stdin)!= NULL)
    {
        line[strcspn(line,"\n")] ='\0';
        return 1;
    }
    return 0;
}
int checkLine(char line[],int open,int close,int index)/*check if specific line is special or not . if not,sends line to balance check.*/
{
    int result;
    if(!isSpecialLine(line,open,close))
    {
        result=balance(line,index);
    }
    else
       result=counter(line);
    return result;

}

int balance (char line[],int index)/*tracking code and dividing by status:curly brackets,round brackets,etc..*/
{
    int i=0;
    int state=OUT;
    
    int balancedLine = 0;
    int specialLine = 0;

    for(i=index;line[i] !='\0';i++)
    {   if(isspace(line[i]) || isalnum(line[i]))/*space,numbers,letters are not relevant to the balance check*/
        {
            balancedLine=1;
             continue;
            
        }
        switch(state)
        {
            case OUT:
                if(line[i]==QUOTES)
                {
                    state = IN_STRING;
                }
                else if(line[i]== OPENING_CURLY)   
                    state = CURLY_O;   
                else if(line[i] == OPENING_ROUND)
                    state = ROUND_O;
                else if(line[i] == OPENING_SQUARE)
                    state = SQUARE_O;
                else if(line[i] == CLOSING_CURLY)
                    state = CURLY_C;
                    
                    
                else if(line[i] == CLOSING_ROUND)
                    state = ROUND_C;
                else if(line[i] == CLOSING_SQUARE)
                    state =SQUARE_C;
                break;


            case IN_STRING:
                if(line[i] == QUOTES)
                {   balancedLine=1;
                    state = OUT;
                }
                continue;

            case SQUARE_O:
                if(line[i] == OPENING_ROUND ||line[i] == CLOSING_ROUND)
                {
                        if(line[i] == OPENING_ROUND)
                            state=ROUND_O;
                        else if(line[i] == CLOSING_ROUND)
                            state = ROUND_C;
                }
                else if(line[i] == OPENING_CURLY||line[i] == CLOSING_CURLY)
                {
                        if(line[i] == OPENING_CURLY)
                            state=CURLY_O;
                        else if(line[i] == CLOSING_CURLY)
                            state = CURLY_C;
                }
                else if(line[i] == CLOSING_SQUARE)
                     balancedLine=1;
                break;

            case ROUND_O:
                if(line[i] == OPENING_CURLY ||line[i] == CLOSING_CURLY)
                {
                        if(line[i] == OPENING_CURLY)
                            state = CURLY_O;
                        else if(line[i] == CLOSING_CURLY)
                            state = CURLY_C;
                }
                else if(line[i] == OPENING_SQUARE ||line[i] == CLOSING_SQUARE)
                {
                        if(line[i] == OPENING_SQUARE)
                            state=SQUARE_O;
                        else if(line[i] == CLOSING_SQUARE)
                            state = SQUARE_C;
                }
                else if(line[i] == CLOSING_ROUND)
                {
                    balancedLine=1;
                    state=OUT;

                }   
                break;

            case CURLY_O: 
                if(line[i] == OPENING_ROUND ||line[i] == CLOSING_ROUND)
                {
                    if(line[i] == OPENING_ROUND)
                        state=ROUND_O;
                    else if(line[i] == CLOSING_ROUND)
                        state = ROUND_C;
                }
                else if(line[i] == OPENING_SQUARE||line[i] == CLOSING_SQUARE)
                {
                        if(line[i] == OPENING_SQUARE)
                            state=SQUARE_O;
                        else if(line[i] == CLOSING_ROUND)
                            state = SQUARE_C;
                }
                else if(line[i] == CLOSING_CURLY)
                    balancedLine=1;
                break;
        }
    }
    printLine(balancedLine,specialLine);
    if(!balancedLine)
    return NOT_BALANCED_LINE;  
    else
    return balancedLine;
}

void printLine(int result,int specialLine)
{
    if(result)
        printf("This line is balanced\n");
    else if(specialLine)
        printf("This line is not balanced\n");
    else
    {
        printf("This line is not balanced\n");
        
    } 
}

int isSpecialLine(char line[],int open,int close)/*check if specific line contain only one curly brackets: {/}*/
{
    int balancedLine=false;
    int specialLine=0;
    int i;
    int counter=0;
    for(i=0;line[i]!='\0';i++)
    {
        if(line[i] == OPENING_CURLY || line[i] ==CLOSING_CURLY)
            counter++;
        else if(isspace(line[i]))
             continue;
    }
    if(counter==1)
    {
        specialLine=1;
        printLine(balancedLine,specialLine);   
    }
    return specialLine;
}

int counter(char line[])/*counter for dpecial line.use to check if number of { equales to number of }*/
{
    int i;
    int result=0;
    for(i=0;line[i]!='\0';i++)
    {
        if(line[i] == OPENING_CURLY)
            result = SPECIAL_LINE_OPEN;
        else if(line[i] == CLOSING_CURLY)
            result =SPECIAL_LINE_CLOSE;
        else if(isspace(line[i]))
            continue;
    }
    return result;
}

void summary(int open,int close,int NonBalancedLine) /*summery for given code*/
{
    int notBalanced=NonBalancedLine;
    printf("\n***************************************\n");
    if((open == close && notBalanced == 0) || (open ==0 && close ==0 && notBalanced==0 ))
        printf("This Code is perfectly balanced :)");
    else    
        printf("This code is not balanced :(");
    printf("\n***************************************\n");
}
  
