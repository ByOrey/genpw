#include "genpw.h"
#include <stdio.h>
#include <stdlib.h>
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

int generate_password(
        int length,
        bool include_digits,
        bool include_lower,
        bool include_upper,
        bool include_special,
        char* password_buffer,
        size_t buffer_size)
{
    if (length < 4) {
        return 1; // Недопустимая длина
    }
    if (buffer_size < (size_t)(length + 1)) {
        return 2; // Недостаточный размер буфера
    }

    // Собираем выбранные наборы символов
    const char* active_sets[4];
    int active_count = 0;

    if (include_digits)
        active_sets[active_count++] = sets.digits;
    if (include_lower)
        active_sets[active_count++] = sets.lowercase;
    if (include_upper)
        active_sets[active_count++] = sets.uppercase;
    if (include_special)
        active_sets[active_count++] = sets.special;

    // Или используем все наборы
    if (active_count == 0) {
        active_sets[0] = sets.digits;
        active_sets[1] = sets.lowercase;
        active_sets[2] = sets.uppercase;
        active_sets[3] = sets.special;
        active_count = 4;
    }

    char password[length + 1];
    int pos = 0;

    // Включаем по одному символу из каждого набора
    for (int i = 0; i < active_count; i++) {
        password[pos++] = get_random_char(active_sets[i]);
    }

    while (pos < length) {
        int set_index = rand() % active_count;
        password[pos++] = get_random_char(active_sets[set_index]);
    }

    // Рандомизируем пароль
    for (int i = length - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char tmp = password[i];
        password[i] = password[j];
        password[j] = tmp;
    }

    password[length] = '\0';
    strcpy(password_buffer, password);

    return 0;
}