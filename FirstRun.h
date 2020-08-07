#include "assembler.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>


int IC =100;
int DC =0;

extern FILE *fp;



char label[50];

bool isLabel(char param[50]);

bool checkComma();



void addSign(char label[50], char character[5], int value);

void addData();





void getVar();

void addString();

SNode *curSNode;
DNode *curDNode;
bool labelFlag = 0;





