#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

enum number_name { nn_units, nn_teens, nn_tens };

struct number_item {
    int number;
    enum number_name name;
    struct number_item *next;
};

struct number_sll {
    struct number_item *first, *last;
};

static const char  *units[] = {
    "zero", "one", "two", "three", "four", "five",
    "six", "seven", "eight", "nine", "ten"
};

static const char *teens[] = {
    "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen",
    "sixteen", "seventeen", "eighteen", "nineteen"
};

static const char *tens[] = {
    "", "", "twenty", "thirty", "forty", "fifty",
    "sixty", "seventy", "eighty", "ninety"
};

static void number_sll_init(struct number_sll *list)
{
    list->first = NULL;
    list->last = NULL;
}

static void number_sll_delete(struct number_sll *list)
{
    while(list->first) {
        struct number_item *tmp = list->first;
        list->first = list->first->next;
        free(tmp);
    }
}

static void number_sll_push(struct number_sll *list,
    int number, enum number_name name)
{
    struct number_item *tmp;
    tmp = malloc(sizeof(*tmp));
    tmp->number = number;
    tmp->name = name;
    tmp->next = NULL;
    if(list->first) {
        list->last->next = tmp;
    } else {
        list->first = tmp;
        list->last = tmp;
    }
}

static void number_sll_get(struct number_sll *list,
    const char *start, const char *end)
{
    for(; *start == '0' && start != end; start++)
        { } /* Skip all leading zeros except the last one */

    if(1 == end - start) {
        if(*start == '1') {
            start++;
            number_sll_push(list, *start - '0', nn_teens);
            return;
        } else {
            number_sll_push(list, *start - '0', nn_tens);
            start++;
            if(*start == '0')
                return;
        }
    }

    if(0 == end - start)
        number_sll_push(list, *start - '0', nn_units);
}

static void number_sll_print(const struct number_sll *list)
{
    struct number_item *tmp;
    for(tmp = list->first; tmp; tmp = tmp->next) {
        switch (tmp->name)
        {
        case nn_tens:
            fputs(tens[tmp->number], stdout);
            break;
        case nn_teens:
            fputs(teens[tmp->number], stdout);
            break;
        case nn_units:
            fputs(units[tmp->number], stdout);
            break;
        }

        if(tmp->name == nn_tens && tmp->next && tmp->next->name == nn_units)
            putchar('-');
        else
            putchar(' ');
    }
    putchar('\n');
}

/* Searches for a number in a string. If the number is found, it returns 1;
 * otherwise, it returns 0. Leading and trailing whitespace are allowed.
 * If the string contains invalid characters, it will return 0. */
static int search_number_in_string(const char *str, char **start, char **end)
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

int main(int argc, char *argv[]) {
    int is_valid_string;
    char *number_start, *number_end;

    if(argc < 2) {
        puts("Too few arguments");
        return 1;
    }

    is_valid_string =
        search_number_in_string(argv[1], &number_start, &number_end);
    if(is_valid_string) {
        struct number_sll number_list;
        number_sll_init(&number_list);
        number_sll_get(&number_list, number_start, number_end);
        number_sll_print(&number_list);
        number_sll_delete(&number_list);
    } else {
        puts("Something went wrong");
    }

    return 0;
}
