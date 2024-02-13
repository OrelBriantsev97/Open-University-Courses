#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct symbol
{
    char *symbolname;
    int base;
    int offset;
    int value;
    char *attributes;
    struct symbol *next;
}symbol;



void createSymbol(char *,int *,int *,char *);
void addSymbol(symbol * );
int searchSymbolList(char *);
int findBase(int );
symbol * getHeadS();
void freeHead();
int getBaseAddress(char * );
int getOffAddress(char * );
int externLabel(char *);



#endif
