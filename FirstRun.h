#include "assembler.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_LENGTH 200
int IC =100;
int DC =0;

extern FILE *fp;



char label[50];

bool isLabel(char param1[50]);

bool checkComma();

int isGuide(char *param);

void addSign(char label[50], char character[5], int value);

void addData();

void pointAfterParam();

void getParam();

void getVar();

void addString();

SNode *curSNode;
DNode *curDNode;
bool labelFlag = 0;
char line[MAX_LENGTH];
char *p;
char param[MAX_LENGTH];




