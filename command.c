/*#define TOTAL_OP 16
*//*struc for operatons table*//*
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
    char adress[7];
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
CNode *curCNode;*/



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
   
     
     
     
     
     
     
    
     
  
// Convert an integer to binary (in a string)
void int2bin(unsigned integer, char* binary, int n)
{  
  int i;
  for (i=0;i<n;i++)   
    binary[i] = (integer & (int)1<<(n-i-1)) ? '1' : '0';
  binary[n]='\0';
}


void get_opcode(char *opcode){
  char *sourceOP=null, *targOP=null; *nonValOP;
  chead = (CNode *) malloc(sizeof(CNode));
  curCNode = chead;
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