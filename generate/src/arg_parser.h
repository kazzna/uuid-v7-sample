#ifndef ARG_PARSER_H
#define ARG_PARSER_H

typedef enum {
    PARSE_HELP,
    PARSE_VERSION,
    PARSE_SUCCESS
} ParseStatus;

typedef struct {
    int help;
    int version;
    unsigned int count;
} Config;

typedef struct {
    ParseStatus status;
    Config *config;
} ParseResult;

ParseResult *parse_args(int argc, char *argv[]);
void free_parse_result(ParseResult *result);

#endif
