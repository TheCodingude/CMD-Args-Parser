# Basic Library for working with command line arguments for C/C++



## How to Use

Before you include it you must define `CMD_ARGS_IMPLEMENTATION` like so: 

```c
#define CMD_ARGS_IMPLEMENTATION
```

then you can include as normal

<hr>

Now before you do anything you need to make an Args structure like so:

```c
Args args = {.argc = argc, .argv = argv};
```

Each function takes a pointer to these arguements


<hr>

## Functions

### expect_bool(pointer_to_args): expects `true` or `false` and nothing else. 

Looks like this:
```c
bool result = expect_bool(&args);
```

### expect_int(pointer_to_args): expects an integer value 

looks like this:
```c
int result = expect_int(&args);
```

### expect_float(pointer_to_args): expects a float value 

looks like this:
```c
float result = expect_float(&args);
```

### expect_string(pointer_to_args, expected_string): expects a string value and can compare with an expected string. 

put `NULL` if no particular string is needed

looks like this:
```c
char* result = expect_string(&args, NULL);
```


### expect_filepath(pointer_to_args, should_exist): expects a filepath, If the second parameter is set to `true` then it will check if the file exists 

looks like this:
```c
char* result = expect_filepath(&args, true);
```


### expect_flag(pointer_to_args, expected_flag): basically the same as `expect_string()` but this one checks for a '-' in front  

looks like this:
```c
char* result = expect_flag(&args, "-thing");
```