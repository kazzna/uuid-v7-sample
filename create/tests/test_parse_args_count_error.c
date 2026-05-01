#include <stdio.h>
#include <stdlib.h>

#include "../arg_parser.h"

static int expect_help(const char *label, int argc, char *argv[]) {
    ParseResult *result = parse_args(argc, argv);

    if (result == NULL) {
        fprintf(stderr, "FAIL %s: parse_args returned NULL\n", label);
        return 1;
    }

    if (result->status != PARSE_HELP) {
        fprintf(stderr, "FAIL %s: expected PARSE_HELP on error, got %d\n", label, result->status);
        free_parse_result(result);
        return 1;
    }

    free_parse_result(result);
    return 0;
}

int main(void) {
    int failures = 0;

    /* -c 単体（値なし） */
    {
        char *argv[] = {"main", "-c"};
        failures += expect_help("-c alone", 2, argv);
    }

    /* --count 単体（値なし） */
    {
        char *argv[] = {"main", "--count"};
        failures += expect_help("--count alone", 2, argv);
    }

    /* --count = 11（= の周りにスペース → argv が分割される） */
    {
        char *argv[] = {"main", "--count", "=", "11"};
        failures += expect_help("--count = 11", 4, argv);
    }

    /* -c -4（負の数） */
    {
        char *argv[] = {"main", "-c", "-4"};
        failures += expect_help("-c -4", 3, argv);
    }

    /* --count 0.8（小数） */
    {
        char *argv[] = {"main", "--count", "0.8"};
        failures += expect_help("--count 0.8", 3, argv);
    }

    /* --count 4*2（非数値） */
    {
        char *argv[] = {"main", "--count", "4*2"};
        failures += expect_help("--count 4*2", 3, argv);
    }

    return failures > 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}
