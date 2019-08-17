
#ifndef ERRFAILS_H
#define ERRFAILS_H
#include <stdio.h>

typedef enum {
    ERROR_MEMORY,
    ERROR_UNDO_MOVE,
    ERROR_COMMAND,
    ERROR_NULL,
    ERROR_FSAVE,
    ERROR_FLOAD,
    ERROR_RESTART
} ERROR;


void PrintError(ERROR error,char* f_name, int num);


#endif
