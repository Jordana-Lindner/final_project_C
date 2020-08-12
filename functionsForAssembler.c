
#include "functionsForAssembler.h"

/*checks of its a lable to turn on label flag*/
bool isLabel(char param[50]) {

    int length = strlen(param);
    if (!isalpha(*param))//*param < 'A' || (*param > 'Z' && *param < 'a') || *param > 'z')
        return 0;
    if (length > 1 && param[length - 1] == ':') {
        if (length >31){
            printf("to long to be a label\n");
            return 0;
        }
        if (isGuide(param)){ /*need - or command or register or already is a label*/
            printf("unvalid name for label\n");
            return 0;
        }
        if (inLabelTab(param)){
            printf("alleardy is label with same name\n");
            return 0;
        }
        strcpy(label, param);
        return 1;
    }

    return 0;
}


/*gets parameter from line*/
void getParam() {
    skipWhite();
    if ((sscanf(p, "%s", param))== 0)
    {
      *param = '\0';
    }
    skipWhite();
    pointAfterParam();
}


/*move pointer after last parameter*/
void pointAfterParam() {
    p += strlen(param);
}

/*points pointer p after white space*/
void skipWhite() {
    while (isspace(*p))
        p++;
}

/*if its a guide command*/
int isGuide(char param[50]) {
    if (!strcmp(param, ".data"))
        return 1;
    else if (!strcmp(param, ".string"))
        return 2;
    else if (!strcmp(param, ".entry"))
        return 3;
    else if (!strcmp(param, ".extern"))
        return 4;

    return 0;
}

// Convert an integer to binary (in a string)
void int2bin(unsigned integer, char* binary, int n)
{
    int i;
    for (i=0;i<n;i++)
        binary[i] = (integer & (int)1<<(n-i-1)) ? '1' : '0';
    binary[n]='\0';
}


bool inLabelTab (char param[50]){
    symboleTabel *curSNode;
    curSNode = sHead;
    while (curSNode != NULL){
        if (strcmp(curSNode->sign.label, param)==0) {
            return 1;
        }
        curSNode = curSNode->next;
    }
}

