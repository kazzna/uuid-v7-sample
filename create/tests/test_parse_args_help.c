#include <stdio.h>
#include <stdlib.h>

#include "../arg_parser.h"

int main(void) {
    char *argv[] = {"main", "--help"};
    ParseResult *result = parse_args(2, argv);

    if (result == NULL) {
        fprintf(stderr, "parse_args returned NULL\n");
        return EXIT_FAILURE;
    }

    if (result->status != PARSE_HELP) {
        fprintf(stderr, "expected PARSE_HELP for --help\n");
        free_parse_result(result);
        return EXIT_FAILURE;
    }

    if (result->config == NULL || result->config->help != 1) {
        fprintf(stderr, "expected help=1 for --help\n");
        free_parse_result(result);
        return EXIT_FAILURE;
    }

    free_parse_result(result);
    return EXIT_SUCCESS;
}
