#include <stdio.h>
#include <stdlib.h>

#include "../arg_parser.h"

static int test_short_flag(void) {
    char *argv[] = {"main", "-h"};
    ParseResult *result = parse_args(2, argv);

    if (result == NULL) {
        fprintf(stderr, "FAIL test_short_flag: parse_args returned NULL\n");
        return 1;
    }

    if (result->status != PARSE_HELP) {
        fprintf(stderr, "FAIL test_short_flag: expected PARSE_HELP for -h\n");
        free_parse_result(result);
        return 1;
    }

    if (result->config->help != 1) {
        fprintf(stderr, "FAIL test_short_flag: expected help=1 for -h, got %d\n",
                result->config->help);
        free_parse_result(result);
        return 1;
    }

    free_parse_result(result);
    return 0;
}

static int test_no_args(void) {
    char *argv[] = {"main"};
    ParseResult *result = parse_args(1, argv);

    if (result == NULL) {
        fprintf(stderr, "FAIL test_no_args: parse_args returned NULL\n");
        return 1;
    }

    if (result->status != PARSE_SUCCESS) {
        fprintf(stderr, "FAIL test_no_args: expected PARSE_SUCCESS for no args\n");
        free_parse_result(result);
        return 1;
    }

    if (result->config->help != 0) {
        fprintf(stderr, "FAIL test_no_args: expected help=0, got %d\n",
                result->config->help);
        free_parse_result(result);
        return 1;
    }

    if (result->config->version != 0) {
        fprintf(stderr, "FAIL test_no_args: expected version=0, got %d\n",
                result->config->version);
        free_parse_result(result);
        return 1;
    }

    if (result->config->count != 1) {
        fprintf(stderr, "FAIL test_no_args: expected count=1, got %u\n",
                result->config->count);
        free_parse_result(result);
        return 1;
    }

    free_parse_result(result);
    return 0;
}

int main(void) {
    int failures = 0;

    failures += test_short_flag();
    failures += test_no_args();

    return failures > 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}
