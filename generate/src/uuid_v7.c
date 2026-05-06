#include <uuid/uuid.h>
#include "uuid_v7.h"

void uuid_v7_generate(char *out) {
    uuid_t b_uuid;
    uuid_generate_time_v7(b_uuid);
    uuid_unparse_lower(b_uuid, out);
}
