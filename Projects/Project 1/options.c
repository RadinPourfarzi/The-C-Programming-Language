#include "options.h"
#include <ctype.h>
#include <stdio.h>

arg_CO arg_manager = {0, 0};

void read_flags()
{
    printf("\n\t__Conditions Checking__\n");
    if((arg_manager.conditions & GIVEN_PATTERN) == GIVEN_PATTERN)
        printf("Given Pattern__\n");
    if((arg_manager.conditions & GIVEN_OPTION) == GIVEN_OPTION)
        printf("Given Option(s)__\n");
    if((arg_manager.conditions & GIVEN_FILES) == GIVEN_FILES)
        printf("Given File(s)__\n");

    printf("\n\t__Options Checking__\n");
    if((arg_manager.flags & IGNORE_CASE) == IGNORE_CASE)
        printf("__Ignore Case\n");
    if((arg_manager.flags & INVERT_MATCH) == INVERT_MATCH)
        printf("__Invert Match\n");
    if((arg_manager.flags & LINE_NUMBERS) == LINE_NUMBERS)
        printf("__Line Numbers\n");
    if((arg_manager.flags & COUNT_MATCHES) == COUNT_MATCHES)
        printf("__Count Matches\n");
    
}

int check_condition(int argument_count, char *arguments[])
{
    int index;

    index = 0;
    if(argument_count == 1)
        return (arg_manager.conditions = 0);
    index++;
    if(*arguments[index] != '-') {
        arg_manager.conditions |= GIVEN_PATTERN;
        arg_manager.pattern = arguments[index++];
    }
    if(index >= argument_count)
        return 0;
    if(check_options(arguments[index++]) == ERROR_O) {
        perror("Non proper option!\n");
        return -1;
    }
    if(index >= argument_count)
        return 0;
    if(arg_manager.flags != 0)
        arg_manager.conditions |= GIVEN_OPTION;
    if(check_file(arguments[index]))
        arg_manager.conditions |= GIVEN_FILES;

    return 0;
}

int check_options(char *argument)
{
    char *s;
    
    s = argument;

    if(*s++ != '-')
        return (arg_manager.flags = 0);
    while(*s != '\0') {
        switch(*s) {
            case 'i':
                arg_manager.flags |= IGNORE_CASE;
                break;
            case 'v':
                arg_manager.flags |= INVERT_MATCH;
                break;
            case 'n':
                arg_manager.flags |= LINE_NUMBERS;
                break;
            case 'c':
                arg_manager.flags |= COUNT_MATCHES;
                break;
            default:
                arg_manager.flags |= ERROR_O;
                return arg_manager.flags;
        }
        s++;
    }
    return arg_manager.flags;
}

int check_file(char *filename)
{
    char *s;

    s = filename;
    
    if(s == '\0')
        return 0;
    while(*filename++ != '\0') {
        if(*filename == '.')
            break;
        if(!isalnum((int)(*filename)))
            return 0;
    }
    return 1;
}