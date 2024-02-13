#ifndef FIRST_SCAN_H
#define FIRST_SCAN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "SymbolTable.h"
#include "Utils.h"
#include "Validation.h"
#include "Errors.h"



void firstScan(int*,int *,int * ,FILE *,FILE *,int *,int *,int *);
void analyzeCommand(int ,int *,char *,char *,int,FILE *,int *);
void processFirstWord(int ,int *,FILE *);
void processSecondWord(int ,int ,int ,int ,int ,int ,int ,int,int *,FILE *);


#endif










