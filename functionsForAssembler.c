
#include "functionsForAssembler.h"


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

/*points pointer p after white space*/
void skipWhite() {
    while (isspace(*p))
        p++;
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