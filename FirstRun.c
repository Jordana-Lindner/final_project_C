
#include "FirstRun.h"

/*start first run */
void firstRun() {
    /*new heads for linked lists */
    shead = (SNode *) malloc(sizeof(SNode));
    curSNode = shead;
    dhead = (DNode *) malloc(sizeof(DNode));
    curDNode = dhead;

    /*while file has a line*/
    while (fgets(line, MAX_LENGTH, fp)) {
        /*points to first letter in line*/
        p = line;
        getParam();
        /*turn on flag if there is a sign*/
        labelFlag = isLabel(param);
        /*gets next param*/
        if (labelFlag) {
            getParam();
        }
        /*if its a guide command (.data/.string/.extern/.entry)*/
        switch (isGuide(param)) {
            /*.data guide */
            case 1: {

                if (labelFlag)
                    addSign(label, "data", DC);
                //getParam();
                addData();
            }
                break;
                /*.string guide */
            case 2: {

                if (labelFlag)
                    addSign(label, "data", DC);
                //getParam();
                addString();
            }
                break;
                /*entry guide*/
            case 3: {
            }
                break;
                /*extern guide*/
            case 4: {
                getParam();
                addSign(param, "external", 0);
            }
                break;
            default: {

            }
                break;
        }


    }
}


/*method to add string data into data image
 *
 * needs - a.to check the string
 *         b. check extranous data
 * */
void addString() {
    int check = 0;
    skipWhite();
    /*if nothing to add to data*/
    if (*p == '\n') {
        printf("missing data\n");
        return;
    }
    /*dosnt start string with " */
    if (*p != '\"') {
        printf("has to start with \" \n");
        return;
    }
    p++;
    skipWhite();
    if (!isalpha(*p)) { //maybe needs to be changed to isascii
        printf("missing char\n");
        return;
    }
    /*while not end of line or end of string*/
    while (*p != '\0' && *p != '\"') {
        /*adds the char to data linked list*/
        curDNode->data.ch = *p;
        DNode *newDNode = (DNode *) malloc(sizeof(DNode));

        printf("%c\n", curDNode->data.ch);

        curDNode->next = newDNode;
        curDNode = newDNode;

        DC++;
        p++;
        skipWhite();
    }
    /*check if last char is "*/
    if (*p != '\"') {
        printf("has to end with \" \n");
        return;
    }
    /*adds the char \0 at the end of linked list*/
    curDNode->data.ch = '\0';
    DNode *newDNode = (DNode *) malloc(sizeof(DNode));
    curDNode->next = newDNode;
    curDNode = newDNode;
    DC++;

}

/*gets parameter from line*/
void getParam() {
    skipWhite();
    sscanf(p, "%s", param);
    skipWhite();
    pointAfterParam();
}

/*move pointer after last parameter*/
void pointAfterParam() {
    p += strlen(param);
}

/*adds data to data linked list*
 *
 * needs- a. return error if comma after last var*/

void addData() {
    int check = 0;//temporary check
    skipWhite();

    /*if starts with comma*/
    if (*p == ',') {
        printf("bad place for comma\n");
        return;
    }
    /*if empty data*/
    if (*p == '\n') {
        printf("missing data\n");
        return;
    }
    getVar();
    /*if not a number*/
    if (!atoi(param)) {
        printf("wrong input for data\n");
        return;
    }
    /*insert data to linked list*/
    curDNode->data.num = atoi(param);
    printf("%d: %d\n", check, atoi(param));
    DNode *newDNode = (DNode *) malloc(sizeof(DNode));
    curDNode->next = newDNode;
    curDNode = newDNode;

    DC++;

/*while not end of line*/
    while (*p != '\0') {
        check++;
        /*if missing comma or mult commas*/
        if (!checkComma()) {
            return;

        } else {
            getVar();

            if (!atoi(param)) {
                printf("wrong input for data\n");
                return;
            } else {
                /*insert data*/
                curDNode->data.num = atoi(param);
                printf("%d: %d\n", check, atoi(param));
                DNode *newDNode = (DNode *) malloc(sizeof(DNode));
                curDNode->next = newDNode;
                curDNode = newDNode;
                DC++;
            }

        }

    }

}

/*get a var diveded by commas */
void getVar() {
    skipWhite();
    sscanf(p, "%[^,]", param);
    skipWhite();
    pointAfterParam();
}

/*checks if has comma ot not or have multiple commas*/
bool checkComma() {
    /*if got two vars with no comma to sparate between them*/
    char check1[MAX_LENGTH];
    char check2[MAX_LENGTH];
    int counter = 0;
    if (sscanf(param, "%s %s", check1, check2) > 1) {
        printf("Missing comma\n");
        return false;
    }
    skipWhite();


    /*check if the first letter (after skipWhite is a comma and looks for multiple commas*/
    while (*p == ',') {
        counter++;
        p++;
        skipWhite();
    }
    /*missing comma*/
    if (counter == 0) {
        printf("Missing comma\n");
        return false;
        /*more then one comma*/
    } else if (counter > 1) {
        printf("Multiple consecutive commas\n");
        return false;
    }
    return true;

}

/*adds to sign table*/
void addSign(char label[50], char character[50], int value) {

    strcpy(curSNode->sign.label, label);
    curSNode->sign.value = (value);
    strcpy(curSNode->sign.car, character);

    SNode *newSNode = (SNode *) malloc(sizeof(SNode));
    curSNode->next = newSNode;
    curSNode = newSNode;

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
/*checks of its a lable to turn on label flag*/
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

/*points pointer p after white space*/
void skipWhite() {
    while (isspace(*p))
        p++;
}

