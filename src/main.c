#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

enum { max_digits_count = 18 };

enum number_name {
    nn_unit, nn_teen, nn_ten, nn_hundred,
    nn_thousand, nn_million, nn_billion, nn_trillion, nn_quadrillion
};

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
        list->last = tmp;
    } else {
        list->first = tmp;
        list->last = tmp;
    }
}

static void number_sll_get(struct number_sll *list,
    const char *start, const char *end)
{
    for(; 3 <= end - start && end - start < 18; start += (end - start) % 3 + 1)
    {
        const char *limit = start + (end - start) % 3;
        for(; *start == '0' && start < limit; start++)
            { }

        if(*start == '0')
            continue;

        number_sll_get(list, start, start + (end - start) % 3);
        if(3 <= end - start && end - start < 6)
            number_sll_push(list, 0, nn_thousand);
        else if(6 <= end - start && end - start < 9)
            number_sll_push(list, 0, nn_million);
        else if(9 <= end - start && end - start < 12)
            number_sll_push(list, 0, nn_billion);
        else if(12 <= end - start && end - start < 15)
            number_sll_push(list, 0, nn_trillion);
        else if(15 <= end - start && end - start < 18)
            number_sll_push(list, 0, nn_quadrillion);
    }

    if(2 == end - start) {
        if(*start != '0') {
            number_sll_push(list, *start - '0', nn_unit);
            number_sll_push(list, 0, nn_hundred);
        }
        start++;
    }

    if(1 == end - start) {
        if(*start == '1') {
            start++;
            number_sll_push(list, *start - '0', nn_teen);
            return;
        } else if(*start != '0') {
            number_sll_push(list, *start - '0', nn_ten);
            start++;
            if(*start == '0')
                return;
        } else {
            start++;
            if(*start == '0')
                return;
        }
    }

    if(0 == end - start)
        number_sll_push(list, *start - '0', nn_unit);
}

static void number_sll_print_as_words(const struct number_sll *list)
{
    struct number_item *tmp;
    for(tmp = list->first; tmp; tmp = tmp->next) {
        switch (tmp->name)
        {
        case nn_quadrillion:
            fputs("quadrillion", stdout);
            break;
        case nn_trillion:
            fputs("trillion", stdout);
            break;
        case nn_billion:
            fputs("billion", stdout);
            break;
        case nn_million:
            fputs("million", stdout);
            break;
        case nn_thousand:
            fputs("thousand", stdout);
            break;
        case nn_hundred:
            fputs("hundred", stdout);
            break;
        case nn_ten:
            fputs(tens[tmp->number], stdout);
            break;
        case nn_teen:
            fputs(teens[tmp->number], stdout);
            break;
        case nn_unit:
            fputs(units[tmp->number], stdout);
            break;
        }

        if(tmp->next)
            putchar(' ');
    }
    putchar('\n');
}

/* Searches for a number in a string. If the number is found, it returns 1;
 * otherwise, it returns 0. Leading and trailing whitespace are allowed.
 * Leading zeros are skipped. If the number length exceeds the
 * `max_digit_count` constant, it returns 0.
 * If the string contains invalid characters, it returns 0. */
static int search_number_in_string(const char *str, char **start, char **end)
{
    *start = NULL;

    if(!*str)
        return 0; /* Empty string */

    for(; isspace(*str); str++)
        { } /* Skip leading whitespace characters */

    for(; isdigit(*str); str++)
        if(!*start || **start == '0') {
            *start = str;
            *end = str;
        } else {
            *end = str;
        }

    for(; *str; str++)
        if(!isspace(*str))
            return 0; /* String has non-whitespace character after digits */

    return *start != NULL && *end - *start < max_digits_count;
}

int main(int argc, char *argv[]) {
    int is_valid_string;
    char *number_start, *number_end;

    if(argc < 2) {
        fputs("Too few arguments\n", stderr);
        return 1;
    }

    is_valid_string =
        search_number_in_string(argv[1], &number_start, &number_end);
    if(is_valid_string) {
        struct number_sll number_list;
        number_sll_init(&number_list);
        number_sll_get(&number_list, number_start, number_end);
        number_sll_print_as_words(&number_list);
        number_sll_delete(&number_list);
    } else {
        fputs("Something went wrong\n", stderr);
    }

    return 0;
}
