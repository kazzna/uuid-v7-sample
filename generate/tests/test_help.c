#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_output(const char *cmd, const char *expected_substring) {
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

    int status = pclose(fp);
    int exit_code = WEXITSTATUS(status);

    if (exit_code != EXIT_SUCCESS) {
        fprintf(stderr, "Fail: '%s' exited with non-zero code %d\n", cmd, exit_code);
        return 0;
    }

    if (strstr(actual_output, expected_substring) != NULL) {
        return 1;
    }

    fprintf(stderr, "Fail: Output of '%s' did not contain expected content.\n", cmd);
    fprintf(stderr, "Expected to contain: %s\n", expected_substring);
    fprintf(stderr, "Actual output:\n%s\n", actual_output);
    return 0;
}

int main(void) {
    int success = 1;

    /*
     * Check --help output.
     * We look for key components of the help message.
     */
    const char *help_cmd = "./uuid_generate --help";

    const char *checks[] = {
        "Usage: uuid_generate [OPTIONS]",
        "A simple UUID v7 generator.",
        "-c, --count <n>",
        "-h, --help",
        "-v, --version"
    };

    for (size_t i = 0; i < sizeof(checks) / sizeof(checks[0]); i++) {
        if (!check_output(help_cmd, checks[i])) {
            success = 0;
        }
    }

    return success ? EXIT_SUCCESS : EXIT_FAILURE;
}
