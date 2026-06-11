#ifndef OPTIONS_H
#define OPTIONS_H

struct argument_conditions_options {
    int flags;
    int conditions;
    const char *pattern;
};
typedef struct argument_conditions_options arg_CO;

extern arg_CO arg_manager;

extern enum option_flags {
    IGNORE_CASE     = 01,
    INVERT_MATCH    = 02,
    LINE_NUMBERS    = 04,
    COUNT_MATCHES   = 010,
    ERROR_O         = 020
};

extern enum condition_flags {
    GIVEN_PATTERN   = 01,
    GIVEN_OPTION    = 02,
    GIVEN_FILES     = 04,
    ERROR_C         = 020
};

int check_condition(int argument_count, char *arguments[]);
void read_flags();
int check_options(char *arguments);
int check_file(char *filename);

#endif