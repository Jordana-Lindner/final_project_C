#define TOTAL_OP 16
/*struc for operatons table*/
typedef struct{
    int opcode;
    int func;
    char *opName;
    int *sourceMeth;
    int *targMeth;
}op;

int IC =100;


void fillin_op_table();

int opCode[16]={0,1,2,3,4,5,5,5,5,9,9,9,12,13,14,15}; 
char allOp[16][4]={"mov","cmp","add", "sub", "lea","clr", "not", "inc", "dec", "jmp", "bne", "jsr", "red", "prn", "rts", "stop"};
int func[16]={0,0,1,2,0,1,2,3,4,1,2,3,0,0,0,0};
int sourceMeth[16][3]={{0,1,3},{0,1,3},{0,1,3},{0,1,3},{1}};
int targMeth[16][3]={{1,3},{0,1,3},{1,3},{1,3},{1,3},{1,3},{1,3},{1,3},{1,3},{1,3},{1,3},{1,3},{1,3},{1,3}};
int i;


op opTable[16];

//bool validat_command(

void fillin_op_table(){

  for(i=0; i<TOTAL_OP; i++){
    opTable[i].opName= allOp[i];
    opTable[i].opcode= opCode[i];
    opTable[i].func= func[i]; 
    opTable[i].sourceMeth=sourceMeth[i];
    opTable[i].targMeth=targMeth[i];
    }
  }
  
  
int validate_command(char *inOpName){
  int valid=0;
  for(i=0; i<TOTAL_OP; i++){
    if(!(strcmp(inOpName,opTable[i].opName))){
        return 1;
    }
  }
  return 0;
}

void decToBinary(int decNum) 
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
   return 0;

}