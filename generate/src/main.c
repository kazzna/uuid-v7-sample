#include <stdio.h>
#include <stdlib.h>

#include "arg_parser.h"
#include "uuid_v7.h"

int main(int argc, char *argv[]) {
    ParseResult *result = parse_args(argc, argv);

    if (result == NULL) {
        fprintf(stderr, "fatal: out of memory\n");
        return EXIT_FAILURE;
    }

    if (result->status == PARSE_SUCCESS) {
        for (unsigned int i = 0; i < result->config->count; i++) {
            char uuid[37];
            uuid_v7_generate(uuid);
            printf("%s\n", uuid);
        }
    }

    free_parse_result(result);
    return EXIT_SUCCESS;
}
