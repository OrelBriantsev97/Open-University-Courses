#ifndef VALIDATION_H
#define VALIDATION_H
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include "Errors.h"
#include "Utils.h"
#include "SymbolTable.h"

int validateLabel(char *,int );
int validateCommand(char *,int ,int ,int ,int ,int ,int ,int ,int );
int validateReg(int );
#endif
