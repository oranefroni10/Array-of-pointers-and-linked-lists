#include "Header.h"
#include "Implementation.c"

int main()
{
    manot*headmanot=NULL;
    table*arr = NULL;
    FILE*in;
    /*open the files*/
    in = fopen("Manot.txt","r");
    if (in==NULL)
    {
        printf("file didnt open");
        return 1;
    }
    FILE*inst;
    inst = fopen("Instructions.txt","r");
    if (inst==NULL)
    {
        printf("file didnt open");
        return 1;
    }
    FILE*Out;
    Out = fopen("Out.txt","w");
    if (Out==NULL)
    {
        printf("file didnt open");
        return 1;
    }
    /*operate the functions using Getfile function and gets the array*/
    arr = Getfile(inst,in,headmanot,arr,Out);
    /*free al the memory allocations*/
    Freememory(&headmanot,arr);
    /*close all the files*/
    fclose(in);
    fclose(inst);
    fclose(Out);
    return 0;
}
