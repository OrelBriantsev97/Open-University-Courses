#ifndef FILES_H
#define FILES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Utils.h"

FILE * openFile(char * ,char * ,char * );
void convert(FILE * object,FILE *f,int,int);

#endif
