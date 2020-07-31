
#include <stdbool.h>
#include "FirstRun.h"

char label[50];

bool isLabel(char param1[50]);

bool checkComma();

int isGuide(char *param);

void addSign(char label[50], char character[5]);

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
            case 2: {

                if (labelFlag)
                    addSign(label, "data");
                //getParam();
                addString();
            }
        }


    }
}

void addString() {
    int check = 0;
    skipWhite();
    if (*p == ',') {
        printf("bad place for comma");
        return;
    }
    if (*p == '\n') {
        printf("missing data");
        return;
    }
    getVar();
    printf("%d: %s\n", check, param);
    while (*p != '\0') {
        check++;
        if (!checkComma()) {
            return;
        } else {
            getVar();
            printf("%d: %s\n", check, param);
            if (!atoi(param)) {
                printf("wrong input for data");
                return;
            } else {
                curDNode->data.num = atoi(param);
                SNode *newSNode = (SNode *) malloc(sizeof(SNode));
                curSNode->next = newSNode;
                curSNode = newSNode;
            }

        }
    }
}


void getParam() {
    skipWhite();
    sscanf(p, "%s", param);
    skipWhite();
    pointAfterParam();
}

void pointAfterParam() {
    p += strlen(param);
}

void addData() {
    int check = 0;
    skipWhite();
    if (*p == ',') {
        printf("bad place for comma");
        return;
    }
    if (*p == '\n') {
        printf("missing data");
        return;
    }
    getVar();
    printf("%d: %s\n", check, param);
    while (*p != '\0') {
        check++;
        if (!checkComma()) {
            return;
        } else {
            getVar();
            printf("%d: %s\n", check, param);
            if (!atoi(param)) {
                printf("wrong input for data");
                return;
            } else {
                curDNode->data.num = atoi(param);
                SNode *newSNode = (SNode *) malloc(sizeof(SNode));
                curSNode->next = newSNode;
                curSNode = newSNode;
            }

        }

    }

}

void getVar() {
    skipWhite();
    sscanf(p, "%[^,]", param);
    skipWhite();
    pointAfterParam();
}

bool checkComma() {
    skipWhite();
    int counter = 0;
    /*check if the first letter (after skipWhite is a comma and looks for multiple commas*/
    while (*p == ',') {
        counter++;
        p++;
        skipWhite();
    }
    if (counter == 0) {
        printf("Missing comma\n");
        return false;
        /*more then one comma*/
    } else if (counter > 1) {
        printf("Multiple consecutive commas\n");
        return false;
    }
    return true;
    /*  int commaCount = 0;
      skipWhite();
      *//*check if the first letter (after skipWhite is a comma and looks for multiple commas*//*
    while (strncmp(p, ",", 1) == 0) {
        commaCount++;
        p++;
        skipWhite();
    }
    if (commaCount == 0) {
        return 0;
    } else if (commaCount > 1) {
        fprintf(stderr, "Multiple consecutive commas\n");
        return 0;
    } else
        return 1;*/
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

