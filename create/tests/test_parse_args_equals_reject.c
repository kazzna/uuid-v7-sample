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
        fprintf(stderr, "FAIL %s: expected PARSE_HELP, got %d\n", label, result->status);
        free_parse_result(result);
        return 1;
    }

    free_parse_result(result);
    return 0;
}

int main(void) {
    int failures = 0;

    /* --help=1 should be rejected */
    {
        char *argv[] = {"main", "--help=1"};
        failures += expect_help("--help=1", 2, argv);
    }

    /* --version=1 should be rejected */
    {
        char *argv[] = {"main", "--version=1"};
        failures += expect_help("--version=1", 2, argv);
    }

    /* -h=1 should be rejected */
    {
        char *argv[] = {"main", "-h=1"};
        failures += expect_help("-h=1", 2, argv);
    }

    /* -v=1 should be rejected */
    {
        char *argv[] = {"main", "-v=1"};
        failures += expect_help("-v=1", 2, argv);
    }

    return failures > 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}
