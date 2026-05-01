#include <stdio.h>
#include <stdlib.h>

#include "../arg_parser.h"

int main(void) {
    char *argv[] = {"main", "--version"};
    ParseResult *result = parse_args(2, argv);

    if (result == NULL) {
        fprintf(stderr, "parse_args returned NULL\n");
        return EXIT_FAILURE;
    }

    if (result->status != PARSE_VERSION) {
        fprintf(stderr, "expected PARSE_VERSION for --version\n");
        free_parse_result(result);
        return EXIT_FAILURE;
    }

    if (result->config == NULL || result->config->version != 1) {
        fprintf(stderr, "expected version=1 for --version\n");
        free_parse_result(result);
        return EXIT_FAILURE;
    }

    free_parse_result(result);
    return EXIT_SUCCESS;
}
