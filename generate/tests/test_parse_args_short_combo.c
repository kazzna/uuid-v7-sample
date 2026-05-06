#include <stdio.h>
#include <stdlib.h>

#include "arg_parser.h"

static int expect_status(const char *label, int argc, char *argv[], ParseStatus expected_status,
                         int help, int version, unsigned int count_value) {
    ParseResult *result = parse_args(argc, argv);

    if (result == NULL) {
        fprintf(stderr, "FAIL %s: parse_args returned NULL\n", label);
        return 1;
    }

    if (result->status != expected_status) {
        fprintf(stderr, "FAIL %s: expected status %d, got %d\n", label, expected_status,
                result->status);
        free_parse_result(result);
        return 1;
    }

    if (result->config == NULL) {
        fprintf(stderr, "FAIL %s: expected non-NULL config\n", label);
        free_parse_result(result);
        return 1;
    }

    if (result->config->help != help) {
        fprintf(stderr, "FAIL %s: expected help=%d, got %d\n", label, help,
                result->config->help);
        free_parse_result(result);
        return 1;
    }

    if (result->config->version != version) {
        fprintf(stderr, "FAIL %s: expected version=%d, got %d\n", label, version,
                result->config->version);
        free_parse_result(result);
        return 1;
    }

    if (result->config->count != count_value) {
        fprintf(stderr, "FAIL %s: expected count=%u, got %u\n", label, count_value,
                result->config->count);
        free_parse_result(result);
        return 1;
    }

    free_parse_result(result);
    return 0;
}

static int expect_status_only(const char *label, int argc, char *argv[], ParseStatus expected_status) {
    ParseResult *result = parse_args(argc, argv);

    if (result == NULL) {
        fprintf(stderr, "FAIL %s: parse_args returned NULL\n", label);
        return 1;
    }

    if (result->status != expected_status) {
        fprintf(stderr, "FAIL %s: expected status %d, got %d\n", label, expected_status,
                result->status);
        free_parse_result(result);
        return 1;
    }

    free_parse_result(result);
    return 0;
}

int main(void) {
    int failures = 0;

    /* -hvc 4: help=1, version=1, count=4 → PARSE_HELP */
    {
        char *argv[] = {"main", "-hvc", "4"};
        failures += expect_status("-hvc 4", 3, argv, PARSE_HELP, 1, 1, 4);
    }

    /* -ch: count needs value → help error */
    {
        char *argv[] = {"main", "-ch"};
        failures += expect_status_only("-ch", 2, argv, PARSE_HELP);
    }

    /* -hcv: count needs value → help error */
    {
        char *argv[] = {"main", "-hcv"};
        failures += expect_status_only("-hcv", 2, argv, PARSE_HELP);
    }

    /* -cv: count needs value → help */
    {
        char *argv[] = {"main", "-cv"};
        failures += expect_status_only("-cv", 2, argv, PARSE_HELP);
    }

    /* -vc: count needs value → help */
    {
        char *argv[] = {"main", "-vc"};
        failures += expect_status_only("-vc", 2, argv, PARSE_HELP);
    }

    /* -vc 3: version=1, count=3 → PARSE_VERSION */
    {
        char *argv[] = {"main", "-vc", "3"};
        failures += expect_status("-vc 3", 3, argv, PARSE_VERSION, 0, 1, 3);
    }

    /* -v -c 4: version=1, count=4 → PARSE_VERSION */
    {
        char *argv[] = {"main", "-v", "-c", "4"};
        failures += expect_status("-v -c 4", 4, argv, PARSE_VERSION, 0, 1, 4);
    }

    return failures > 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}
