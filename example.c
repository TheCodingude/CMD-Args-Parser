#include <stdio.h>

#define CMD_ARGS_IMPLEMENTATION
#include "ArgParse.h"

int main(int argc, char** argv){

    Args args = {.argc = argc, .argv = argv};

    bool b = expect_bool(&args);
    
    int i = expect_int(&args);
    float f = expect_float(&args);


    char* str = expect_string(&args, "yes");
    char* fp = expect_filepath(&args, true);
    char* flag = expect_flag(&args, NULL);

    return 0;
}