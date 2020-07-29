
#include <stdbool.h>
#include "FirstRun.h"

char label[50];

bool isLabel(char param1[50]);
int checkComma();

int isGuide(char *param);

void addSign(char label[50], char character[5]);

void addData();

void pointAfterParam();

void getParam();

SNode *curSNode;
DNode *curDNode;
bool labelFlag = 0;
char line[MAX_LENGTH];
char *p;
char param[MAX_LENGTH];

void firstRun() {

    shead = (SNode *) malloc(sizeof(SNode));
    curSNode = shead;
    dhead = (DNode *) malloc(sizeof(DNode));
    curDNode = dhead;


    //while (!feof(fp)) {
    while (fgets(line, MAX_LENGTH, fp)) {
        p = line;
        getParam();
        labelFlag = isLabel(param);
        if (labelFlag) {
            getParam();
        }
        switch (isGuide(param)) {
            case 1: {

                if (labelFlag)
                    addSign(label, "data");
                //getParam();
                addData();
            }
        }


    }
}

void getParam() {
    skipWhite();
    sscanf(p, "%s 255[^,]", param);
    skipWhite();
    pointAfterParam();
}

void pointAfterParam() {
    p += strlen(param);
}

void addData() {
    bool needComma = 0;
    int commaCounter = 0;
    int num;
    if(checkComma()!=0){
        printf("misplaced comma");
        return;}

    if (*p == '\0') {
        fprintf(stderr, "missing data\n");
        return;
    }

    while (*p != '\0') {
        if (needComma)
            if(checkComma()==0){
                fprintf(stderr, "Missing comma\n");
                return;
            }
            if(checkComma()>1){
                fprintf(stderr, "Multiple consecutive commas\n");
                return;
        }
        if(!getVar()){

        }
       needComma=1;
        }
    }


int checkComma(){
    int commaCount =0;
    skipWhite();
    /*check if the first letter (after skipWhite is a comma and looks for multiple commas*/
    while (strncmp(p, ",", 1) == 0) {
        commaCount++;
        p++;
        skipWhite();
    }
    return commaCount;
}

bool getVar(){

}


void addSign(char label[50], char character[50]) {

    strcpy(curSNode->sign.label, label);
    curSNode->sign.value = (IC + DC);
    strcpy(curSNode->sign.car, character);

    SNode *newSNode = (SNode *) malloc(sizeof(SNode));
    curSNode->next = newSNode;
    curSNode = newSNode;

}

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

bool isLabel(char param[50]) {
    int length = strlen(param);
    if (*param < 'A' || (*param > 'Z' && *param < 'a') || *param > 'z')
        return 0;
    if (length > 1 && param[length - 1] == ':') {
        strcpy(label, param);
        return 1;
    }

    return 0;
}

void skipWhite() {
    while (isspace(*p))
        p++;
}

