#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    FILE *fp;
    char buffer[1024];
    int count = 0;

    /* Run the uuid_generate command with --count 5 */
    /* Note: The path might need adjustment depending on where ctest runs */
    fp = popen("./uuid_generate --count 5", "r");
    if (fp == NULL) {
        perror("popen");
        return EXIT_FAILURE;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        if (strlen(buffer) > 1) { /* Ignore empty lines if any */
            count++;
        }
    }

    pclose(fp);

    if (count != 5) {
        fprintf(stderr, "Fail: Expected 5 lines, got %d\n", count);
        return EXIT_FAILURE;
    }

    printf("Success: Got %d lines as expected\n", count);
    return EXIT_SUCCESS;
}
