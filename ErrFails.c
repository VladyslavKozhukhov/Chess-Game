
#include "ErrFails.h"

void PrintError(ERROR error,char* f_name, int num){//Prints kinds of errors

    switch(error){
        case(ERROR_COMMAND): printf("ERROR: invalid command\n");
            break;
        case(ERROR_MEMORY): printf("ERROR: %s has failed\n",f_name);
            break;
        case(ERROR_FSAVE): printf("File can not be created or modified\n");
            break;
        case(ERROR_FLOAD): printf("ERROR: File does not exist or cannot be opened\n");
            break;
        case(ERROR_NULL):printf("ERROR: there was a case of null pointer exception\n");
            break;
        case(ERROR_UNDO_MOVE): printf("Empty history, move cannot be undone\n");
            break;
        default:;
    }
}
