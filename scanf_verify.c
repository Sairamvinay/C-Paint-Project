#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include "scanf_verify.h"

/*
 * Calls scanf, verifying that input is valid
 * format: the format string to pass to scanf
 * ...: further arguments to scanf
 * Return true if successful, false otherwise.
*/
bool scanf_verify(char *format, ...) {
    va_list args;
    int i, num_args=0;
    bool success=true;

    // Count specifiers in format string
    // Note: assumes all % symbols a format specifiers (not escaped)
    for (i=0; i < strlen(format); i++) {
        if (format[i] == '%')
            num_args++;
    }

    va_start(args, format);
    if (vscanf(format, args) != num_args)
        success = false;
    va_end(args);
    success = correct_input(success);

    return success;
}


/*THIS FUNCTION IS USED TO VERIFY WHETHER THE INPUT IS CORRECT OR NOT
@PARAMETER: A BOOL VALUE TO CHECK WHETHER THE INPUT IS CORRECT OR NOT
@RETURNS: THE SAME BOOL VARIABLE
*/
bool correct_input(bool success){
    
    char next_char;   
    // Input may be followed by any amount of whitespace, then newline
    do {
        next_char = getchar();
        if (!isspace(next_char))
            success = false;
    } while (next_char != '\n');
    
    return success;
}
