#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Helper to convert hex string to uint64_t */
unsigned long long hex_to_uint64(const char *hex, int len) {
    char buf[17];
    if (len > 16) len = 16;
    strncpy(buf, hex, len);
    buf[len] = '\0';
    return strtoull(buf, NULL, 16);
}

unsigned long long extract_timestamp(const char *uuid) {
    char ts_hex[13];
    strncpy(ts_hex, uuid, 8);           /* First 8 chars */
    strncpy(ts_hex + 8, uuid + 9, 4);   /* Next 4 chars (skip hyphen) */
    ts_hex[12] = '\0';
    return hex_to_uint64(ts_hex, 12);
}

int main(void) {
    FILE *fp;
    char buffer[1024];
    unsigned long long prev_ts = 0;
    int count = 0;

    fp = popen("./uuid_generate --count 10", "r");
    if (fp == NULL) {
        perror("popen");
        return EXIT_FAILURE;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        if (strlen(buffer) < 36) continue;

        unsigned long long current_ts = extract_timestamp(buffer);
        printf("UUID: %s -> Timestamp: %llu\n", buffer, current_ts);

        if (count > 0 && current_ts < prev_ts) {
            fprintf(stderr, "Fail: Timestamps are not in chronological order! (%llu < %llu)\n", current_ts, prev_ts);
            pclose(fp);
            return EXIT_FAILURE;
        }

        prev_ts = current_ts;
        count++;
    }

    pclose(fp);

    if (count < 2) {
        /* If we only got 1 or 0 UUIDs, we can't really verify the order */
        fprintf(stderr, "Fail: Not enough UUIDs generated to verify order (got %d)\n", count);
        return EXIT_FAILURE;
    }

    printf("Success: %d UUIDs are in chronological order\n", count);
    return EXIT_SUCCESS;
}
