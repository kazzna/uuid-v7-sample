#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#include "uuid_v7.h"

/* Helper to convert hex string to uint64_t */
unsigned long long hex_to_uint64(const char *hex, int len) {
    char buf[17];
    if (len > 16) len = 16;
    strncpy(buf, hex, len);
    buf[len] = '\0';
    return strtoull(buf, NULL, 16);
}

int main(void) {
    char uuid[37];
    uuid_v7_generate(uuid);

    printf("Testing UUID: %s\n", uuid);

    /* UUID v7: tttttttt-tttt-7xxx-yxxx-xxxxxxxxxxxx */
    /* Timestamp is the first 48 bits (12 hex chars) */
    char ts_hex[13];
    strncpy(ts_hex, uuid, 8);           /* First 8 chars */
    strncpy(ts_hex + 8, uuid + 9, 4);   /* Next 4 chars (skip hyphen) */
    ts_hex[12] = '\0';

    unsigned long long uuid_ts_ms = hex_to_uint64(ts_hex, 12);

    /* Get current system time in milliseconds */
    struct timeval tv;
    gettimeofday(&tv, NULL);
    unsigned long long now_ms = (unsigned long long)(tv.tv_sec) * 1000 + (tv.tv_usec / 1000);

    printf("UUID timestamp (ms): %llu\n", uuid_ts_ms);
    printf("System time (ms):    %llu\n", now_ms);

    /* Check if the difference is within 10 seconds (10000 ms) */
    long long diff = (long long)now_ms - (long long)uuid_ts_ms;
    if (diff < 0) diff = -diff;

    if (diff > 10000) {
        fprintf(stderr, "Fail: Timestamp difference too large (%lld ms)\n", diff);
        return EXIT_FAILURE;
    }

    printf("Success: Timestamp is valid (diff: %lld ms)\n", diff);
    return EXIT_SUCCESS;
}
