
#include "FirstRun.h"

/*start first run */
void firstRun() {
    /*new heads for linked lists */
    sHead = (symboleTabel *) malloc(sizeof(symboleTabel));
    curSNode = sHead;
    dHead = (dataNode *) malloc(sizeof(dataNode));
    curDNode = dHead;

    /*while file has a line*/
    while (fgets(line, MAX_LENGTH, fp)) {
        /*points to first letter in line*/
        p = line;
        if (*p == ';'){
            continue;
        }
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
                if(labelFlag){
                    printf("cant put .extern after label");
                    continue;
                }
                getParam();
                if (*param == '\n')
                {
                    printf("missing extern label");
                    continue;
                }
                addSign(param, "external", 0);
            }
                break;
            default: {
                if (labelFlag) {
                    addSign(label, "code", IC);
                }
                get_opcode(param);
            }
                break;
        }
/*go over symbolTabel and add 100 to value*/

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
        dataNode *newDNode = (dataNode *) malloc(sizeof(dataNode));

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
    dataNode *newDNode = (dataNode *) malloc(sizeof(dataNode));
    curDNode->next = newDNode;
    curDNode = newDNode;
    DC++;

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
    dataNode *newDNode = (dataNode *) malloc(sizeof(dataNode));
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
                dataNode *newDNode = (dataNode *) malloc(sizeof(dataNode));
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

    symboleTabel *newSNode = (symboleTabel *) malloc(sizeof(symboleTabel));
    curSNode->next = newSNode;
    curSNode = newSNode;

}

int validate_command(char *opcode){
    int i;
    for( i=0; i<TOTAL_OP; i++){
        if(!(strcmp(opcode,opTable[i].opName))){
            return i;
        }
    }
    return -1;
}


void get_opcode(char *opcode) {
    int opInd;
    char *sourceOP = NULL, *targOP = NULL, *nonValOP = NULL;
    Chead = (CNode *) malloc(sizeof(CNode));
    curCNode = Chead;
    if (opInd = validate_command(opcode) != -1) {
        if (opTable[opInd].oprndN == 2) {
        }
        getParam();
        strcpy(sourceOP, param);
        getParam();
        strcpy(targOP, param);
        getParam();
        strcpy(nonValOP, param);
        if (sourceOP && targOP && !nonValOP) {

        } else {
            printf("The command %s you entered requires exactly two operands, a non valid number of operands was found %s",
                   opcode);
        }
    } else {
        printf("The command %s entered is not valid, Please eneter a valid command", opcode);
    }
}

    void get_souceOP(int opInd,char * sourceOP){


        if (sourceOP[0] == 35 && opTable[opInd].sourceMeth[0]==0)
        {
            char binary[21];
            int num = atoi(*(sourceOP+1));
            int2bin(num,binary,21);
            strcpy(curCNode -> adress, (strcat(IC,);


            else if(sourceOP[0] == 114 && opTable[opInd].sourceMeth[3]==3)
            {


                else
                {
                    printf("The input command %s can't be applied with the selected sorce operand %s", opTable[opInd].opName, sourceOP);
                }

            }

        }
    }
}
