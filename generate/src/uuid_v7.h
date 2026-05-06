#ifndef UUID_V7_H
#define UUID_V7_H

/**
 * Generates a UUID v7 and returns it as a lower-case string.
 * @param out A buffer of at least 37 bytes (36 chars + null terminator).
 */
void uuid_v7_generate(char *out);

#endif
