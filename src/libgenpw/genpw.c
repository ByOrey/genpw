#include "genpw.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

static const CharSets sets
        = {.digits = "0123456789",
           .lowercase = "abcdefghijklmnopqrstuvwxyz",
           .uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
           .special = "!@#$%^&*()-_=+[]{}|;:,.<>/?"};