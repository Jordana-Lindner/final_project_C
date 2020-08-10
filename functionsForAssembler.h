
#include <stdbool.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "assembler.h"
#define MAX_LENGTH 200



char label[50];
char line[MAX_LENGTH];
char *p;
char param[MAX_LENGTH];
bool inLabelTab (char param[50]);
bool isLabel(char param1[50]);
void pointAfterParam();
void getParam();
void skipWhite();
int isGuide(char *param);
void int2bin(unsigned integer, char* binary, int n);