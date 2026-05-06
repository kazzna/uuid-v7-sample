#include "arg_parser.h"

#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

static Config *create_config(void) {
    Config *config;

    config = (Config *)malloc(sizeof(Config));
    if (config == NULL) {
        return NULL;
    }

    config->help = 0;
    config->version = 0;
    config->count = 1;
    return config;
}

static int parse_unsigned_int(const char *text, unsigned int *out_value) {
    char *endptr;
    unsigned long value;

    if (text == NULL || *text == '\0') {
        return 0;
    }

    if (text[0] == '-' || text[0] == '+') {
        return 0;
    }

    errno = 0;
    value = strtoul(text, &endptr, 10);
    if (errno != 0 || *endptr != '\0' || value > UINT_MAX) {
        return 0;
    }

    *out_value = (unsigned int)value;
    return 1;
}

ParseResult *parse_args(int argc, char *argv[]) {
    ParseResult *result;
    Config *config;
    const char *short_opt;
    unsigned int parsed_count;
    int i, j;

    config = create_config();
    if (config == NULL) {
        return NULL;
    }

    result = (ParseResult *)malloc(sizeof(ParseResult));
    if (result == NULL) {
        free(config);
        return NULL;
    }

    for (i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] != '\0' && argv[i][1] != '-') {
            short_opt = argv[i] + 1;

            for (j = 0; short_opt[j] != '\0'; j++) {
                if (short_opt[j] == 'h') {
                    config->help = 1;
                    continue;
                }

                if (short_opt[j] == 'v') {
                    config->version = 1;
                    continue;
                }

                if (short_opt[j] == 'c') {
                    const char *tail = short_opt + j + 1;

                    if (*tail != '\0') {
                        /* Handle -c=VALUE format */
                        if (*tail == '=') {
                            if (!parse_unsigned_int(tail + 1, &parsed_count)) {
                                result->status = PARSE_HELP;
                                result->config = config;
                                return result;
                            }
                            config->count = parsed_count;
                        } else if (parse_unsigned_int(tail, &parsed_count)) {
                            config->count = parsed_count;
                        } else {
                            result->status = PARSE_HELP;
                            result->config = config;
                            return result;
                        }
                    } else {
                        if (i + 1 >= argc || !parse_unsigned_int(argv[i + 1], &parsed_count)) {
                            result->status = PARSE_HELP;
                            result->config = config;
                            return result;
                        }

                        config->count = parsed_count;
                        i++;
                    }

                    break;
                }

                /* Unknown character in short option */
                result->status = PARSE_HELP;
                result->config = config;
                return result;
            }

            continue;
        }

        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            config->help = 1;
            continue;
        }

        if (strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-v") == 0) {
            config->version = 1;
            continue;
        }

        if (strcmp(argv[i], "--count") == 0) {
            if (i + 1 >= argc || !parse_unsigned_int(argv[i + 1], &parsed_count)) {
                result->status = PARSE_HELP;
                result->config = config;
                return result;
            }

            config->count = parsed_count;
            i++;
            continue;
        }

        if (strncmp(argv[i], "--count=", 8) == 0) {
            if (!parse_unsigned_int(argv[i] + 8, &parsed_count)) {
                result->status = PARSE_HELP;
                result->config = config;
                return result;
            }

            config->count = parsed_count;
            continue;
        }

        if (strcmp(argv[i], "-c") == 0) {
            if (i + 1 >= argc || !parse_unsigned_int(argv[i + 1], &parsed_count)) {
                result->status = PARSE_HELP;
                result->config = config;
                return result;
            }

            config->count = parsed_count;
            i++;
            continue;
        }

        /* Unknown option format */
        result->status = PARSE_HELP;
        result->config = config;
        return result;
    }

    result->status = PARSE_SUCCESS;
    if (config->help == 1) {
        result->status = PARSE_HELP;
    } else if (config->version == 1) {
        result->status = PARSE_VERSION;
    }

    result->config = config;
    return result;
}

void free_parse_result(ParseResult *result) {
    if (result == NULL) {
        return;
    }

    if (result->config != NULL) {
        free(result->config);
    }

    free(result);
}
