
#include "functionsForAssembler.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#define TOTAL_OP 16

int IC =100;
int DC =0;

extern FILE *fp;



char label[50];

bool isLabel(char param[50]);

bool checkComma();

void get_opcode(char *opcode);

void addSign(char label[50], char character[5], int value);

void addData();



int validate_command(char *opcode);


void fillin_op_table();

void getVar();

void addString();

symboleTabel *curSNode;
dataNode *curDNode;
bool labelFlag = 0;



void get_opcode(char *opcode);

/*struc for operatons table*/
typedef struct{
    int opcode;
    int func;
    char *opName;
    int *sourceMeth;
    int *targMeth;
    int oprndN;
}op;



typedef struct{
    int adress;
    int ICval;
    char binCode[24];
    char opName[MAX_LENGTH];
    char opLabel[MAX_LENGTH];
    char operandLabel[MAX_LENGTH];

}Code;

typedef struct CNode {
    Code code;
    struct CNode * next;
}CNode;

CNode* Chead ;
CNode *curCNode;



op opTable[16];