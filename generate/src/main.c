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

    char uuid[37];
    uuid_v7_generate(uuid);
    printf("%s\n", uuid);

    free_parse_result(result);
    return EXIT_SUCCESS;
}
