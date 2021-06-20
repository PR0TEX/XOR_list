#define _CRT_SECURE_NO_WARNIGS
#include <iostream>
#include <string>
#include "List.h"

using namespace std;

int main() {
    List list;
    char comm[15];
    int x,n=0;
    string temp;
    while(scanf("%s",comm)>0)
    {
        string command=comm;
        x=0;
        if(command.compare("ACTUAL")==0) x=1;
        else if(command.compare("NEXT")==0) x=2;
        else if(command.compare("PREV")==0) x=3;
        else if(command.compare("ADD_BEG")==0) x=4;
        else if(command.compare("ADD_END")==0) x=5;
        else if(command.compare("ADD_ACT")==0) x=6;
        else if(command.compare("DEL_BEG")==0) x=7;
        else if(command.compare("DEL_END")==0) x=8;
        else if(command.compare("DEL_VAL")==0) x=9;
        else if(command.compare("DEL_ACT")==0) x=10;
        else if(command.compare("PRINT_FORWARD")==0) x=11;
        else if(command.compare("PRINT_BACKWARD")==0) x=12;

        switch(x) {
            case 1:
                list.getAct();
                break;
            case 2:
                list.getNext();
                break;
            case 3:
                list.getPrev();
                break;
            case 4:
                scanf("%d",&n);
                list.addNodeBeg(n);
                break;
            case 5:
                scanf("%d",&n);
                list.addNodeEnd(n);
                break;
            case 6:
                scanf("%d",&n);
                list.addNodeAct(n);
                break;
            case 7:
                list.deleteNodeBeg();
                break;
            case 8:
                list.deleteNodeEnd();
                break;
            case 9:
                scanf("%d",&n);
                list.deleteNode(n);
                break;
            case 10:
                list.deleteNodeAct();
                break;
            case 11:
                list.printListF();
                break;
            case 12:
                list.printListB();
                break;
            default:
                return 0;
        }
        if(x==0) return 0;
    }
    return 0;
}
