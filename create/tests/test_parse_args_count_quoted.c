#include <stdio.h>
#include <stdlib.h>

#include "../arg_parser.h"

/* シェルは --count="19" のクォートを外して --count=19 として argv に渡す */
int main(void) {
    char *argv[] = {"main", "--count=19"};
    ParseResult *result = parse_args(2, argv);

    if (result == NULL) {
        fprintf(stderr, "parse_args returned NULL\n");
        return EXIT_FAILURE;
    }

    if (result->status != PARSE_SUCCESS) {
        fprintf(stderr, "expected PARSE_SUCCESS for --count=\"19\"\n");
        free_parse_result(result);
        return EXIT_FAILURE;
    }

    if (result->config == NULL) {
        fprintf(stderr, "expected non-NULL config\n");
        free_parse_result(result);
        return EXIT_FAILURE;
    }

    if (result->config->count != 19) {
        fprintf(stderr, "expected count value 19, got %u\n",
                result->config->count);
        free_parse_result(result);
        return EXIT_FAILURE;
    }

    free_parse_result(result);
    return EXIT_SUCCESS;
}
