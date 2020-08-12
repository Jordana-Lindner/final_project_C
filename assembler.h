
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>


typedef struct{
    char label[50];
    int value;
    char car[50];
}Sign;

typedef struct SNode {
    Sign sign;
    struct SNode * next;
}symboleTabel;

symboleTabel* sHead;
symboleTabel* curSNode;

typedef union Data{
    int num;
    char ch;
}Data;

typedef struct DNode {
    Data data;
    struct DNode* next;
}dataNode;


dataNode* dHead;
dataNode* curDNode;


void firstRun();
void secondRun();
/*void secondRun();*/

