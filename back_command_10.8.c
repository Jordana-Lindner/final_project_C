#define TOTAL_OP 16
/*struc for operatons table*/
typedef struct{
    int opcode;
    int func;
    char *opName;
    int *sourceMeth;
    int *targMeth;
    int oprndN;
}op;

int IC =100;


typedef struct{
    int adress;
    int ICval;
    int binCode[72];
    char *opName;
    char *opLabel;
    
}Code;

typedef struct CNode {
    Code code;
    struct CNode * next;
}CNode;

CNode* Chead ;



void fillin_op_table();

int opCode[TOTAL_OP]={0,1,2,3,4,5,5,5,5,9,9,9,12,13,14,15}; 
char allOp[TOTAL_OP][4]={"mov","cmp","add", "sub", "lea","clr", "not", "inc", "dec", "jmp", "bne", "jsr", "red", "prn", "rts", "stop"};
int func[TOTAL_OP]={0,0,1,2,0,1,2,3,4,1,2,3,0,0,0,0};
int sourceMeth[TOTAL_OP][3]={{0,1,3},{0,1,3},{0,1,3},{0,1,3},{1}};
int targMeth[TOTAL_OP][3]={{1,3},{0,1,3},{1,3},{1,3},{1,3},{1,3},{1,3},{1,3},{1,3},{1,3},{1,3},{1,3},{1,3},{1,3}};
int oprndN[TOTAL_OP]= {2,2,2,2,2,1,1,1,1,1,1,1,1,1,0,0};
int i;


op opTable[16];

//bool validat_command(

void fillin_op_table(){
  int i;
  for(i=0; i<TOTAL_OP; i++){
    opTable[i].opName= allOp[i];
    opTable[i].opcode= opCode[i];
    opTable[i].func= func[i]; 
    opTable[i].sourceMeth=sourceMeth[i];
    opTable[i].targMeth=targMeth[i];;
    opTable[i].oprndN = oprndN[i]
    }
  }
  
  
int validate_command(char *opcode){
  for(i=0; i<TOTAL_OP; i++){
    if(!(strcmp(opcode,opTable[i].opName))){
        return i;
    }
  }
  return -1;
}


void get_souceOP(opInd,sourceOP,targOP){
  
  char *  itoa ( int value, char * str, int base );
  if (sourceOP[0] == 35)
  {
     int num = atoi(*(sourceOP+1));
     
     
    
     
  
void dec_to_binary(int decNum) 
{ 
    // array to store binary number 
    int binaryNum[24]; 
  
    // counter for binary array 
    int i = 0; 
    while (decNum > 0) { 
  
        // storing remainder in binary array 
        binaryNum[i] = decNum % 2; 
        decNum = decNum / 2; 
        i++; 
    } 
    // printing binary array in reverse order 
    for (int j = i - 1; j >= 0; j--) 
        cout << binaryNum[j]; 
} 


void get_opcode(char *opcode){
  char *sourceOP=null, *targOP=null; *nonValOP;
  if(opInd=validate_command(opcode)!=-1)
  {
    if (opTable[opInd].oprndN ==2){
      }  
    getParam();
    strcpy(sourceOP, param);
    getParam();
    strcpy(targOP, param);
    getParam();
    strcpy(nonValOP, param);
      if (sourceOP && targOP && !nonValOP)
      {
         if (labelFlag)
         {
           addSign(label, "code", IC);
           strcpy(curCNode ->opLabel,label);
         }
      }  
      else 
      {
        printf("The command %s you entered requires exactly two operands, a non valid number of operands was found %s", opcode); 
      }
  }
  else {
    printf("The command %s entered is not valid, Please eneter a valid command", opcode); 
  }




//only for testing the above functions 
int main(){
  int i;
  fillin_op_table();
  for(i = 0; i<TOTAL_OP; i++)
  {
   //printf("%d \n", opTable[i].opcode);
   printf("%s \n", opTable[i].opName);
   //printf("%d \n", opTable[i].func);
   printf("%d \n", opTable[i].sourceMeth[0]);   
  }
   printf("\n\n\n %d", validate_command("lll"));
   
    chead = (CNode *) malloc(sizeof(CNode));
    curCNode = chead;

   return 0;

}