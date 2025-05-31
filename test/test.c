#define CTEST_MAIN
#include <ctest.h>
#include <ctype.h>
#include <libgenpw/genpw.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CTEST(generate_password, all_flags_enabled)
{
    char password[32];
    int length = 12;

    int result = generate_password(
            length,
            true, // digits
            true, // lower
            true, // upper
            true, // special
            password,
            sizeof(password));

    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(length, strlen(password));

    bool has_digit = false, has_lower = false, has_upper = false,
         has_special = false;
    for (int i = 0; i < length; i++) {
        if (isdigit(password[i]))
            has_digit = true;
        else if (islower(password[i]))
            has_lower = true;
        else if (isupper(password[i]))
            has_upper = true;
        else
            has_special = true;
    }

    ASSERT_TRUE(has_digit);
    ASSERT_TRUE(has_lower);
    ASSERT_TRUE(has_upper);
    ASSERT_TRUE(has_special);
}

CTEST(generate_password, only_digits)
{
    char password[32];
    int length = 8;

    int result = generate_password(
            length,
            true,  // digits
            false, // lower
            false, // upper
            false, // special
            password,
            sizeof(password));

    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(length, strlen(password));

    for (int i = 0; i < length; i++) {
        ASSERT_TRUE(isdigit(password[i]));
    }
}

CTEST(generate_password, lower_and_upper)
{
    char password[32];
    int length = 10;

    int result = generate_password(
            length,
            false, // digits
            true,  // lower
            true,  // upper
            false, // special
            password,
            sizeof(password));

    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(length, strlen(password));

    bool has_lower = false, has_upper = false;
    for (int i = 0; i < length; i++) {
        if (islower(password[i]))
            has_lower = true;
        else if (isupper(password[i]))
            has_upper = true;
        else
            ASSERT_FAIL();
    }

    ASSERT_TRUE(has_lower);
    ASSERT_TRUE(has_upper);
}

CTEST(generate_password, buffer_too_small)
{
    char password[5];
    int length = 10;

    int result = generate_password(
            length,
            true, // digit
            true, // lower
            true, // upper
            true, // special
            password,
            sizeof(password));

    ASSERT_NOT_EQUAL(0, result);
}

CTEST(generate_password, minimum_length)
{
    char password[8];
    int length = 4;

    int result = generate_password(
            length,
            true, // digits
            true, // lower
            true, // upper
            true, // special
            password,
            sizeof(password));

    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(length, strlen(password));
}

CTEST(generate_password, only_special_chars)
{
    char password[32];
    int length = 6;
    const char special_chars[] = "!@#$%^&*()_+-=[]{}|;:,.<>?";

    int result = generate_password(
            length,
            false, // digits
            false, // lower
            false, // upper
            true,  // special
            password,
            sizeof(password));

    ASSERT_EQUAL(0, result);
    ASSERT_EQUAL(length, strlen(password));

    for (int i = 0; i < length; i++) {
        if (strchr(special_chars, password[i]) == NULL) {
            ASSERT_FAIL();
        }
    }
}
int main(int argc, const char* argv[])
{
    return ctest_main(argc, argv);
}