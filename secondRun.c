#include "secondRun.h"

void secondRun() {
    fseek(fp, 0, SEEK_SET);
    while (fgets(line, MAX_LENGTH, fp)) {
        p = line;
        getParam();
        if(isLabel(param))
            getParam();
        switch (isGuide(param)){
            case 4:{

            }break;
        }
    }
}
