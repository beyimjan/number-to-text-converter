#include <ctype.h>
#include <stddef.h>
#include <stdio.h>

/* Searches for a number in a string. If the number is found, it returns 1;
 * otherwise, it returns 0. Leading and trailing whitespace are allowed.
 * If the string contains invalid characters, it will return 0. */
int search_number_in_string(const char *str, char **start, char **end)
{
    *start = NULL;

    if(!*str)
        return 0; /* Empty string */

    for(; isspace(*str); str++)
        { } /* Skip leading whitespace characters */

    for(; isdigit(*str); str++)
        if(!*start) {
            *start = str;
            *end = str;
        } else {
            *end = str;
        }

    for(; *str; str++)
        if(!isspace(*str))
            return 0; /* String has non-whitespace character after digits */

    return *start != NULL;
}

void print_number_as_words(const char *str)
{
    /* Not implemented */
}

int main(int argc, char *argv[]) {
    int is_valid_string;
    char *number_start, *number_end;

    if(argc < 2) {
        puts("Too few arguments");
        return 1;
    }

    is_valid_string =
        search_number_in_string(argv[1], &number_start, &number_end);
    if(is_valid_string)
        puts("Ok");
    else
        puts("Something went wrong");

    return 0;
}
