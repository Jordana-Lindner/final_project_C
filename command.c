/*

#include "FirstRun.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include "main.h"

#define TOTAL_OP 16

void get_opcode(char *opcode);

*/
/*struc for operatons table*//*

typedef struct{
    int opcode;
    int func;
    char *opName;
    int *sourceMeth;
    int *targMeth;
    int oprndN;
}op;



typedef struct{
    int adress;
    int ICval;
    char binCode[24];
    char *opName;
    char *opLabel;
    char *operandLabel;
    
}Code;

typedef struct CNode {
    Code code;
    struct CNode * next;
}CNode;

CNode* Chead ;
CNode *curCNode;

//functions that will have to be removed - just for testing 


*/
/*gets parameter from line*//*

void getParam() {
    skipWhite();
    sscanf(p, "%s", param);
    skipWhite();
    pointAfterParam();
}


*/
/*move pointer after last parameter*//*

void pointAfterParam() {
    p += strlen(param);
}

*/
/*points pointer p after white space*//*

void skipWhite() {
    while (isspace(*p))
        p++;
}

*/
/*if its a guide command*//*

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



*/
/*checks of its a lable to turn on label flag*//*

bool isLabel(char param[50]) {

    int length = strlen(param);
    if (!isalpha(*param))//*param < 'A' || (*param > 'Z' && *param < 'a') || *param > 'z')
        return 0;
    if (length > 1 && param[length - 1] == ':') {
        if (length >31){
            printf("to long to be a label\n");
            return 0;
        }
        if (isGuide(param)){ */
/*need - or command or register or already is a label*//*

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


*/
/*start first run *//*

void firstRun() {
    */
/*new heads for linked lists *//*


    */
/*while file has a line*//*

    while (fgets(line, MAX_LENGTH, fp)) {
        */
/*points to first letter in line*//*

        p = line;
        if (*p == ';'){
            continue;
        }
        getParam();
        */
/*turn on flag if there is a sign*//*

        printf("this is the param %s \n", param);
        labelFlag = isLabel(param);
        */
/*gets next param*//*

        if (labelFlag) {
            getParam();
        }
        else
          get_opcode(param);

        }
*/
/*go over symbolTabel and add 100 to value*//*


    }


///


int opCode[TOTAL_OP]={0,1,2,3,4,5,5,5,5,9,9,9,12,13,14,15}; 
char allOp[TOTAL_OP][4]={"mov","cmp","add", "sub", "lea","clr", "not", "inc", "dec", "jmp", "bne", "jsr", "red", "prn", "rts", "stop"};
int func[TOTAL_OP]={0,0,1,2,0,1,2,3,4,1,2,3,0,0,0,0};
int sourceMeth[TOTAL_OP][4]={{0,1,-1,3},{0,1,-1,3},{0,1,-1,3},{0,1,-1,3},{-1,1,-1,-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1},{-1}};
int targMeth[TOTAL_OP][4]={{-1,1,-1,3},{0,1,-1,3},{-1,1,-1,3},{-1,1,-1,3},{-1,1,-1,3},{-1,1,-1,3},{-1,1,-1,3},{-1,1,-1,3},{-1,1,-1,3},{-1,1,2,-1},{-1,1,2,-1},{-1,1,2,-1},{-1,1,-1,3},{0,1,-1,3},{-1},{-1}};
int oprndN[TOTAL_OP]= {2,2,2,2,2,1,1,1,1,1,1,1,1,1,0,0};

op opTable[16];

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
        return i;
    }
  }
  return -1;
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
        { */
/*need - or command or register or already is a label*//*

          printf("invalid label name \n");
          return 0;
        }
    }
    return 1;
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

int check_int_meth0(char *OP, long *num){
    if (isdigit(OP[1]) || OP[1]== 45)
    {
      int i=0; 
      char *ptr;
      *num = strtol(OP+1, &ptr, 10);
      if (!check_non_white_char(ptr))
       {
         printf("invlid integer, found non- numbers %s characters", ptr);
         return 0;

       }
      int min = (pow(2, 21) / 2) * -1;
      int max = (pow(2, 21) / 2) -1;
      if (*num > max)
        {
          printf("the number you enetered is too big %ld", *num);
          return 0;
        }  
      if (*num < max)
        {
          printf("the number you enetered is too small %ld", *num);
          return 0;
        }  
    }
    else{
      return 0;}  
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


  
// Convert an integer to binary (in a string)
void int2bin(unsigned integer, char* binary, int n)
{  
  int i;
  for (i=0;i<n;i++)   
    binary[i] = (integer & (int)1<<(n-i-1)) ? '1' : '0';
  binary[n]='\0';
}

void fillin_BinOP(int funN, int opcodeN)

{
   char func[5]; 
   char opcode [6];
   int2bin(funN,func,5);
   int2bin(opcodeN,opcode,6);
   strcpy(curCNode ->  code.binCode+3,func);
   strcpy(curCNode ->  code.binCode+18,opcode);
   curCNode -> code.adress=IC;
   strcpy(curCNode ->  code.binCode+2,"1");    
   if (labelFlag)
     strcpy(curCNode -> code.opLabel,label);

}


void fillin_firstBinCode(int methCode, int regNum, int methInd, int regInd) 
{
   char methC[2], regN[3];
   int2bin(regNum,regN,3);
   strcpy(curCNode ->  code.binCode+regInd,regN);
   int2bin(methCode,methC,2);
   strcpy(curCNode ->  code.binCode+methInd,methC);
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
         fillin_firstBinCode(0,0,methInd, regInd);
         fillin_extraBinCode(num);
         strcpy(curCNode ->  code.binCode+2,"1"); //set A=1 in in the ARE
       }  
       else //operand started with # and no valid int was written after it 
          return;
      }
     else if(check_register_meth3(OP) && meth[3]==3) // method for register operands (number 3) 
       {
         fillin_BinOP(3,atoi(OP+1));
       }
     else if(OP[0] == 38 && meth[2]==2) //relative method (number 2)
     {
       if (check_label(OP+1))
       {
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
         fillin_firstBinCode(1,0,methInd, regInd);
         fillin_extraBinCode(0);
         strcpy(curCNode -> code.operandLabel, OP+1);   
       }
       else 
         printf("The input command %s can't be applied with the selected sorce operand %s", opTable[opInd].opName, OP);
     }
  } 
  else
   {
      if (check_label(OP) && meth[1]==1)
       {
         fillin_firstBinCode(1,0,methInd, regInd);
         fillin_extraBinCode(0); 
         strcpy(curCNode -> code.operandLabel, OP+1);    
       }
      else 
         printf("The input command %s can't be applied with the selected sorce operand %s", opTable[opInd].opName, OP);
    } 
  }
   

     

int check_non_valOP(char *nonValOP)
{
  if (nonValOP[0] == '\0')
    return 1;
  else 
    {
      printf("A non valid number of operands was found extra operand %s was found", nonValOP);
      return 0;
    }
}


void get_opcode(char *opcode){
  char *sourceOP, *targOP, *nonValOP;
  int opInd;
  Chead = (CNode *) malloc(sizeof(CNode));
  curCNode = Chead;
  if(opInd=validate_command(opcode)!=-1)
  {
    if (opTable[opInd].oprndN ==2){
      getParam();
      strcpy(sourceOP, param);
      getParam();
      strcpy(targOP, param);
      getParam();
      strcpy(nonValOP, param);
      if (sourceOP[0] != '\0' && targOP[0] != '\0' && check_non_valOP)
        {
        fillin_BinOP(opTable[opInd].func, opTable[opInd].opcode);
        get_operand(opInd, sourceOP, opTable[opInd].sourceMeth, 16, 13);
        get_operand(opInd, targOP, opTable[opInd].targMeth, 11, 8);
        }
      }  
    else if(opTable[opInd].oprndN == 1)
    {
      getParam();
      strcpy(targOP, param);
      getParam();
      strcpy(nonValOP, param);
      if (targOP[0] !='\0' && check_non_valOP)
      {
        fillin_BinOP(opTable[opInd].func, opTable[opInd].opcode);
        get_operand(opInd, targOP, opTable[opInd].targMeth, 11, 8);
        
      }
    }
    else if(opTable[opInd].oprndN == 0)
    {
      getParam();
      strcpy(nonValOP, param);
      if (check_non_valOP)
        fillin_BinOP(opTable[opInd].func, opTable[opInd].opcode);
    }    
  }
  else {
    printf("The command %s entered is not valid, Please eneter a valid command \n", opcode);
    return; }
  CNode *newCNode = (CNode *) malloc(sizeof(CNode)); // set new node for int adress 
  curCNode->next = newCNode;
  curCNode = newCNode;
  IC++;
  }

//to do list: 
//1. add method for negative numbers 
//2. add comma case- ask aviad 
//3. add operand label- done
//4.in the check label function add check to eack character
//5. does the functions get opcode and get operand shold return something incase of success or failure 


//only for testing the above functions 
//int main(){
  //int i;
  //fillin_op_table();
  //for(i = 0; i<TOTAL_OP; i++)
  //{
  //printf("%d \t %s \t %s \n", opTable[i].opcode , opTable[i].opName, opTable[i].func);

  //}
   //printf("\n\n\n %d", validate_command("lll"));


int main(int argc, char* argv[] ) {
    fillin_op_table();
    int i;
    if (argc<2)*/
/*if there is less filenames then expected *//*

        fprintf(stderr, "files are missing\n");
    else {
        printf("HI");
        strcpy(filename, argv[0]);*/
/*copy the name of the file - need to check it *//*

        //for (i = 1; i < argc; i++) {
            strcpy(input,argv[i]);*/
/*copy and add .as to the input*//*

            if(!(fp = fopen(input,"r")))*/
/*file dose not exist*//*

                fprintf(stderr, "File not found\n");
            else{
                firstRun();
                fclose(fp);
            }

        //}
    }
    exit(0);
}

*/
