#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_hex_string(const char *s) {
    if (*s == '\0') return 0;
    while (*s) {
        if (!isxdigit((unsigned char)*s)) return 0;
        s++;
    }
    return 1;
}

int is_valid_version_format(const char *output) {
    const char *prefix = "uuid_generate version 1.0.0 (";
    char *start = strstr(output, prefix);
    if (!start) return 0;

    start += strlen(prefix);
    char *end = strchr(start, ')');
    if (!end) return 0;

    size_t len = end - start;
    char hash[64];
    if (len >= sizeof(hash)) return 0;
    strncpy(hash, start, len);
    hash[len] = '\0';

    if (strcmp(hash, "unknown") == 0) return 1;
    return is_hex_string(hash);
}

int check_version_output(const char *cmd) {
    FILE *fp;
    char buffer[1024];
    char actual_output[4096] = "";

    fp = popen(cmd, "r");
    if (fp == NULL) {
        perror("popen");
        return 0;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        strcat(actual_output, buffer);
    }
    pclose(fp);

    if (is_valid_version_format(actual_output)) {
        return 1;
    }

    fprintf(stderr, "Fail: Output of '%s' did not match expected version format.\n", cmd);
    fprintf(stderr, "Actual output:\n%s\n", actual_output);
    return 0;
}

int main(void) {
    int success = 1;

    /* Check --version */
    if (!check_version_output("./uuid_generate --version")) {
        success = 0;
    }

    return success ? EXIT_SUCCESS : EXIT_FAILURE;
}
