#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Errors.h"
#include "SymbolTable.h"

#define MAX_LINE_LENGTH 80
#define MAX_LABEL_LENGTH 31


typedef struct operations
{
    char *str;
    int opcode;
    int funct;
    int numOfOperands;
}operations;



typedef struct registers
{
    char *str;
    int num;
}registers;

struct newWord
{
    unsigned int opcode : 16;
    unsigned int ARE : 3;
    unsigned int zero : 1;
    struct newWord *next;

}newWord;


struct firstLine
{
    unsigned int opcode : 16;
    unsigned int ARE :3;
    unsigned int zero :1;
    struct opCode *next;
}firstLine;

struct secondLine
{
    unsigned int amDest : 2;
    unsigned int regDest : 4;
    unsigned int amOrign : 2;
    unsigned int regOrigin : 4;
    unsigned int funct : 4;
    unsigned int ARE : 3;

}secondLine;

typedef struct emptyLine
{
	char *labelName;
	int numLine;
	struct emptyLine *next;
}emptyLine;

bool isComment(char *);
int isLabel(char *);
char * getLabel(char *,int);
char * removeSpaces(char *);
int countCommas(char *,int);
bool isEntry(char *);
bool isExtern(char *);
int searchOp(char *);
int searchReg(char *);
int findReg(char *);
void binaryLine( int ,int *,FILE *);
void addNewWord(int ,int ,int *,FILE *);
int isStorageInstruction(char *);
void addDataLine(char * ,int *,int *,FILE *,int,int *,int *);
void addStringLine(char *,int *,int *,FILE *,int,int*);
int findAM(char *,int *,int *,int *);
void addLabelAddress(int ,char *);
void addLine(emptyLine * );
int searchNum(int );
char * searchMissingLabel(int );


#endif



