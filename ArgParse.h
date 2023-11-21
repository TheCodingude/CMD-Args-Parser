#ifndef CMD_ARGS_H_
#define CMD_ARGS_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int argc;
    char** argv;
} Args;

char* next_arg(Args* args);

bool expect_bool(Args *args);
char* expect_string(Args *args, char* expected);
char* expect_filepath(Args *args, bool exists);
char* expect_flag(Args *args, char* expect_flag);
int expect_int(Args *args);
float expect_float(Args *args);

bool predict_bool(Args *args);
char* predict_string(Args *args, char* expected);
char* predict_filepath(Args *args, bool exists);
char* predict_flag(Args *args, char* expect_flag);
int predict_int(Args *args);
float predict_float(Args *args);



#endif
#ifdef CMD_ARGS_IMPLEMENTATION

void push_back(Args *args){
    args->argc -= 1;
    args->argv += 1;

    if (args->argc == 0){
        fprintf(stderr, "RAN OUT OF ARGUEMENTS TO PROCESS\n");
        exit(1);
    }
}

char* next_arg(Args* args){
    push_back(args);
    return args->argv[0];
}

char* predict_bool(Args *args, bool* result){
    push_back(args);

    if(strcmp(args->argv[0], "true") == 0){
        result = true;
        return NULL;
    } else if(strcmp(args->argv[0], "false") == 0){
        result = false;
        return NULL;
    }else{
        result = NULL;
        return args->argv[0];
    }
}


float expect_float(Args *args){

    push_back(args);

    char* current = args->argv[0];

    bool yes = true;

    for(int i = 0; i < strlen(current); i++){
        if(!isdigit(current[i])){
            if(!(current[i] == '-')){               // there has to be a better way than this, right?
                if(!(current[i] == '.')){
                    yes = false;
                }
            }
        }
    }

    if(yes){
        return (float) atof(current);
    } else{
        fprintf(stderr, "EXPECTED INTEGER BUT GOT SOMETHING ELSE");
        exit(1);
    }

}

int expect_int(Args *args){

    push_back(args);

    char* current = args->argv[0];

    bool yes = true;

    for(int i = 0; i < strlen(current); i++){
        if(!isdigit(current[i])){                         // this too
            if(!(current[i] == '-')){
                yes = false;
            }
        }
    }

    if(yes){
        int i;
        sscanf(current, "%d", &i);
        return i;
    } else{
        fprintf(stderr, "EXPECTED INTEGER BUT GOT SOMETHING ELSE");
        exit(1);
    }

}


bool expect_bool(Args *args){

    push_back(args);

    if(strcmp(args->argv[0], "true") == 0){
        return true;
    } else if(strcmp(args->argv[0], "false") == 0){
        return false;
    } else{
        fprintf(stderr, "Expected Argument of type bool but got something else\n");
        exit(1);

    }
}

char* expect_string(Args *args, char* expected){

    push_back(args);

    if (expected != NULL){
        if(strcmp(args->argv[0], expected) == 0){
            return expected;
        } else{
            fprintf(stderr, "expected a string but a differnt string\n");
            exit(0);
        }
    } else {
        return args->argv[0];
    }
}

char* expect_filepath(Args *args, bool should_exist){

    push_back(args);

    if(should_exist == true){
        FILE *f = fopen(args->argv[0], "r");

        if(f == NULL){
            fprintf(stderr, "File path provided does not exist or could not be found\n");
            exit(1);
        } else{
            fclose(f);
            return args->argv[0];
        }

    } else{
        return args->argv[0];
    }

}

char* expect_flag(Args *args, char* expect_flag){   

    push_back(args);

    if (expect_flag != NULL){
        if(strcmp(args->argv[0], expect_flag) == 0){
            return expect_flag;
        } else{
            fprintf(stderr, "Expected flag but got something else");
            exit(1);
        }
    }else{
        if(args->argv[0][0] == '-'){
            return args->argv[0];
        }else{
            fprintf(stderr, "Expected flag but got something else");
            exit(1);
        }
    }
}

#endif


