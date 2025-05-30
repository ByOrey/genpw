#ifndef GENPW_H
#define GENPW_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    const char* digits;
    const char* lowercase;
    const char* uppercase;
    const char* special;
} CharSets;

int generate_password(
        int length,
        bool include_digits,
        bool include_lower,
        bool include_upper,
        bool include_special,
        char* password_buffer,
        size_t buffer_size);

#endif
