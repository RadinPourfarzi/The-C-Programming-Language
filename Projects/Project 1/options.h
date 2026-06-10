#ifndef OPTIONS_H
#define OPTIONS_H

extern enum option_flags {
    IGNORE_CASE     = 01,
    INVERT_MATCH    = 02,
    LINE_NUMBERS    = 04,
    COUNT_MATCHES   = 010,
    ERROR           = 020
};

int check_options(char *arguments);
int check_file(char *filename);

#endif