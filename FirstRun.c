
#include <stdbool.h>
#include "FirstRun.h"


bool isLabel(char param1[50]);

bool isGuide(char *param);

bool labelFlag =0;
void firstRun(){
    char param1[MAX_LENGTH],param2[MAX_LENGTH],param3[MAX_LENGTH],param4[MAX_LENGTH],*tempParam;

    int check = fscanf(fp, "%s %s %s %s" , param1,param2,param3,param4);
    if(check == 0){}
    else{
        tempParam = param1;
        labelFlag = isLabel(tempParam);
        if(labelFlag)
            tempParam = param2;
        if(isGuide(tempParam)){

        }



    }
}

bool isGuide(char *param) {
    if(strcmp(param,".data"))

    return 0;
}

bool isLabel(char param[50]) {
    int length = strlen(param);
    if(*param < 'A' || (*param>'Z'&&*param<'a')||*param>'z')
        return 0;
    if (length>1 && param[length-1]==':')
        return 1;
    return 0;
}

