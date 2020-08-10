#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


// Convert an integer to binary (in a string)
void int2bin(unsigned integer, char* binary, int n)
{  
  int i;
  for (i=0;i<n;i++)   
    binary[i] = (integer & (int)1<<(n-i-1)) ? '1' : '0';
  binary[n]='\0';
}


int main(){

  char bin[21];
  int2bin(48,bin,21);
  printf("48 in bin is: %s \n", bin);
  
  return 0;
  }