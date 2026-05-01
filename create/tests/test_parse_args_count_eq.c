#include <stdio.h>
#include <stdlib.h>

#include "../arg_parser.h"

int main(void) {
    char *argv[] = {"main", "--count=6"};
    ParseResult *result = parse_args(2, argv);

    if (result == NULL) {
        fprintf(stderr, "parse_args returned NULL\n");
        return EXIT_FAILURE;
    }

    if (result->status != PARSE_SUCCESS) {
        fprintf(stderr, "expected PARSE_SUCCESS for --count=6\n");
        free_parse_result(result);
        return EXIT_FAILURE;
    }

    if (result->config == NULL) {
        fprintf(stderr, "expected non-NULL config\n");
        free_parse_result(result);
        return EXIT_FAILURE;
    }

    if (result->config->count != 6) {
        fprintf(stderr, "expected count value 6, got %u\n",
                result->config->count);
        free_parse_result(result);
        return EXIT_FAILURE;
    }

    free_parse_result(result);
    return EXIT_SUCCESS;
}
