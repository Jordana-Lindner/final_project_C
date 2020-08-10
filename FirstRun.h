#include "assembler.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

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




void getVar();

void addString();

symboleTabel *curSNode;
dataNode *curDNode;
bool labelFlag = 0;



/*struc for operatons table*/
typedef struct{
    int opcode;
    int func;
    char *opName;
    int *sourceMeth;
    int *targMeth;
    int oprndN;
}op;

op opTable[16];

typedef struct{
    char adress[7];
    int ICval;
    int binCode[72];
    //char *opName;
    //char *opLabel;

}Code;

typedef struct CNode {
    Code code;
    struct CNode * next;
}CNode;

CNode* Chead ;
CNode *curCNode;

void get_souceOP(int opInd, char * sourceOP);



