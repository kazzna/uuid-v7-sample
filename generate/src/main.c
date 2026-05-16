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

    if (result->status == PARSE_HELP) {
        printf("Usage: uuid_generate [OPTIONS]\n");
        printf("\n");
        printf("A simple UUID v7 generator.\n");
        printf("\n");
        printf("Options:\n");
        printf("  -c, --count <n>  Number of UUIDs to generate (default: 1)\n");
        printf("  -h, --help       Display this help message\n");
        printf("  -v, --version    Display version information\n");
    } else if (result->status == PARSE_VERSION) {
        printf("uuid_generate version 1.0.0 (%s)\n", GIT_HASH);
    } else if (result->status == PARSE_SUCCESS) {
        for (unsigned int i = 0; i < result->config->count; i++) {
            char uuid[37];
            uuid_v7_generate(uuid);
            printf("%s\n", uuid);
        }
    }

    free_parse_result(result);
    return EXIT_SUCCESS;
}
