#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define MAX_LINE_LENGTH 80

typedef struct macroNode
{
        char *name;
        char *data;
        struct macroNode *next;
}macroNode;


void findMacro(FILE *,FILE *,FILE *);
char * deleteFirstWord(char *);
void createMacroNode(FILE *,FILE *,char *);
void addMacroNode (macroNode *);
macroNode * getPointer();
void secondPass(FILE *,FILE *,char *);
char * getLine(char *,FILE *);
void printList(struct macroNode* );
char * removeWhiteSpaces(char* );
void addRest(FILE *,FILE *,char *);


#endif

