#include "assembler.h"
#include <stdio.h>
#include <string.h>
#define MAX_LENGTH 50
int IC =100;
int DC =0;

extern FILE *fp;



enum codeTabel{
    char name;
    int adress;
    type say_action;
    boolean external;

};

int[] data;

enum signTable{
    char sign;
    int value;
    type code_data;
};

