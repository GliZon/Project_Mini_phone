#pragma once

#include <stdint.h>



/*
 * Quick Messages
 */

const char *message_service_get_quick_message(
    uint8_t index
);

void message_service_set_quick_message(
    uint8_t index,
    const char *text
);



/*
 * Draft
 */

const char *message_service_get_draft(
    void
);

void message_service_set_draft(
    const char *text
);