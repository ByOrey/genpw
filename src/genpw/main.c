#include <libgenpw/genpw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void genpw_info(const char* prog_name)
{
    printf("Использование: %s длина [-n] [-c] [-C] [-s]\n", prog_name);
    printf("Где:\n");
    printf("  длина - длина пароля (не менее 4)\n");
    printf("Флаги:\n");
    printf("  -n - включить цифры\n");
    printf("  -c - включить строчные буквы\n");
    printf("  -C - включить заглавные буквы\n");
    printf("  -s - включить специальные символы\n");
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        genpw_info(argv[0]);
        return EXIT_FAILURE;
    }

    int length = atoi(argv[1]);

    if (length < 4) {
        fprintf(stderr, "Ошибка: длина пароля должна быть не менее 4.\n");
        return EXIT_FAILURE;
    }

    bool include_digits = false;
    bool include_lower = false;
    bool include_upper = false;
    bool include_special = false;

    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0)
            include_digits = true;
        else if (strcmp(argv[i], "-c") == 0)
            include_lower = true;
        else if (strcmp(argv[i], "-C") == 0)
            include_upper = true;
        else if (strcmp(argv[i], "-s") == 0)
            include_special = true;
        else {
            fprintf(stderr, "Неизвестный флаг: %s\n", argv[i]);
            genpw_info(argv[0]);
            return EXIT_FAILURE;
        }
    }

    char password[256]; // Максимальная длина пароля

    // Инициализация генератора случайных чисел
    srand((unsigned int)time(NULL));

    int result = generate_password(
            length,
            include_digits,
            include_lower,
            include_upper,
            include_special,
            password,
            sizeof(password));
    if (result != 0) {
        switch (result) {
        case 1:
            fprintf(stderr, "Ошибка: длина пароля должна быть не менее 4.\n");
            break;
        case 2:
            fprintf(stderr, "Ошибка: недостаточный размер буфера.\n");
            break;
        default:
            fprintf(stderr, "Неизвестная ошибка.\n");
            break;
        }
        return EXIT_FAILURE;
    }

    printf("%s\n", password);
    return EXIT_SUCCESS;
}