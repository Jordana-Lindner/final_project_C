
#include "FirstRun.h"

int opCode[TOTAL_OP]={0,1,2,3,4,5,5,5,5,9,9,9,12,13,14,15};
char allOp[TOTAL_OP][4]={"mov","cmp","add", "sub", "lea","clr", "not", "inc", "dec", "jmp", "bne", "jsr", "red", "prn", "rts", "stop"};
int func[TOTAL_OP]={0,0,1,2,0,1,2,3,4,1,2,3,0,0,0,0};
int sourceMeth[TOTAL_OP][4]={{0,1,-1,3},{0,1,-1,3},{0,1,-1,3},{0,1,-1,3},{-1,1,-1,-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1}};
int targMeth[TOTAL_OP][4]={{-1,1,-1,3},{0,1,-1,3},{-1,1,-1,3},{-1,1,-1,3},{-1,1,-1,3},{-1,1,-1,3},{-1,1,-1,3},{-1,1,-1,3},{-1,1,-1,3},{-1,1,2,-1},{-1,1,2,-1},{-1,1,2,-1},{-1,1,-1,3},{0,1,-1,3},{-1},{-1}};
int oprndN[TOTAL_OP]= {2,2,2,2,2,1,1,1,1,1,1,1,1,1,0,0};

/*start first run */
void firstRun() {

    /*new heads for linked lists */
    sHead = (symboleTabel *) malloc(sizeof(symboleTabel));
    curSNode = sHead;
    curSNode->sign.label[0] = '\0';
    dHead = (dataNode *) malloc(sizeof(dataNode));
    curDNode = dHead;
    Chead = (CNode *) malloc(sizeof(CNode));
    curCNode = Chead;
    //curCNode-> code.binCode[25]='\0';
    fillin_op_table();
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
                    if (inLabelTab(label))
                        continue;
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
    if (!isascii(*p)) { //maybe needs to be changed to isascii
        printf("missing char\n");
        return;
    }
    /*while not end of line or end of string*/
    while (*p != '\0' && *p != '\"') {

        /*adds the char to data linked list*/
        curDNode->data.ch = *p;
        dataNode *newDNode = (dataNode *) malloc(sizeof(dataNode));

        printf("%d: %c\n",check ,curDNode->data.ch);

        curDNode->next = newDNode;
        curDNode = newDNode;

        DC++;
        p++;
        skipWhite();
        check++;
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

    p++;
    skipWhite();
    if (*p != '\0'){
        printf("extra input after .string\n");

        return;
    }

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
    /*if no data after comma*/
    if (*p == '\0'){
        printf("Missing Data after comma\n");
        return false;
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

    if (inLabelTab(label)) {
    printf("This label is alradey decalared");
    return;
    }

    strcpy(curSNode->sign.label, label);
    curSNode->sign.value = (value);
    strcpy(curSNode->sign.car, character);

    symboleTabel *newSNode = (symboleTabel *) malloc(sizeof(symboleTabel));
    curSNode->next = newSNode;
    curSNode = newSNode;
    curSNode->sign.label[0] = '\0';

}

//bool validat_command(

void fillin_op_table(){
    int i;
    for(i=0; i<TOTAL_OP; i++){
        opTable[i].opName= allOp[i];
        opTable[i].opcode= opCode[i];
        opTable[i].func= func[i];
        opTable[i].sourceMeth=sourceMeth[i];
        opTable[i].targMeth=targMeth[i];
        opTable[i].oprndN = oprndN[i];
    }
}


int validate_command(char *opcode){
    int i;
    for(i=0; i<TOTAL_OP; i++){
        if(!(strcmp(opcode,opTable[i].opName))){
            printf("the command %s is valid\n", opcode);
            return i;
        }
    }
    return -1;
}

int check_non_white_char(char *str){
    int i=0;
    while (str[i] != '\0')
    {
        if (!isspace(str[i]))
        {
            return 0;
        }
        i++;
    }
    return 1;
}

int check_register_meth3(char *OP){
    if(OP[0] == 114 && isdigit(OP[1]))
    {
        if (atoi(OP+1)<0 || atoi(OP+1)>7)
            return 0;
        if (strlen(OP) > 2 && !check_non_white_char(OP+2))
            return 0;
    }
    else
        return 0;
    return 1;
}


int check_label(char *OP) {
    int length = strlen(OP);
    if (!isalpha(*OP))//*param < 'A' || (*param > 'Z' && *param < 'a') || *param > 'z')
        return 0;
    if (length > 1)
    {
        if (length >31)
        {
            printf("Label is too long\n");
            return 0;
        }
        if (isGuide(OP) || validate_command(OP)==-1 || check_register_meth3(OP))
        { /*need - or command or register or already is a label*/
            printf("invalid label name \n");
            return 0;
        }
    }
    return 1;
}




int check_int_meth0(char *OP, long *num){
    if (isdigit(OP[1]) || OP[1]== 45)
    {
        int i=0;
        char *ptr;
        *num = strtol(OP+1, &ptr, 10);
        if (!check_non_white_char(ptr))
        {
            printf("invlid integer, found non- numbers %s characters\n", ptr);
            return 0;

        }
        int min = (pow(2, 21) / 2) * -1;
        int max = (pow(2, 21) / 2) -1;
        if (*num > max)
        {
            printf("the number you enetered is too big %ld\n", *num);
            return 0;
        }
        if (*num < min)
        {
            printf("the number you enetered is too small %ld\n", *num);
            return 0;
        }
    }
    else{
        return 0;}
    return 1;
}





// Convert an integer to binary (in a string)
void int2bin(int integer, char* binary, int n)
{
    int i;
    for (i=0;i<n;i++)
        binary[i] = (integer & (int)1<<(n-i-1)) ? '1' : '0';
    //binary[n]='\0';
    printf("this is the binary code inside int2bin %s\n", binary);
}

void fillin_BinOP(int funN, int opcodeN)

{
    char function [5]={"0"};
    char opcode [6]={"0"};
    int2bin(funN,function,5);
    int2bin(opcodeN,opcode,6);
    printf("this is the binary code of func %s \n", function);
    printf("this is the binary code of opcode %s \n", opcode);
    strcpy(curCNode ->  code.binCode+3,function);
    strcpy(curCNode ->  code.binCode+18,opcode);
    printf("the binary code of the first word after opcode command is %s \n", curCNode ->  code.binCode);
    curCNode -> code.adress=IC;
    strcpy(curCNode ->  code.binCode+2,"1");
    printf("the binary code of the first word command is %s \n", curCNode ->  code.binCode);

    if (labelFlag)
        strcpy(curCNode -> code.opLabel,label);
        printf("the label of the command is %s\n", curCNode -> code.opLabel);

}


void fillin_firstBinCode(int methCode, int regNum, int methInd, int regInd)
{
    char methC[2], regN[3];
    int2bin(regNum,regN,3);
    strcpy(curCNode ->  code.binCode+regInd,regN);
    int2bin(methCode,methC,2);
    printf ("this is the output of int2bin for thr method code %s\n",methC );
    printf ("this is the output of int2bin for thr register code num %s\n", regN );
    strcpy(curCNode ->  code.binCode+methInd,methC);
    printf("the binary code of the first word after adding the rg and method command is %s \n", curCNode ->  code.binCode);
}

void fillin_extraBinCode(int num)
{
    char binary[21];
    int2bin(num,binary,21);
    IC++;
    CNode *newCNode = (CNode *) malloc(sizeof(CNode)); // set new node for int adress
    curCNode->next = newCNode;
    curCNode = newCNode;
    curCNode -> code.adress = IC;
    strcpy(curCNode ->  code.binCode+3,binary); // complete the rest of the binary code
    printf("the binary code of extra word command is %s \n", curCNode ->  code.binCode);
}

void get_operand(int opInd, char *OP, int *meth, int methInd, int regInd){
    int i;
    if (strlen(OP) >= 2)
    {
        if (OP[0] == 35 && meth[0]==0)// direct method (number 0) for int operands
        {
            long num;
            if (check_int_meth0(OP,&num))
            {
                printf("the operand %s is valid for %d method of command %s \n", OP ,meth[0],opTable[opInd].opcode);
                fillin_firstBinCode(0,0,methInd, regInd);
                fillin_extraBinCode(num);
                strcpy(curCNode ->  code.binCode+2,"1"); //set A=1 in in the ARE
            }
            else //operand started with # and no valid int was written after it
                return;
        }
        else if(check_register_meth3(OP) && meth[3]==3) // method for register operands (number 3)
        {
            printf("the operand %s is valid for %d method of command %s \n", OP ,meth[0],opTable[opInd].opcode);
            fillin_BinOP(3,atoi(OP+1));
        }
        else if(OP[0] == 38 && meth[2]==2) //relative method (number 2)
        {
            if (check_label(OP+1))
            {
                printf("the operand %s is valid for %d method of command %s \n", OP ,meth[0],opTable[opInd].opcode);
                fillin_firstBinCode(2,0,methInd, regInd);
                fillin_extraBinCode(0);
                strcpy(curCNode -> code.operandLabel, OP+1);
                strcpy(curCNode ->  code.binCode+2,"1"); //set A=1 in in the ARE
            }
            else
                return; //operand started with & and no valid label was written after it
        }
        else
        {
            if (check_label(OP) && meth[1]==1)
            {
                printf("the operand %s is valid for %d method of command %s \n", OP ,meth[0],opTable[opInd].opcode);
                fillin_firstBinCode(1,0,methInd, regInd);
                fillin_extraBinCode(0);
                strcpy(curCNode -> code.operandLabel, OP+1);
            }
            else
                printf("The input command %s can't be applied with the selected sorce operand %s\n", opTable[opInd].opName, OP);
        }
    }
    else
    {
        if (check_label(OP) && meth[1]==1)
        {
            printf("the operand %s is valid for %d method of command %s \n", OP ,meth[0],opTable[opInd].opcode);
            fillin_firstBinCode(1,0,methInd, regInd);
            fillin_extraBinCode(0);
            strcpy(curCNode -> code.operandLabel, OP+1);
        }
        else
            printf("The input command %s can't be applied with the selected sorce operand %s\n", opTable[opInd].opName, OP);
    }
}




int check_non_valOP(char *nonValOP)
{
    if (nonValOP[0] == '\0')
        return 1;
    else
    {
        printf("A non valid number of operands was found extra operand %s was found\n", nonValOP);
        return 0;
    }
}


void get_opcode(char *opcode) {
    char sourceOP[MAX_LENGTH] ={'\0'}, targOP[MAX_LENGTH]={'\0'}, nonValOP[MAX_LENGTH]={'\0'};
    int opInd;
    char Code[MAX_LENGTH];
    strcpy(Code, opcode);

    if ((opInd = validate_command(Code)) != -1) {
        printf ("the index of the command %s is %d\n",Code,opInd);
        if (opTable[opInd].oprndN == 2) {
            getParam();
            strcpy(sourceOP, param);
            printf("this is the source operand %s of the command %s\n", sourceOP,Code);
            getParam();

            strcpy(targOP, param);
            printf("this is the targ operand %s of the command %s\n", targOP,Code);
            //getParam();//check if p is EOF

           //strcpy(nonValOP, param);

            if (sourceOP[0] != '\0' && targOP[0] != '\0'){//&& check_non_valOP) {
                fillin_BinOP(opTable[opInd].func, opTable[opInd].opcode);
                get_operand(opInd, sourceOP, opTable[opInd].sourceMeth, 16, 13);
                get_operand(opInd, targOP, opTable[opInd].targMeth, 11, 8);
            }
        } else if (opTable[opInd].oprndN == 1) {
            getParam();
            strcpy(targOP, param);
            printf("this is the targ operand %s of the command %s\n", targOP,Code);
            //getParam();
            //strcpy(nonValOP, param);
            if (targOP[0] != '\0'){ //&& check_non_valOP) {
                fillin_BinOP(opTable[opInd].func, opTable[opInd].opcode);
                get_operand(opInd, targOP, opTable[opInd].targMeth, 11, 8);

            }
        } else if (opTable[opInd].oprndN == 0) {
            //getParam();
            //strcpy(nonValOP, param);
            //if (check_non_valOP)
            printf("no targ operand of the command %s\n", Code);
                fillin_BinOP(opTable[opInd].func, opTable[opInd].opcode);
        }
    } else {
        printf("The command %s entered is not valid, Please eneter a valid command \n", Code);
        return;
    }
    CNode *newCNode = (CNode *) malloc(sizeof(CNode)); // set new node for int adress
    curCNode->next = newCNode;
    curCNode = newCNode;
    curCNode-> code.binCode[25]='\0';
    IC++;

}
