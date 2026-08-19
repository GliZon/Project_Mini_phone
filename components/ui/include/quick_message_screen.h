#pragma once

#include "ui_event.h"

#include <stdint.h>

/*
 * Lifecycle
 */

void quick_message_screen_create(
    void
);

void quick_message_screen_destroy(
    void
);

void quick_message_screen_on_enter(
    void
);

void quick_message_screen_on_exit(
    void
);

void quick_message_screen_update(
    uint32_t dt_ms
);

void quick_message_screen_handle_event(
    ui_event_t *event
);
