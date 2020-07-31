#include <stddef.h>
#include <stdlib.h>
typedef struct{
    char label[50];
    int value;
    char car[50];
}Sign;

typedef struct SNode {
    Sign sign;
    struct SNode * next;
}SNode;

SNode* shead ;

typedef union Data{
    int num;
    char ch;
}Data;

typedef struct DNode {
    Data data;
    struct DNode* next;
}DNode;

DNode* dhead;

void firstRun();
/*void secondRun();*/
void skipWhite();
