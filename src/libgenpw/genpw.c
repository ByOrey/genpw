#include "genpw.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

static const CharSets sets
        = {.digits = "0123456789",
           .lowercase = "abcdefghijklmnopqrstuvwxyz",
           .uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
           .special = "!@#$%^&*()-_=+[]{}|;:,.<>/?"};

static int get_random_char(const char* charset)
{
    size_t len = strlen(charset);
    if (len == 0)
        return '\0';
    return charset[rand() % len];
}