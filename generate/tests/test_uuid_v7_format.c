#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* UUID v7 generate function declaration (to be implemented) */
void uuid_v7_generate(char *out);

int is_hex(char c) {
    c = tolower(c);
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f');
}

int main(void) {
    char uuid[37]; /* 36 chars + null terminator */
    memset(uuid, 0, sizeof(uuid));

    /* This will fail to link or run because uuid_v7_generate is not implemented */
    uuid_v7_generate(uuid);

    printf("Generated UUID: %s\n", uuid);

    /* 1. Check length */
    if (strlen(uuid) != 36) {
        fprintf(stderr, "Fail: Length is %zu, expected 36\n", strlen(uuid));
        return EXIT_FAILURE;
    }

    /* 2. Check hyphens at 8, 13, 18, 23 (0-indexed: 8, 13, 18, 23) */
    if (uuid[8] != '-' || uuid[13] != '-' || uuid[18] != '-' || uuid[23] != '-') {
        fprintf(stderr, "Fail: Hyphen placement is incorrect\n");
        return EXIT_FAILURE;
    }

    /* 3. Check if all other characters are hex */
    for (int i = 0; i < 36; i++) {
        if (i == 8 || i == 13 || i == 18 || i == 23) continue;
        if (!is_hex(uuid[i])) {
            fprintf(stderr, "Fail: Character at index %d is not hex: '%c'\n", i, uuid[i]);
            return EXIT_FAILURE;
        }
    }

    /* 4. Check version (14th char should be '7') */
    if (uuid[14] != '7') {
        fprintf(stderr, "Fail: Version is '%c', expected '7'\n", uuid[14]);
        return EXIT_FAILURE;
    }

    /* 5. Check variant (19th char should be 8, 9, a, or b) */
    char v = tolower(uuid[19]);
    if (v != '8' && v != '9' && v != 'a' && v != 'b') {
        fprintf(stderr, "Fail: Variant is '%c', expected 8, 9, a, or b\n", v);
        return EXIT_FAILURE;
    }

    printf("Success: UUID v7 format is valid!\n");
    return EXIT_SUCCESS;
}
