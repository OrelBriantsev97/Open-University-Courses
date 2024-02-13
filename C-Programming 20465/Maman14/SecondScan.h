#ifndef SECOND_SCAN_H
#define SECOND_SCAN_H
#include <stdio.h>
#include <stdlib.h>
#include "Utils.h"
#include "SymbolTable.h"
#include "Errors.h"



void secondScan(FILE *,FILE *,FILE *,FILE *,int *);
void analyize(char *,int);
void updateAtt(char *,int,FILE *);
void addAddress(FILE *,FILE *);

#endif
