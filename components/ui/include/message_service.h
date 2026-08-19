#pragma once

#include <stdint.h>
#include <stdbool.h>



/*
 * Quick Messages
 */

uint8_t message_service_get_quick_message_count(
    void
);

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



/*
 * Outgoing
 *
 * Staged between picking the text and picking
 * the recipient, so both send paths converge.
 */

void message_service_stage_outgoing(
    const char *text
);

const char *message_service_get_outgoing(
    void
);

void message_service_clear_outgoing(
    void
);



/*
 * Recipient
 *
 * MESSAGE_RECIPIENT_ALL broadcasts.
 */

void message_service_set_recipient(
    uint8_t recipient
);

uint8_t message_service_get_recipient(
    void
);



/*
 * Send
 *
 * Returns false when nothing is staged.
 */

bool message_service_send(
    void
);