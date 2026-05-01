#include <stdio.h>
#include <stdlib.h>

#include "arg_parser.h"

int main(int argc, char *argv[]) {
    ParseResult *result = parse_args(argc, argv);

    if (result == NULL) {
        fprintf(stderr, "fatal: out of memory\n");
        return EXIT_FAILURE;
    }

    if (result->status == PARSE_HELP) {
        /* TODO: display help */
    } else if (result->status == PARSE_VERSION) {
        /* TODO: display version */
    } else {
        /* TODO: generate and display UUIDs */
    }

    free_parse_result(result);
    return EXIT_SUCCESS;
}
